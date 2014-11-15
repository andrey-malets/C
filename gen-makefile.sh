#!/usr/bin/env bash

{
  for file in *.c; do
    echo -e "${file%%.c}: $file"
    echo -e "\tmkdir -p bin"
    clang_opts="$(grep '^// clang_opts: ' "$file" | cut -f3- -d' ')"
    prefix="$(grep '^// prefix: ' "$file" | cut -f3- -d' ')"
    suffix="$(grep '^// suffix: ' "$file" | cut -f2- -d:)"
    echo -e "\tclang $clang_opts -Wall -pedantic -o bin/${file%%.c} $file"
    if ! [[ -z "$prefix" ]]; then
        echo -e "\tbash -c \"${prefix} ./bin/${file%%.c}${suffix}\""
    else
        echo -e "\t./bin/${file%%.c}${suffix}"
    fi
  done
} > Makefile
