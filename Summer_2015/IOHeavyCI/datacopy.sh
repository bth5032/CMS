DATA_DIR=/nfs-7/userdata/matevz/Run2012D/DoubleMu/AOD/16Jan2013-v2/10000

i=3
for x in `ls $DATA_DIR/*.root`
do
	if [ $i -le 14 ]
	then
		dd if=$x of=/data$i/xrootd/trimmed_infile_$i bs=1000000 count=2000 &
		i=$(($i + 1))
	fi
done
