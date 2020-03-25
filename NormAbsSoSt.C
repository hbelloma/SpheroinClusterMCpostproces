#include <TFile.h>
#include <TList.h>
#include <TTree.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TObjString.h>
#include <TString.h>
#include <TROOT.h>
#include <TMath.h>
#include <TH2D.h>
#include <TProfile.h>
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include <string>
#include <my_settings.C>

void NormAbsSoSt( const Char_t * inFileName1="SOpp13TeV_MERGE_newbinsSOPCSOEQSo_PER0.root",  const Char_t * inFileName2="SOpp13TeV_MERGE_newbinsSOPCSOEQSo_PER0.root"){


  TFile *fin1 = TFile::Open(inFileName1);
  TFile *fin2 = TFile::Open(inFileName2);
  if(!fin1)
   return;
  if(!fin2)
   return;

TFile* outFile = new TFile("HistPercPP13000_PER0asdatai_test.root", "RECREATE");
const Int_t npc= nMultbins-1; // last was 12

TH1D* histSOM[npc+1];
TH1D* histSOT[npc+1];
TH1D* histSTM[npc+1];
TH1D* histSTT[npc+1];

/*
TH1D* hSOM[npc+1];
TH1D* hSOT[npc+1];
TH1D* hSTM[npc+1];
TH1D* hSTT[npc+1];
*/

Printf("loop npc");
for(Int_t i=0; i<npc+1; i++){
   histSOT[i]=(TH1D*)fin1->Get(Form("hSOT%d",i));
   histSTT[i]=(TH1D*)fin2->Get(Form("hSTT%d",i));
   histSOM[i]=(TH1D*)fin1->Get(Form("hSOM%d",i));
   histSTM[i]=(TH1D*)fin2->Get(Form("hSTM%d",i));
}

TH1F* hSOT[npc+1];
TH1F* hSTT[npc+1];
TH1F* hSOM[npc+1];
TH1F* hSTM[npc+1];

for(Int_t i=0; i<npc+1; i++){
  hSOT[i]= new TH1F(Form("hSOTPerc%d",i),";;", 1000,0,1);
  hSTT[i]= new TH1F(Form("hSTTPerc%d",i),";;", 1000,0,1);
  hSOM[i]= new TH1F(Form("hSOMPerc%d",i),";;", 1000,0,1); 
  hSTM[i]= new TH1F(Form("hSTMPerc%d",i),";;", 1000,0,1);
}


printf("out of loop npc");

Int_t binstot =1000;// histSOT[9]->GetXaxis()->GetNbins();
printf("binstot=%d",binstot);

Double_t intehistSOT[npc+1]=0;
Double_t conthistSOT[npc+1]=0.0;
Double_t contSOT[npc+1]=0;

Double_t intehistSTT[npc+1]=0;
Double_t conthistSTT[npc+1]=0.0;
Double_t contSTT[npc+1]=0;

Double_t intehistSOM[npc+1]=0;
Double_t conthistSOM[npc+1]=0.0;
Double_t contSOM[npc+1]=0;

Double_t intehistSTM[npc+1]=0;
Double_t conthistSTM[npc+1]=0.0;
Double_t contSTM[npc+1]=0;

Double_t intehistSOTt[npc+1]=0;
Double_t intehistSTTt[npc+1]=0;
Double_t intehistSOMt[npc+1]=0;
Double_t intehistSTMt[npc+1]=0;

printf("entrando  loop\n");
// /*
for(Int_t i=0; i<npc+1; i++){
  printf("i=%d",i);
  intehistSOTt[i]=histSOT[i]->Integral(1,binstot+1);
  intehistSTTt[i]=histSTT[i]->Integral(1,binstot+1);
  intehistSOMt[i]=histSOM[i]->Integral(1,binstot+1);
  intehistSTMt[i]=histSTM[i]->Integral(1,binstot+1);
  Printf("intehistSOMt=%1.1f", intehistSOMt[i]);
 for(Int_t bin=1; bin<binstot+1; bin++){
   intehistSOT[i]=histSOT[i]->Integral(1,bin+1);
   conthistSOT[i]=histSOT[i]->GetBinContent(bin);
   intehistSTT[i]=histSTT[i]->Integral(1,bin+1);
   conthistSTT[i]=histSTT[i]->GetBinContent(bin); 
   intehistSOM[i]=histSOM[i]->Integral(1,bin+1);
   conthistSOM[i]=histSOM[i]->GetBinContent(bin); 
   intehistSTM[i]=histSTM[i]->Integral(1,bin+1);
   conthistSTM[i]=histSTM[i]->GetBinContent(bin); 
   //printf("intehistSOT=%d, conthistSOT=%f\n",intehistSOT[9],conthistSOT[9]);
  // printf("SOT\n");
   if(i>0){ 
     //contSOT[i]=conthistSOT[i]/intehistSOT[i];
     contSOT[i]=intehistSOT[i]/intehistSOTt[i];
     //printf("contSOT=%f\n",contSOT[i]);
     hSOT[i]->SetBinContent(bin,contSOT[i]);
   }
   else hSOT[i]->SetBinContent(bin,0);
  // printf("STT\n"); 
   if(i>0){
     //contSTT[i]=conthistSTT[i]/intehistSTT[i];
     contSTT[i]=intehistSTT[i]/intehistSTTt[i];
     hSTT[i]->SetBinContent(bin,contSTT[i]);
   }
   else hSTT[i]->SetBinContent(bin,0);

  // printf("SOM\n");
   if(intehistSOMt[i]>0){
     //contSOM[i]=conthistSOM[i]/intehistSOM[i];
     contSOM[i]=intehistSOM[i]/intehistSOMt[i];
//     printf("i=%d, contSOM=%f\n",i,contSOM[i]); 
     hSOM[i]->SetBinContent(bin,contSOM[i]);
   }
   else hSOM[i]->SetBinContent(bin,0);

  // printf("STM\n");
   if(intehistSTMt[i]>0){
    // contSTM[i]=conthistSTM[i]/intehistSTM[i];
     contSTM[i]=intehistSTM[i]/intehistSTMt[i];
     hSTM[i]->SetBinContent(bin,contSTM[i]);
   }
   else hSTM[i]->SetBinContent(bin,0);
   
 }
}
// */

TCanvas* ceta;
ceta = new TCanvas("ceta","THETA",200,10,900,600);
hSOT[9]->Draw();
//histSOM[9]->Draw();
//histSOT[9]->Draw();
//histSTT[9]->Draw();
//hSOT[9]->Draw("sames");
//histSTM[1]->Draw();

outFile->cd();
for(Int_t i=0; i<npc+1; i++){
  hSOT[i]->Write();
}
for(Int_t i=0; i<npc+1; i++){
  hSOM[i]->Write();
}
for(Int_t i=0; i<npc+1; i++){
  hSTT[i]->Write();
}
for(Int_t i=0; i<npc+1; i++){
  hSTM[i]->Write();
}
outFile->Close();

}
