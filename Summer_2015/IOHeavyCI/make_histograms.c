// This program is a root script which generates 
// histograms from the data files created by running 
// data_generator.sh on UAF-4.t2.ucsd.edu
// It was written on June 26 2105 by Bobak Hashemi 
// using the liberal assistance of Matevz Tadel
//
//
//

/*#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TRint.h"
#include <time.h>
#include <stdio.h>

const short MaxNN = 6;
*/
void make_histograms(TString data_file, TString plot_name)
{
	//TApplication program = new TInt 
	//pull in data
	TTree *t;
	t = new TTree(); 
	t->ReadFile(data_file);
	//TString name = "run2.png";
		
	//Initialize Canvas
	TCanvas *c = new TCanvas("c1", "Read Velocity on Local Disk for CMS3 Files", 1920, 1080);
	c->Divide(2,2);
	
	//In first slot have Time vs. Buffer for 1 Concurrent Read
	c->cd(1);
	t->SetMarkerStyle(3);
	t->SetMarkerColor(1);
	t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==1");
	
	
	//In second slot have Time vs. Buffer for 3 Concurrent Reads
	c->cd(2);
	t->SetMarkerStyle(3);
	t->SetMarkerColor(2);
	t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==3");
	
	//In third slot have Time vs. Buffer for 3 Concurrent Reads
	c->cd(3);
	t->SetMarkerStyle(4);
	t->SetMarkerColor(1);
	t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==6");
	
	//In fourth slot have Time vs. Buffer for 10 Concurrent Reads
	c->cd(4);
	t->SetMarkerStyle(4);
	t->SetMarkerColor(2);
	t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==10");
	
	
	c->cd(0);
	
	gPad->SaveAs(plot_name);
}

/*float calculateVelocities(TH2F hist){
	
}*/