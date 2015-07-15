#!/bin/bash

## This script will run 'reader' on a machine for 
## various block sizes($j) and concurrent reads($k)
## it assumes the files are split amoungst the /data$i directories.
## It drops the ram cahce using the program Matevz wrote
## and then calls reader for each file on data3 through data12
## and waits for all the reads to return before doing the next round.

echo ConcurrentReads:VelocityMBps:BufferSize
for k in 1 3 6 10; do
	for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
		/nfs-7/t2tas/drop_cache
		for i in `seq 3 $(($k+2))`; do
			./nfs-7/t2tas/reader -f /data$i/xrootd/trimmed_infile_$i -b $j -a $k &   
		done
		wait
	done
done