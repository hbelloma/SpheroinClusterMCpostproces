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
#include "esa_tools.C"
#include "DebugClassesMultESA2016.C"


#include "my_settings.C"
//#include <TGxis.h>
#include <iostream>

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


//root -l plotandextlowpt("EsBin7","png");
//void plotandextlowpt( const Char_t * type, TString suffix){
void plotandextlowpt( const Char_t * type= "EsBin9", TString suffix="PNG"){
//void plotandextlowpt( const Char_t * type="EsBin0", const Char_t * inFN1="inel/MeanPtVsNm_EsBin0.root",const Char_t * outDir="EsBin0", TString suffix="png",const char *outf="MeanPtVsNm_inelf.root"){


const Char_t * inFN1=Form("%s/MeanPtVsNm_%s.root",type,type);
const Char_t * outDir=Form("%s",type);
const char *outf=Form("%s/MeanPtVsNm_%sf.root",type,type);

CreateDir(outDir);
CreateDir(Form("%s",outDir));


TFile *f1 = TFile::Open(inFN1, "read");//outputdedx
if(!f1) {
        Printf("FATAL: File 1 doesn't exist");
        return;
}

TH1D* hPtmvsNm;
TH1D* hPtvsNm;


hPtmvsNm=(TH1D *)f1->Get(Form("hPtmvsNm_%s",type)); 
hPtvsNm=(TH1D *)f1->Get(Form("hPtvsNm_%s",type));

TH1D *hPtmvsNmnew=(TH1D *)hPtmvsNm->Clone("hPtmvsNm");
TH1D *hPtvsNmnew=(TH1D *)hPtvsNm->Clone("hPtvsNm");

hPtmvsNm->Fit("pol1","IM","",3,7);
hPtvsNm->Fit("pol1","IM2","",3,7);
TF1 *myfit = (TF1*) hPtmvsNm->GetFunction("pol1");
TF1 *myfit2 = (TF1*) hPtvsNm->GetFunction("pol1");

Double_t chis=myfit->GetChisquare();
Double_t chis2=myfit2->GetChisquare();
Int_t ndf=myfit->GetNDF();
Int_t ndf2=myfit->GetNDF();

Double_t a=myfit->Eval(1.5);
Double_t b=myfit->Eval(2.5);
Double_t a2=myfit->Eval(1.5);
Double_t b2=myfit->Eval(2.5);

Printf("a=%f, b=%f, chis=%f,ndf=%d",a,b, chis,ndf);
Printf("a=%f, b=%f, chis=%f,ndf=%d",a2,b2, chis2,ndf2);
Double_t cont=0;
Double_t cont2=0;

for(Int_t i=0; i<=hPtmvsNm->GetNbinsX(); i++){
  cont=hPtmvsNm->GetBinContent(i);
  cont2=hPtvsNm->GetBinContent(i);
  if(i==2){
   hPtmvsNmnew->SetBinContent(i,a);
   hPtvsNmnew->SetBinContent(i,a2);
  }
  else if(i==3){
   hPtmvsNmnew->SetBinContent(i,b);
   hPtvsNmnew->SetBinContent(i,b2);
  }
  else{
    hPtmvsNmnew->SetBinContent(i,cont);
    hPtvsNmnew->SetBinContent(i,cont2);
  }
}


  TCanvas* cmeanpt;
  TLegend* legmeanpt;
  cmanpt= new TCanvas(Form("cmeanpt%s",type),"THmeanpt",200,10,900,600);
  hPtmvsNm->SetMarkerStyle(24);
  hPtmvsNmnew->SetMarkerStyle(7);
  hPtvsNm->SetMarkerStyle(24);
  hPtvsNmnew->SetMarkerStyle(7);
  hPtmvsNm->SetMarkerColor(2);
  hPtmvsNmnew->SetMarkerColor(4);
  hPtvsNm->SetMarkerColor(8);
  hPtvsNmnew->SetMarkerColor(9);
  hPtmvsNm->Draw();
  hPtmvsNmnew->Draw("sames");
  hPtvsNm->Draw("sames");
  hPtvsNmnew->Draw("sames"); 




 TFile *fout = TFile::Open( outf,"RECREATE");
 fout->cd();
 hPtmvsNm->Write();
 myfit->Write();
 hPtmvsNmnew->Write();
 hPtvsNm->Write();
 myfit2->Write();
 hPtvsNmnew->Write();
 fout->Close();

}
