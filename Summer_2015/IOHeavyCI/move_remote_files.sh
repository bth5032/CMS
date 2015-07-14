# This script will create a file called "datacopy.sh" on all the servers listed in 
# SERVER_LIST that Matevz built for me. Then run the script on each server in 
# the list.   


SERVER_LIST="cabinet-7-7-0.t2.ucsd.edu
cabinet-7-7-10.t2.ucsd.edu
cabinet-7-7-11.t2.ucsd.edu
cabinet-7-7-16.t2.ucsd.edu
cabinet-7-7-17.t2.ucsd.edu
cabinet-7-7-19.t2.ucsd.edu
cabinet-7-7-3.t2.ucsd.edu
cabinet-7-7-8.t2.ucsd.edu
cabinet-7-7-4.t2.ucsd.edu
cabinet-7-7-5.t2.ucsd.edu
cabinet-7-7-6.t2.ucsd.edu
cabinet-7-7-7.t2.ucsd.edu
cabinet-7-7-9.t2.ucsd.edu"

for i in $SERVER_LIST; do scp datacopy.sh $i:/data3/xrootd; done

for server in $SERVER_LIST; do echo ssh -t $server /data3/xrootd/datacopy.sh ; done