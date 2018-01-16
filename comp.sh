#!/bin/sh
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="malloc.so_x86_64_Darwin"
export DYLD_FORCE_FLAT_NAMESPACE=1