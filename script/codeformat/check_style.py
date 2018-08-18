#!/usr/bin/env python3

import codeformat
import multiprocessing

if __name__ == "__main__":
    multiprocessing.freeze_support()
    codeformat.codeformat_main(["--checkstyle-all", "-v"])
