#!/bin/bash

echo ConcurrentReads:Velocity:BufferSize
for k in 1 3 6 10; do
	for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
		/nfs-7/t2tas/drop_cache
		for i in `seq 1 $((k-1))`; do
			./reader -f /data/tmp/IOHeavyCI/infile_$i -b $j -a $k &   
		done
			./reader -f /data/tmp/IOHeavyCI/infile_$k -b $j -a $k
	done
done