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
#include "my_settings.C"

void CreateDir(const Char_t* dirName)
{
   TString pwd(gSystem->pwd());
   gSystem->cd(pwd.Data());

   if(gSystem->cd(dirName)) {
   gSystem->cd(pwd.Data());
   } else {
   gSystem->mkdir(dirName, kTRUE); // kTRUE means recursive
   }
}


void GetSoIntervals( const Char_t * inFileName1="SOpp13TeV_MERGE_newbinsSOPCSO_PER0asDat.root",const Char_t * outDir="SopcSo", TString suffix="png" ){

CreateDir(outDir);
CreateDir(Form("%s",outDir));

//const Int_t nSobins = 10;
//Double_t Sobins[nSobins+1] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
//const Int_t nMultbins = 13;
//Double_t Multbins[nMultbins+1]={ 0.0, 1.0, 4.0, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0, 50.0, 60.0, 70.0, 140.0 };

TFile *fin1 = TFile::Open(inFileName1);
if(!fin1)
   return;

TFile* outFile = new TFile("SoIntervals_Per0asdat_100Nchbins.root", "RECREATE");

const Int_t nchbins= nMultbins-1; 

TH2D* HSOPCSO[nchbins+1];
TH1D* HpSOPCSO[nchbins+1];

TH1D* hnewbins[nchbins+2];
TH2D* h2newbins[nchbins+2];
//Double_t SobinsMRsopc[nSobins+1]=0;

for(Int_t i=0; i<nchbins+1; i++){
  HSOPCSO[i]=(TH2D*)fin1->Get(Form("hSompercVsSom%d",i));
//  HpSOPCSO[i]=new TH1D(Form("hpSompercVsSom%d",i), "", nSobins, Sobins); 
  HpSOPCSO[i]=HSOPCSO[i]->ProjectionY(Form("HproSOPCSO%d",i),1,1000);

}



Double_t SobinsMRsopc[nSobins+1]=0; //nSobins
for(Int_t i=0; i<nchbins+1; i++){// nchbins+1; i++){
  Printf("----------------------i=%d\n",i);
  Double_t Sommax=0;
  Double_t Sommin=0;
  for(Int_t y=1; y<nSobins+1; y++){
    SobinsMRsopc[y]=0;
    Printf("=======y=%d\n",y);
    Int_t consopcso=0;;
    for(Int_t j=1; j<1000+1; j++){
      consopcso=HSOPCSO[i]->GetBinContent(j,y); 
      if(j==1) Sommin=Sommax;
      if(consopcso>0){
          Sommax=j*0.001;
      }
    }
    
 // Printf("....Sommin=%f,Sommax=%f\n",Sommin,Sommax);
  if(y==nSobins) Sommax=1;
  SobinsMRsopc[y]=Sommax;
  Printf("....Sommin=%f,Sommax=%f\n",Sommin,Sommax);
  }
  Printf("declaring histos");
  hnewbins[i] = new TH1D(Form("hnewbins%d",i),"",nSobins,SobinsMRsopc);
  h2newbins[i] = new TH2D(Form("h2newbins%d",i),"",nSobins,SobinsMRsopc,nSobins,SobinsMRsopc);
  for(Int_t y=1; y<nSobins+1; y++){ //nSobins
     Printf("filling %d bin content",y);
     hnewbins[i]->SetBinContent(y,y);
//     h2newbins[i]->SetBinContent(y,y,0);
  }
}
 

/* 
  TCanvas* cSopcSo[nchbins+1]; 
  for(Int_t j=0; j<nchbins+1; ++j){
  cSopcSo[j]= new TCanvas(Form("cSopcSo%d",j),Form("THSopcSo%d",j),200,10,900,600);
  //cSopcSo[j]->SetLogx();
  cSopcSo[j]->SetLogz();
  gStyle->SetOptStat(0);
  HSOPCSO[j]->SetTitle(Form("So_{m} vs Sopc_{m} for %1.1f<Mult<%1.1f",Multbins[j],Multbins[j+1]));
  HSOPCSO[j]->GetYaxis()->SetTitle("Sopc_{m} (|eta|<0.8)");
  HSOPCSO[j]->GetXaxis()->SetTitle("So_{m} (|eta|<0.8)");
  HSOPCSO[j]->GetXaxis()->SetRangeUser(0,1);
  HSOPCSO[j]->Draw("colz"); 
  cSopcSo[j]->SaveAs(Form("%s/SopcSo%d.%s",outDir,j,suffix.Data()));
  }


  TCanvas* cSopcSop[nchbins+1]; 
  for(Int_t j=0; j<nchbins+1; ++j){
    cSopcSop[j]= new TCanvas(Form("cSopcSop%d",j),Form("THSopcSop%d",j),200,10,900,600);
    cSopcSop[j]->SetLogy();
    HpSOPCSO[j]->SetTitle(Form("Sopc_{m} for %1.1f<Mult<%1.1f",Multbins[j],Multbins[j+1]));
    HpSOPCSO[j]->GetYaxis()->SetTitle("Entries");
    HpSOPCSO[j]->GetXaxis()->SetTitle("Sopc_{m} (|eta|<0.8)");
    HpSOPCSO[j]->GetYaxis()->SetRangeUser(100,1000000);
    HpSOPCSO[j]->Draw(); 
    cSopcSop[j]->SaveAs(Form("%s/SopcSop%d.%s",outDir,j,suffix.Data()));
  }
*/


   outFile->cd();  
   for(Int_t j=0; j<nchbins+1; ++j){
     HSOPCSO[j]->Write();
     HpSOPCSO[j]->Write();
     hnewbins[j]->Write();
     h2newbins[j]->Write();
   }
   outFile->Close();


}
