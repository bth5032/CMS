# This program extracts the locations of hadoop blocks from the output 
# of a hadoop fsck over multiple files by explioting the structure of
# the output. It works for hadoop 2.0.
# You must generate the file named 'locations' by running the command: 
# for name in LIST_OF_FILES_IN_HADOOP_FUSE_FS; do hdfs fsck $name -files -blocks -locations; done > locations	
# where the name in X syntax is a list of the files whose locations you want to find. 
#
# For the purpose of personal re-usablilty, the particular command I ran was:
# for name in `ls /hadoop/cms/store/user/matevz/IOHeavyCI/trimmed_infile_*`; do hdfs fsck ${name:7} -files -blocks -locations ; done > ~/locations
#
# This was written by Bobak Hashemi at UCSD on June 30 2015
#  
# 

myfile = open("locations", "r")

servers = []

for line in myfile:
	x = line.split("repl=2")
	if len(x) > 1:
		if not (x[1][2:17] in servers):
			servers.append(x[1][2:17])
		if not (x[1][25:40] in servers):
			servers.append(x[1][25:40])	

for x in servers:
	print(x)

