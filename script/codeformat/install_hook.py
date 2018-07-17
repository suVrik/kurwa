#!/usr/bin/env python3

import os
import shutil

if __name__ == "__main__":
    # Save current directory
    previous_dir = os.getcwd()
    # Go to script directory
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    try:
        # Create hooks directory
        hooks_path = "../../.git/hooks"
        if not os.path.exists(hooks_path):
            os.mkdir(hooks_path)
        # Copy hook script
        script_path = os.path.join(hooks_path, "pre-commit")
        if os.path.exists(script_path):
            print("File '{}' was overwritten".format(script_path))
        else:
            print("Pre-commit hook was successfully installed!")
        shutil.copy("pre-commit", script_path)
    finally:
        # recover current directory
        os.chdir(previous_dir)
