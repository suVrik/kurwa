#!/usr/bin/env python3

import os
import shutil

if __name__ == "__main__":
    original_current_directory = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    try:
        hooks_path = "../../.git/hooks"
        if not os.path.exists(hooks_path):
            os.mkdir(hooks_path)

        script_path = os.path.join(hooks_path, "pre-commit")
        if os.path.exists(script_path):
            print("Pre-commit hook '{}' was overwritten!".format(script_path))
        else:
            print("Pre-commit hook was successfully installed!")
        shutil.copy("pre-commit", script_path)
    finally:
        os.chdir(original_current_directory)
