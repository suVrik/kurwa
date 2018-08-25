#!/usr/bin/env python3

import argparse
import os
import sys
import subprocess
import multiprocessing
import fnmatch
import logging


# Repository root directory
repository_root_dir = os.path.abspath(os.path.dirname(__file__) + "/../..")


clang_format_binary = 'clang-format'


# Project sources
sources_list = [
    "framework",
    "program"
]


# Exception rules in 'fnmatch' format
ignore_list = []


# Extensions to check, in lowercase
sources_extensions = ["*.h", "*.cpp"]


def multiprocess_map(func, items):
    # Multiprocess version of 'return map(func, items)'
    pool = multiprocessing.Pool()
    result = pool.map(func, items)
    pool.close()
    pool.join()
    return result


def clang_format_files(filenames):
    return multiprocess_map(clang_format_file, filenames)


def clang_format_file(file_name):
    assert(clang_format_binary != None)
    try:
        if not os.path.isfile(file_name):
            return (False, "File not exist!")
        proc = subprocess.Popen([clang_format_binary, '--style=file', '-i', file_name],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        if len(stderr) > 0:
            logging.debug(stderr)
        return (True, file_name)
    except OSError as e:
        logging.error("{}".format(e))
        logging.error("Check 'clang-format' binaries!")
        return (False, "clang-format error!")


def checkstyle_file(file_name):
    assert(clang_format_binary != None)
    try:
        if not os.path.isfile(file_name):
            return (False, "File not exist!")
        proc = subprocess.Popen([clang_format_binary, '--style=file', '-output-replacements-xml', file_name],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        if len(stderr) > 0:
            logging.debug(stderr)
        success = stdout.find(b"<replacement ") < 0
        return (success, file_name)
    except OSError as e:
        logging.error("{}".format(e))
        logging.error("Check 'clang-format' binaries!")
        return (False, "clang-format error!")


def execute_in_path(new_dir, callback):
    # Save current directory
    previous_dir = os.getcwd()
    try:
        logging.debug("chdir: {}".format(new_dir))
        # Go to script directory
        os.chdir(new_dir)
        callback()
    finally:
        # restore current directory
        os.chdir(previous_dir)


# Filter source files
def is_file_from_sources(f):
    for prefix in sources_list:
        if f.startswith(prefix):
            return True
    return False


def is_valid_filename(file_name):
    if not any((fnmatch.fnmatch(file_name, ignore_rule) for ignore_rule in ignore_list)):
        for ext in sources_extensions:
            if fnmatch.fnmatch(file_name.lower(), ext):
                return True
    return False


def collect_all_filenames():
    files = []
    for source_dir in sources_list:
        for root, dirnames, filenames in os.walk(source_dir):
            root = os.path.relpath(os.path.abspath(root), repository_root_dir)
            for filename in filenames:
                full_filename = os.path.join(root, filename)
                if is_valid_filename(full_filename):
                    files.append(os.path.join(root, filename))
    return files


def format_all(parsed_args):
    logging.debug("format all - collecting files...")
    filenames = collect_all_filenames()
    logging.debug("Formatting {} files...".format(len(filenames)))
    # Process files
    if not parsed_args.simulate:
        result = clang_format_files(filenames)
        filenames = [file_name for _, file_name in result]
    else:
        logging.debug("Simulate: True")
    logging.debug("Files: ")
    for f in filenames:
        logging.debug("     {}".format(f))
    logging.debug("Total: {} files...".format(len(filenames)))
    logging.debug("format all - completed")


def checkstyle_all(parsed_args):
    logging.debug("checkstyle all - collecting files...")
    filenames = collect_all_filenames()
    logging.debug("Checking {} files...".format(len(filenames)))
    results = multiprocess_map(checkstyle_file, filenames)
    # Show report
    logging.debug("Problem files: ")
    has_errors = False
    for success, file_name in results:
        if not success:
            has_errors = True
            logging.warning("     {}".format(file_name))
    logging.debug("checkstyle all - completed")
    if has_errors:
        sys.exit(1)


def git_pre_commit(parsed_args):
    logging.debug("git pre commit hook - collecting files...")
    try:
        proc = subprocess.Popen(["git", "diff-index", "--cached", "--name-only", "HEAD"],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        if len(stderr) > 0:
            logging.debug(stderr)
    except OSError as e:
        logging.error("{}".format(e))
        logging.error("Check your 'git' installation! HINT: Add 'git' location to $PATH.")
        sys.exit(1)

    filenames = stdout.decode().strip().split("\n")
    filenames = list(filter(os.path.isfile, filenames))
    filenames = list(filter(is_file_from_sources, filenames))
    filenames = list(filter(is_valid_filename, filenames))

    # Process files
    if not parsed_args.simulate:
        clang_format_files(filenames)
    else:
        logging.debug("Simulate: True")
    logging.debug("Files: ")
    for f in filenames:
        logging.debug("     {}".format(f))
    total = len(filenames)
    while len(filenames) > 0:
        CHUNK_SIZE = 32
        filenames_chunk = filenames[:CHUNK_SIZE]
        filenames = filenames[CHUNK_SIZE:]
        proc = subprocess.Popen(["git", "add", "-f"] + filenames_chunk,
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
    logging.debug("Total: {} files...".format(total))
    logging.debug("git pre commit hook - completed")


def codeformat_main(argv):
    logging.basicConfig(level=logging.DEBUG,
                        format='%(levelname)s - %(message)s')
    parser = argparse.ArgumentParser(description='Codeformat tool.')
    parser.add_argument('--git-pre-commit', default=False,
                        action="store_true", help='Format only staged files')
    parser.add_argument('--format-all', default=False,
                        action="store_true", help='Format all files')
    parser.add_argument('--checkstyle-all', default=False,
                        action="store_true", help='Do style check for all files')
    parser.add_argument('--simulate', default=False,
                        action="store_true", help="Don`t change source files actually.")
    parser.add_argument("-v", '--verbose', default=False,
                        action="store_true", help='Verbose mode')
    parsed_args = parser.parse_args(argv)

    if not parsed_args.verbose:
        logging.disable(logging.INFO)

    logging.debug("Args: {}".format(parsed_args))
    logging.debug("Paths:")
    logging.debug("* repository_root_dir: {}".format(repository_root_dir))
    logging.debug("* clang-format: {}".format(clang_format_binary))

    def body():
        if parsed_args.checkstyle_all:
            checkstyle_all(parsed_args)
        elif parsed_args.format_all:
            format_all(parsed_args)
        elif parsed_args.git_pre_commit:
            git_pre_commit(parsed_args)
        else:
            parser.print_help()
    execute_in_path(repository_root_dir, body)


if __name__ == "__main__":
    multiprocessing.freeze_support()
    codeformat_main(sys.argv[1:])
