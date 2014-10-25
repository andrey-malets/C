#!/usr/bin/env bash

{
  for file in *.c; do
    echo -e "${file%%.c}: $file"
    echo -e "\tmkdir -p bin"
    opts="$(grep '^// clang_opts: ' "$file" | cut -f2 -d:)"
    echo -e "\tclang $opts -Wall -pedantic -o bin/${file%%.c} $file"
    echo -e "\t./bin/${file%%.c}"
  done
} > Makefile
