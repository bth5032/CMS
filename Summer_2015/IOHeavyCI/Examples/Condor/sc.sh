# This script will print out the files which contain real test data or ignored
# test data (i.e. the output of jobs which did not land on slot 33) depending
# on command line arguments. If given "active" as the first arg, you get the 
# slot 33 results. If given "print" as the second argument, it prints the 
# contents of the file.

if [ $1 == "active" ]
then 
	for i in out* 
	do 
		if [ "`head -n1 $i`" == "ConcurrentReads:CondorSlot:VelocityMBps:BufferSize" ]
		then
			echo "file: " $i
			if [ $2 == "print" ]
			then
				cat $i
			fi
		fi
	done
fi
