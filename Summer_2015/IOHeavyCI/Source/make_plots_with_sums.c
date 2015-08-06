// This program is a root script which generates 
// plots from the data files created by running 
// data_generator.sh
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

#include <stdio.h>

const int BLIST[8] = {1024,2048,4096,8192,16384,32768,65536,131072};
const int YPOS[8] = {35,152,30,147,35,152,30,147};
void make_plots_with_sums(TString data_file, TString plot_name, TString header)
{
	//TApplication program = new TRInt(); 
	//pull in data
	TTree *t = new TTree(); 
	t->ReadFile(data_file);
	t->SetName("t");
	
	//Vars for painting labels
	float sum = 0;
	char *print_sum = (char *) malloc(30);
	
	
	//TString name = "run2.png";
	TCanvas *BG = new TCanvas("c1", "Read Velocity on Local Disk for CMS3 Files", 1920, 1080);
	BG->cd();
	TPad *c = new TPad("MainPad", "My main pad", 0, 0, 1, 0.9);
	c->Draw();
	c->Divide(2,2);

	//In first slot have Time vs. Buffer for 1 Concurrent Read
	c->cd(1);
	int n1 = t->Draw("VelocityMBps:BufferSize", "ConcurrentReads==1", "goff");
	TGraph *ghist1 = new TGraph(n1, t->GetV2(), t->GetV1());	
	ghist1->SetName("ghist1");
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
	ghist2->SetName("ghist2");
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
	ghist3->SetName("ghist3");
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
	ghist4->SetName("ghist4");
	ghist4->SetMarkerColor(1);
	ghist4->SetTitle("10 Concurrent Reads");
	ghist4->GetXaxis()->SetTitle("Buffer Size (Bytes)");
	ghist4->GetYaxis()->SetTitle("Read Velocity (MB/s)");
	ghist4->Draw("ap");
	
	//Draw to screen
	
	//Draw sums:
	c->cd(1);
	double DP1x[n1];
	double DP1y[n1];
	TLegend* leg1 = new TLegend(0.85,0.15,1,.9);
	leg1->AddEntry((TObject*)0, "Net Speeds", "");
	
	for(int j=0; j<8;j++)
	{	
		//int x_loc = 0;
		for(int i=0; i<n1;i++)
		{
			ghist1->GetPoint(i, DP1x[i], DP1y[i]);
			
			if (BLIST[j] == DP1x[i])
			{
				sum = sum + DP1y[i];
			}		
		}
		//cout<<"Sum of Buffer Size "<<BLIST[j]<<" is "<<sum<<"\n";
		sprintf(print_sum, "%i -- %.0f", BLIST[j], sum);
		leg1->AddEntry((TObject*)0, print_sum, "");
		sum=0;
	}
	leg1->Draw();
	
	c->cd(2);
	double DP2x[n2];
	double DP2y[n2];
	TLegend* leg2 = new TLegend(0.85,0.15,1,.9);
	leg2->AddEntry((TObject*)0, "Net Speeds", "");
	
	for(int j=0; j<8;j++)
	{	
		//int x_loc = 0;
		for(int i=0; i<n2;i++)
		{
			ghist2->GetPoint(i, DP2x[i], DP2y[i]);
			
			if (BLIST[j] == DP2x[i])
			{
				sum = sum + DP2y[i];
			}		
		}
		//cout<<"Sum of Buffer Size "<<BLIST[j]<<" is "<<sum<<"\n";
		sprintf(print_sum, "%i -- %.0f", BLIST[j], sum);
		leg2->AddEntry((TObject*)0, print_sum, "");
		sum=0;
	}
	leg2->Draw();
	
	c->cd(3);
	double DP3x[n3];
	double DP3y[n3];
	TLegend* leg3 = new TLegend(0.85,0.15,1,.9);
	leg3->AddEntry((TObject*)0, "Net Speeds", "");
	
	for(int j=0; j<8;j++)
	{	
		//int x_loc = 0;
		for(int i=0; i<n3;i++)
		{
			ghist3->GetPoint(i, DP3x[i], DP3y[i]);
			
			if (BLIST[j] == DP3x[i])
			{
				sum = sum + DP3y[i];
			}		
		}
		//cout<<"Sum of Buffer Size "<<BLIST[j]<<" is "<<sum<<"\n";
		sprintf(print_sum, "%i -- %.0f", BLIST[j], sum);
		leg3->AddEntry((TObject*)0, print_sum, "");
		sum=0;
	}
	leg3->Draw();
	
	c->cd(4);
	double DP4x[n4];
	double DP4y[n4];
	TLegend* leg4 = new TLegend(0.85,0.15,1,.9);
	leg4->AddEntry((TObject*)0, "Net Speeds", "");
	
	for(int j=0; j<8;j++)
	{	
		//int x_loc = 0;
		for(int i=0; i<n4;i++)
		{
			ghist4->GetPoint(i, DP4x[i], DP4y[i]);
			
			if (BLIST[j] == DP4x[i])
			{
				sum = sum + DP4y[i];
			}		
		}
		//cout<<"Sum of Buffer Size "<<BLIST[j]<<" is "<<sum<<"\n";
		sprintf(print_sum, "%i -- %.0f", BLIST[j], sum);
		leg4->AddEntry((TObject*)0, print_sum, "");
		sum=0;
	}
	leg4->Draw();
	
	//Initialize Canvas
	
	c->cd(0);
	c->Draw();
	
	BG->cd();
	TText *title = new TText(.5,.95, header);
	title->SetTextAlign(22);
	title->Draw();
	
	gDirectory->Add(ghist1);
	gDirectory->Add(ghist2);
	gDirectory->Add(ghist3);
	gDirectory->Add(ghist4);
	gDirectory->Add(t);
	gPad->SaveAs(plot_name);
}

/*float calculateVelocities(TH2F hist){
	
}*/