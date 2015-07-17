# This script probes the output of submit_file.sh
# passing "ignored" will read files which did not 
# land on slot 33, whereas  

lineOne="ConcurrentReads:CondorSlot:VelocityMBps:BufferSize"
 
if [[ $1 == "ignored" ]]
then 
	lineOne="--Ignored Slot--"
	echo "Printing Ignored Data Files"
else
	echo "Printing Slot 33 Active Data Files"
fi

for i in out* 
do 
	if [[ "`head -n1 $i`" == $lineOne ]] || [[ "`head -n2 $i | tail -n1`" == $lineOne ]]
	then
		echo "file: " $i
		if [[ $2 == "print" ]]
		then
			cat $i
		fi
	fi
done

