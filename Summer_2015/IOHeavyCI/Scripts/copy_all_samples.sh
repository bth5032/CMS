#Takes in one argument, the path to the file which contains the tab seperated
#list of (SAMPLE_NAME, PATH) pairs. Then goes through each line, copying the 
#the sample into the proper disks/directories with symbolic links as explained below.

while read -r name path
do 
	#Make the top level directories on the machine
	for disc in `seq 3 14`
	do 
		mkdir /data$disc/xrootd/SABM/$name
	done

#This loop reads in every file from the path
#and then copies them one by one into the 
#available SABM folders. It attempts to 
#spread the files out as much as possible by
#by copying each new file to it's own disk 
#modulo the number available
#Make the top level directories

	i=3  
	for file in `ls $path/*.root`
	do
		if [ $i -gt 14 ]
		then
			i=3
		fi
		
		if cp $file /data$i/xrootd/SABM/$name
		then
			pass
		else
			i=$(($i + 1))
		fi 
		
		if [[ $i -ne 3 ]]
		then 
			ln -s /data$i/xrootd/SABM/$name/`basename $file` /data3/xrootd/SABM/$name/`basename $file`
		fi
		
		i=$(($i + 1))
	done
done <$1