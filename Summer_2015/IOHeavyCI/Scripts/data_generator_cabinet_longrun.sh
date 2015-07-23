#!/bin/bash

# This script performs read testing on cabinet-8-8-0
# The specifics for this machine include "trimmed_infile"
# locations as well as the location of drop_caches.
# Written by Bobak Hashemi - July 2015

echo TrialNumber:ConcurrentReads:FileID:VelocityMBps:BufferSize
for trial in `seq 1 100`; do
	for k in 1 3 6 10; do
		for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
			/nfs-7/t2tas/drop_cache
			for i in `seq 1 $k`; do
				./reader -f /data$i/xrootd/trimmed_infile_$i -b $j -a '$trial    $k    $i' &   
			done
			wait
		done
	done
done