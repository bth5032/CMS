#This script takes in the path to a list of samples on hadoop (from sample.dat) and copies them onto the 
#the disks /data$i for 3<=$i<=14. 


path='/hadoop/cms/store/group/snt/run2_25ns/TT_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/V07-04-03'

i=3

#This loop reads in every file from the path
#and then copies them one by one into the 
#available SABM folders. It attempts to 
#spread the files out as much as possible by
#by copying each new file to it's own disk 
#modulo the number available
  
for file in `ls $path/*.root`
do
	if [ $i -gt 14 ]
	then
		i=3
	fi
	
	cp $file /data$i/xrootd/SABM
	
	if [[ $i -ne 3 ]]
	then 
		ln -s /data$i/xrootd/SABM/`basename $file` /data3/xrootd/SABM/`basename $file`
	fi
	
	i=$(($i + 1))
done