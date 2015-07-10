#!/bin/bash

echo ConcurrentReads:FileID:VelocityMBps:BufferSize
for trial in `seq 1 100`; do
	for k in 1 3 6 10; do
		for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
			../drop_cache
			for i in `seq 1 $k`; do
				./reader -f /data$i/xrootd/trimmed_infile_$i -b $j -a $k\ \ \ \ $i &   
			done
			wait
		done
	done
done