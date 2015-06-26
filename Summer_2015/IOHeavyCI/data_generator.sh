#!/bin/bash

echo ConcurrentReads:ReadTime:BufferSize
for k in `seq 1 10`; do
	for j in 128 256 512 1024 4096 8192; do
		/nfs-7/t2tas/drop_cache
		for i in `seq 1 $((k-1))`; do
			./reader -f /data/tmp/IOHeavyCI/infile_$i -b $j -a $k &   
		done
			./reader -f /data/tmp/IOHeavyCI/infile_$k -b $j -a $k
	done
done