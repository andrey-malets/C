#!/usr/bin/env bash

set -eu

gcc -msse4 -O2 -std=c11 common.c $1/bench.c -o bin.$1
./bin.$1 red
./bin.$1 green
