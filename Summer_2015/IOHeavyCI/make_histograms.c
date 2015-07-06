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
	TTree *t = new TTree(); 
	t->ReadFile(data_file);
	
	//TString name = "run2.png";
	TCanvas *c = new TCanvas("c1", "Read Velocity on Local Disk for CMS3 Files", 1920, 1080);
	c->Divide(2,2);

	//In first slot have Time vs. Buffer for 1 Concurrent Read
	c->cd(1);
	int n1 = t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==1", "goff");
	TGraph *ghist1 = new TGraph(n1, t->GetV2(), t->GetV1());
	ghist1->SetMarkerStyle(3);
	ghist1->SetMarkerColor(1);
	ghist1->SetTitle("Single File Read");
	ghist1->GetXaxis()->SetTitle("Buffer Size (Bytes)");
	ghist1->GetYaxis()->SetTitle("Read Velocity (MB/s)");
	ghist1->Draw("ap");
	
	//In second slot have Time vs. Buffer for 3 Concurrent Reads
	c->cd(2);
	int n2 = t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==3", "goff");
	TGraph *ghist2 = new TGraph(n2, t->GetV2(), t->GetV1());
	ghist2->SetMarkerStyle(3);
	ghist2->SetMarkerColor(1);
	ghist2->SetTitle("3 Concurrent Reads");
	ghist2->GetXaxis()->SetTitle("Buffer Size (Bytes)");
	ghist2->GetYaxis()->SetTitle("Read Velocity (MB/s)");
	ghist2->Draw("ap");
	
	//In third slot have Time vs. Buffer for 3 Concurrent Reads
	c->cd(3);
	int n3 = t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==6", "goff");
	TGraph *ghist3 = new TGraph(n3, t->GetV2(), t->GetV1());
	ghist3->SetMarkerStyle(3);
	ghist3->SetMarkerColor(1);
	ghist3->SetTitle("6 Concurrent Reads");
	ghist3->GetXaxis()->SetTitle("Buffer Size (Bytes)");
	ghist3->GetYaxis()->SetTitle("Read Velocity (MB/s)");
	ghist3->Draw("ap");
	
	//In fourth slot have Time vs. Buffer for 10 Concurrent Reads
	c->cd(4);
	int n4 = t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==10", "goff");
	TGraph *ghist4 = new TGraph(n4, t->GetV2(), t->GetV1());
	ghist4->SetMarkerStyle(3);
	ghist4->SetMarkerColor(1);
	ghist4->SetTitle("10 Concurrent Reads");
	ghist4->GetXaxis()->SetTitle("Buffer Size (Bytes)");
	ghist4->GetYaxis()->SetTitle("Read Velocity (MB/s)");
	ghist4->Draw("ap");
	
	//Draw to screen
	//Initialize Canvas
	
	c->cd(0);
	
	gPad->SaveAs(plot_name);
}

/*float calculateVelocities(TH2F hist){
	
}*/