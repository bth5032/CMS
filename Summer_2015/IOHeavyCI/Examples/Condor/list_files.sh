## This script will list all the contents of /data*/xrootd
## on the machines listed in cab-7. This was used to make 
## sure the datafiles were moved over by the move_remote_files script

for servername in `cat cab-7`
do
	echo "Server ----- $servername"
	ssh -t $servername ls /data*/xrootd
	echo
	echo
done