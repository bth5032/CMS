## This simple script runs whatever peice of code you
## write in the ' ' on every IOSlot machine 

for server in `cat ../.list_of_IOSlot_nodes`
do
	sh -T $server "bash -s"
done