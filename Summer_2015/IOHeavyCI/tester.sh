#!/bin/bash

for k in `seq 1 10`; do
	for j in {128 256 512 1024 4096 8192}; do
		echo "Drop Cache Command"
		for i in `seq 1 $k`; do
		#sync && echo 3 > /proc/sys/vm/drop_caches
		#Command above works for ultrabook

		#/nfs-7/t2tas/drop_cache
			echo "$k:reader -f InFile_$i -b $j"   
		done
	done
done
