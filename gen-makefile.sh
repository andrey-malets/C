#!/usr/bin/env bash

{
  for file in *.c; do
    echo -e "${file%%.c}: $file"
    echo -e "\tmkdir -p bin"
    echo -e "\tclang -Wall -pedantic -o bin/${file%%.c} $file"
    echo -e "\t./bin/${file%%.c}"
  done
} > Makefile
