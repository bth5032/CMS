#!/bin/bash

echo ConcurrentReads:VelocityMBps:BufferSize
for k in 1 3 6 10; do
	for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
		#/nfs-7/t2tas/drop_cache
		for i in `seq 1 $k`; do
			./reader -f /hadoop/cms/store/user/matevz/IOHeavyCI/trimmed_infile_$i -b $j -a $k &   
		done
		wait
	done
done