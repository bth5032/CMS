# This ROOT script will extract from a data file of the standard format
# used during this testing, all events which have the same values for
# the (ConcurrentReads, BufferSize) combination. Using those data, it 
# constructs a 1D histogram (which we expect to be a discrete gaussian)
# of the data and saves those files to disk. It was written on 
# July 23 2015 by Bobak Hashemi in the lab of Frank Wuerthwein at UCSD.

from ROOT import TTree, TCanvas, TGraph, gPad, TH1F
import sys, itertools, time

bufferList = [1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072]
numReadsList = [1, 3, 6, 10]

#bufferList = [32768]
#numReadsList = [10]

def drawNext(allData, b, r): 
	"""This function creates a new TH1F and fills it with the data
	corresponding to the next buffer/read combination and returns it."""
	
	constraints = "BufferSize== %i && ConcurrentReads== %i " % (b, r)
	BG = TCanvas("c1", "Read Velocity on Local Disk for root Files", 1920, 1080)
	hist = TH1F("hist", "", 40, 0, 200)
	
	numPoints = allData.Draw("VelocityMBps>>hist", constraints, "goff")
	
	hist.SetTitle("%s Concurrent Reads with %s Byte Buffer" % (r, b) )
	hist.SetXTitle("Read Velocity (MB/s)")
	hist.Draw()
	gPad.SaveAs("b%sr%s.png" % (b, r) );
	#time.sleep(100)
	
def makeGaussians(data_file):
	#Pull in Data
	allData = TTree()
	allData.ReadFile(data_file)
	#allData.GetXaxis().SetTitle("Read Velocity (MB/s)")

	for (buf, reads) in itertools.product(bufferList, numReadsList):
		drawNext(allData, buf, reads)


makeGaussians(sys.argv[1])
