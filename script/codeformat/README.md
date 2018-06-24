# codeformat

Take a look at clang format settings in `.clang-format`.

You can run `scripts/codeformat/install_hook.py` from any directory to install clang format pre-commit hook.

Run `scripts/codeformat/codeformat.py --format-all` to format the whole repository.

Run `scripts/codeformat/codeformat.py --git-pre-commit` to format only staged files.

Run `scripts/codeformat/codeformat.py --checkstyle-all` to check style of the whole repository.

`--verbose` flag might be used to inspect errors.

**These files were originally created by [Blitzteam](http://blitzteam.com/).**
