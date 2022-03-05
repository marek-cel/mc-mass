#!/bin/bash

################################################################################

rm -f out_cpplint.txt

cpplint.py \
    --filter=-build/c++11,+build/c++14,-readability/multiline_comment,-readability/alt_tokens,-whitespace/parens,-whitespace/braces,-whitespace/indent,-whitespace/comments,-whitespace/newline,-whitespace/blank_line \
    --linelength=100 \
    --extensions=h,cpp --root=./src \
    ./src/*.cpp ./src/*.h ./src/*/*.cpp ./src/*/*.h \
    2> out_cpplint.txt

################################################################################
