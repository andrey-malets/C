#!/usr/bin/env bash

{
  for file in *.c; do
    [[ -f "$file" ]] || continue;

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

{
    for maybe_dir in *; do
        if ! [[ -d "$maybe_dir" ]] || [[ "$maybe_dir" == bin ]]; then
            continue
        fi

        dir=$maybe_dir
        deps=()
        for file in "$dir"/*.c; do
            [[ -f "$file" ]] || continue;
            obj="bin/${file%%.c}.o"
            fdeps=($(perl -n -e \
                'if (/^#include "(.+)"$/) { print "'"$dir"'/".$1.$/; }' < $file))
            echo -e "$obj: $file ${fdeps[*]}"
            echo -e "\tmkdir -p bin/$dir"
            echo -e "\tclang -c -Wall -pedantic -o $obj $file"
            deps+=($obj)
        done
        binary="bin/$dir.bin"
        echo -e "$binary: ${deps[*]}"
        echo -e "\tclang -o $binary ${deps[*]}"

        echo ".PHONY: $dir"
        echo -e "$dir: $binary"
        echo -e "\t./$binary"
    done
} >> Makefile
