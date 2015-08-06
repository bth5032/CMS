# This ROOT script will extract from a data file of the standard format
# used during this testing, all events which have the same values for
# the (ConcurrentReads, BufferSize) combination. Using those data, it 
# constructs a 1D histogram (which we expect to be a discrete gaussian)
# of the data and saves those files to disk. It was written on 
# July 23 2015 by Bobak Hashemi in the lab of Frank Wuerthwein at UCSD.

from ROOT import TTree, TCanvas, TGraph, gPad, TPad, TText
import sys, itertools, time

bufferList = [1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072]
numReadsList = [1, 3, 6, 10]
RObjs = {}

def drawTitle(text):
	'''Takes in the title text and draws it to the top of the current pad'''
	headerText = TText(.5,.95, text)
	headerText.SetTextAlign(22)
	headerText.Draw()
	
	return headerText
	
def drawNext(reads):
	"""This function creates a new TGraph and fills it with the data
	corresponding to the next buffer/read combination then returns it."""
	constraints = "ConcurrentReads==%i" % reads
	
	numPoints = allData.Draw("VelocityMBps:BufferSize", constraints, "goff")
	
	v2=allData.GetV2()
	v1=allData.GetV1()
	
	graph = TGraph(numPoints, v2, v1)
	
	graph.SetTitle("%i Concurrent Reads" % reads)
	graph.SetXTitle("Read Velocity (MB/s)")
	graph.Draw("ap")
	return graph


##### Begin Main Scriping #####
	
#Pull in Data
data_file = sys.argv[1]
allData = TTree()
allData.ReadFile(data_file)

#Set title equal to default value if none given
title = sys.argv[2] if len(sys.argv) == 3 else "Read Velocity on Local Disk for root Files"

#Create Background Canvas
BG = TCanvas("BG", title, 1920, 1080)
'''RObjs['headerText'] = drawTitle(title)

#Create pad to hold all plots.
body = TPad("MainPad", "My main pad", 0, 0, 1, 0.9)
body.Draw()
halfSize = (int) (len(numReadsList)/2)
body.Divide(halfSize,halfSize)

i=1
for reads in numReadsList:
	body.cd(i)
	RObjs["graph%i" %i] = drawNext(reads)
	i+=1
'''
constraints = "ConcurrentReads==%i" % 6
	
numPoints = allData.Draw("VelocityMBps:BufferSize", constraints, "goff")

v2=allData.GetV2()
v1=allData.GetV1()


print("not broken")
graph = TGraph(numPoints, v2, v1)
print("did we break yet?")

graph.SetTitle("%i Concurrent Reads" % reads)
graph.SetXTitle("Read Velocity (MB/s)")
graph.Draw("ap")

BG.SaveAs("%s.png" % data_file.split('.output')[0]);

