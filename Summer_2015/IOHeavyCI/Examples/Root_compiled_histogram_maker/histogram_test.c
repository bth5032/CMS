// This program provides an example compilable Root
// script. It was written by Bobak Hashemi on 
// June 25 2105 with much help from Matevz Tadel 
// at UCSD in the lab of Frank Wuerthwein
//
//

#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TRint.h"
#include <time.h>
#include <stdio.h>

const short MaxNN = 6;

int main(int argc, char** argv)
{
	//TApplication *app=new TApplication("name", &argc, argv);
	
	TTree *t;
	t = new TTree(); 
	t->ReadFile("tree_input");
	t->Print();
	t->Draw("Gops");
	t->Draw("Gops:Time");
	
	gPad->SaveAs("xxx.png");
	
	
	//app->Run();
	/*t->Draw("Gops:Time","","lego3");
	t->Draw("Gops:Time","","lego2");
	t->Draw("Gops:Time","","surf"); 
	sleep(2);*/
	return 1;
}