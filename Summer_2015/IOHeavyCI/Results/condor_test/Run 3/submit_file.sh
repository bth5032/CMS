if [ "slot33" == $_CONDOR_SLOT ]
then 
	echo ConcurrentReads:CondorSlot:VelocityMBps:BufferSize
	for k in 1 3 6 10; do
		for j in 1024 2048 4096 8192 16384 32768 65536 131072; do
			/nfs-7/t2tas/drop_cache
			for i in `seq 3 $(($k+2))`; do
				/nfs-7/t2tas/reader -f /data$i/xrootd/trimmed_infile_$i -b $j -a "$k    $_CONDOR_SLOT" &   
			done
			wait
		done
	done
	sleep 600
else
	echo "--Ignored Slot--"
	#sleep 600 
	echo `uname -n` : $_CONDOR_SLOT
fi
