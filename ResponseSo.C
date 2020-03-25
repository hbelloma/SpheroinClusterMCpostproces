#include <iostream>
#include <fstream>
#include <cmath>

#include "TGaxis.h"
#include <TH1D.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TProfile.h>
#include <TRandom.h>

#include <TCanvas.h>
#include <TList.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TMath.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <TASImage.h>
#include <TLine.h>
#include <TBox.h>
#include <TAxis.h>
#include <iostream>
#include <my_settings.C>

//--------------------------------
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
// caso 1.5
/*
void ResponseSo( const char *f1 ="SOpp13TeV_MERGE_ptmax1p5.root",const Char_t* ptmxn="1p5_", const Char_t* ptm="0.15<p_{T}<1.5 (GeV/c)",const     Char_t * outDir="SoResponse",TString suffix="pdf", const char *outf="SoResponse_ptmax1p5.root"   ){
*/
// caso ptmax=2
/*
void ResponseSo( const char *f1 ="SOpp13TeV_MERGE_ptmax2.root",const Char_t* ptmxn="2_", const Char_t* ptm="0.15<p_{T}<2 (GeV/c)",const Char_t * outDir="SoResponse",TString suffix="pdf", const char *outf="SoResponse_ptmax2.root"   ){
*/
// caso ptmax=5
/*
void ResponseSo( const char *f1 ="SOpp13TeV_MERGE_ptmax5.root",const Char_t* ptmxn="5_", const Char_t* ptm="0.15<p_{T}<5 (GeV/c)",const Char_t     * outDir="SoResponse",TString suffix="pdf", const char *outf="SoResponse_ptmax5.root"   ){
*/
// caso no ptmax
void ResponseSo( const char *f1 ="SOpp13TeV_MERGE_newbinsSOPCSO_PER0asDat.root",const Char_t* ptmxn="_", const Char_t* ptm="0.15<p_{T} (GeV/c)",const Char_t* outDir="SoResponse_10Sob100nchb_PER0asDat",TString suffix="png", const char *outf="SoResponse_noptmax_10Sob100nchb_PER0asDat.root"   ){

const Int_t Multmax=nMultbins-1;


CreateDir(outDir);
CreateDir(Form("%s",outDir));

 TFile *fin1 = TFile::Open(f1);
   if(!fin1)
   return;

// TFile* outFile = new TFile( outf, "RECREATE"); 
TFile* outFile = new TFile(  Form("%s/%s",outDir,outf), "RECREATE");        
const Int_t nmul= Multmax;

TH2D* RSO[nmul+1];
TH2D* RNSO[nmul+1];
TProfile* RNSO_pfx[nmul+1];
TH1D* HproyRSO1[nmul+1];
TH1D* HproyRSO2[nmul+1];
TH1D* HproyRSO3[nmul+1];
TH1D* HproyRSO4[nmul+1];
TH1D* HproyRSO5[nmul+1];
TH1D* HproyRSO6[nmul+1];
TH1D* HproyRSO7[nmul+1];
TH1D* HproyRSO8[nmul+1];
TH1D* HproyRSO9[nmul+1];
TH1D* HproyRSO10[nmul+1];

for(Int_t i=0; i<nmul+1; i++){
  RSO[i]=(TH2D*)fin1->Get(Form("h2newbins%d",i));
  RNSO[i]=(TH2D*)RSO[i]->Clone(Form("RNSO%d",i));
  HproyRSO1[i]=RSO[i]->ProjectionX(Form("HproyRSO1%d",i), 0, 1); 
  HproyRSO2[i]=RSO[i]->ProjectionX(Form("HproyRSO2%d",i), 1, 2);
  HproyRSO3[i]=RSO[i]->ProjectionX(Form("HproyRSO3%d",i), 2, 3);
  HproyRSO4[i]=RSO[i]->ProjectionX(Form("HproyRSO4%d",i), 3, 4);
  HproyRSO5[i]=RSO[i]->ProjectionX(Form("HproyRSO5%d",i), 4, 5);
  HproyRSO6[i]=RSO[i]->ProjectionX(Form("HproyRSO6%d",i), 5, 6);
  HproyRSO7[i]=RSO[i]->ProjectionX(Form("HproyRSO7%d",i), 6, 7);
  HproyRSO8[i]=RSO[i]->ProjectionX(Form("HproyRSO8%d",i), 7, 8);
  HproyRSO9[i]=RSO[i]->ProjectionX(Form("HproyRSO9%d",i), 8, 9);
  HproyRSO10[i]=RSO[i]->ProjectionX(Form("HproyRSO10%d",i), 9, 10);
}

Double_t IntRSObin[nmul+1]=0;
Int_t contRSObin[nmul+1]=0;

for(Int_t j=0; j<Multmax+1; ++j){
 for(Int_t binx=0; binx<nSobins+1; ++binx){ //40
  IntRSObin[j]= RSO[j]->Integral(binx,binx);
  if(IntRSObin[j]>0){
     for(Int_t biny=0; biny<nSobins+1; ++biny){
      contRSObin[j]=RSO[j]->GetBinContent(binx,biny);
      RNSO[j]->SetBinContent(binx,biny,contRSObin[j]/IntRSObin[j]); 
     }    
  }   
 }
RNSO_pfx[j]=RNSO[j]->ProfileX(Form("RNSO_pfx%d",j),0,40,"s"); 
}

TCanvas* cRSO[nMultbins+1];
  for(Int_t j=1; j<Multmax+1; ++j){
  cRSO[j]= new TCanvas(Form("cRSO%d",j),Form("TRSO%d",j),200,10,900,600);
  cRSO[j]->SetLogz();
  gStyle->SetOptStat(0);
  RNSO[j]->SetTitle(Form("S_{o} Response for %1.1f<Mult<%1.1f",Multbins[j],Multbins[j+1]));
  RNSO[j]->GetYaxis()->SetTitle(Form("S_{o} Rec (%s)",ptm));
  RNSO[j]->GetXaxis()->SetTitle(Form("S_{o} True (%s)",ptm));
  RNSO[j]->GetZaxis()->SetRangeUser(0.0001,1);
  //RNSO_pfx[j]->SetMarkerStyle(33); //7
  //RNSO_pfx[j]->SetFillColor(1);
  //RNSO_pfx[j]->SetFillStyle(0);//3001);
  //RNSO_pfx[j]->SetLineColor(1);

  RNSO[j]->Draw("colz");
  //RNSO_pfx[j]->Draw("same E2");
  cRSO[j]->SaveAs(Form("%s/cRSO%s%d.%s",outDir,ptmxn,j,suffix.Data()));
  }




for(Int_t j=1; j<Multmax+1; j++){
 Printf("%1.1f<Nch<%1.1f ------------", Multbins[j],Multbins[j+1]);
 for(Int_t i=0; i<nSobins; i++){
  RSO[j]->GetXaxis()->SetRangeUser(Sobins[i],Sobins[i+1]);
  RSO[j]->GetYaxis()->SetRangeUser(Sobins[i],Sobins[i+1]);
  Double_t meanx=RSO[j]->GetMean();
  Double_t meany=RSO[j]->GetMean(2);

  Printf("Rango So:   %1.1f<So<%1.1f, meanx=%f, meany=%f",Sobins[i],Sobins[i+1],meanx,meany);
 }
}
/*
TCanvas* cproy;
cproy=new TCanvas("cproy","Tcproy",200,10,900,600);
HproyRSO4[1]->Draw();
*/

//Double_t meanp=HproyRSO4[1]->GetMean();
//Printf("meanp=%d", meanp );


}
