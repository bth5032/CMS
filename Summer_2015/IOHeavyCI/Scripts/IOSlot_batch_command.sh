## This simple script runs whatever peice of code you
## write in the ' ' on every IOSlot machine 

for server in `cat ../.list_of_IOSlot_nodes`
do
	ssh -T $server 'for i in 3 4 5 6 7 8 9 10 11 12 13 14; do mkdir /data$i/xrootd/SABM/ttbar_powheg_pythia8_25ns; done'
done