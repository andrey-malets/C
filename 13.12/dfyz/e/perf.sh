#!/usrb/bin/env bash

python ocperf.py stat -e mem_load_uops_llc_miss_retired.local_dram,mem_load_uops_llc_miss_retired.remote_dram ./a.out
