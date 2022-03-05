#!/bin/bash

################################################################################

build_dir="${1%/}"

################################################################################

if [ ! -z "$build_dir" ]
then
    rm -f coverage_full.info
    rm -f coverage.info
    rm -r -f coverage-report
    cd bin; ./tests; cd ..;
    lcov --capture --base-directory . --no-external --directory $build_dir --output-file coverage_full.info
    lcov --remove coverage_full.info -o coverage.info "$(pwd)/tests/*"
    genhtml coverage.info --output-directory coverage-report
else
    echo
    echo Error! Build directory path not specified.
    echo Usage:
    echo ./generate_coverage-report.sh BUILD_DIRECTORY_PATH
    echo
fi

################################################################################
