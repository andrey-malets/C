#!/usr/bin/env bash

i=1
while [ $i -lt 100000000 ]
do
    ocperf.py stat -e mem_load_uops_retired.l1_hit,mem_load_uops_retired.l2_hit,mem_load_uops_retired.llc_hit,mem_load_uops_retired.llc_miss,mem_uops_retired.all_loads ./a.out $i 2>&1 | egrep 'mem_|length' | grep -v perf
    i=$((i * 2))
done
