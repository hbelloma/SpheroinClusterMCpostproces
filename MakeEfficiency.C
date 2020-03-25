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

void MakeEfficiency( const char *f1 ="SOpp13TeV_MERGE_newbinsSOPCSO_EPOS4corr.root", const Char_t * outDir="Efficiencypt", TString suffix="png", const char *outfile="EfficiencyPerc10_EPOS.root"){


CreateDir(outDir);
CreateDir(Form("%s",outDir));


//const Int_t nSobins = 10;
//Double_t Sobins[nSobins+1] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
//Double_t Sobinspc[nSobins+1] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };


//const Char_t * eta_for_pt = "|#eta|<0.8";

TFile *Rf1 = TFile::Open(f1, "read");//outputdedx
if(!Rf1) {
        Printf("FATAL: File 1 doesn't exist");
        return;
}

TH1D* hOutAll;
TH1D* hOutAllnp;

TH1D* hInAll;
//TH1D* hSecAll;
TH1D* hMcSecAll;

TH1D* hOutMult[nMultbins+1];
TH1D* hOutMultnp[nMultbins+1];
TH1D* hInMult[nMultbins+1];


TH1D* hOutES0Mult[nMultbins+1];
TH1D* hInES0Mult[nMultbins+1];
TH1D* hOutES1Mult[nMultbins+1];
TH1D* hInES1Mult[nMultbins+1];
TH1D* hOutES2Mult[nMultbins+1];
TH1D* hInES2Mult[nMultbins+1];
TH1D* hOutES3Mult[nMultbins+1];
TH1D* hInES3Mult[nMultbins+1];
TH1D* hOutES4Mult[nMultbins+1];
TH1D* hInES4Mult[nMultbins+1];
TH1D* hOutES5Mult[nMultbins+1];
TH1D* hInES5Mult[nMultbins+1];
TH1D* hOutES6Mult[nMultbins+1];
TH1D* hInES6Mult[nMultbins+1];
TH1D* hOutES7Mult[nMultbins+1];
TH1D* hInES7Mult[nMultbins+1];
TH1D* hOutES8Mult[nMultbins+1];
TH1D* hInES8Mult[nMultbins+1];
TH1D* hOutES9Mult[nMultbins+1];
TH1D* hInES9Mult[nMultbins+1];

 hOutAll=(TH1D *)Rf1->Get("hMcOutAll");
  hInAll=(TH1D *)Rf1->Get("hInOutAll");
  hOutAll->Sumw2();
  hInAll->Sumw2();
hOutAllnp=(TH1D *)Rf1->Get("hMcOutAllnp");
hOutAllnp->Sumw2();
hMcSecAll=(TH1D *)Rf1->Get("hMcSecAll");
hMcSecAll->Sumw2();

//hSecAll=(TH1D *)hMcSecAll->Clone("hSecAll");
//hSecAll->Divide(hOutAllnp);
TH1D* hSecAll = new TH1D("hSecAll","",nPtBins,xBins);
hSecAll->Divide(hMcSecAll,hOutAllnp);

Printd("getting histos")

for(Int_t j=1; j<nMultbins; ++j){
  hOutMult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%d",j));
  hInMult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%d",j));
  hOutMult[j]->Sumw2();
  hInMult[j]->Sumw2();
  hOutES0Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES0",j));
  hInES0Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES0",j));
  hOutES1Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES1",j));
  hInES1Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES1",j));
  hOutES2Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES2",j));
  hInES2Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES2",j));
  hOutES3Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES3",j));
  hInES3Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES3",j));
  hOutES4Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES4",j));
  hInES4Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES4",j));
  hOutES5Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES5",j));
  hInES5Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES5",j));
  hOutES6Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES6",j));
  hInES6Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES6",j));
  hOutES7Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES7",j));
  hInES7Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES7",j));
  hOutES8Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES8",j));
  hInES8Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES8",j));
  hOutES9Mult[j]=(TH1D *)Rf1->Get(Form("hMcOutMult%dES9",j));
  hInES9Mult[j]=(TH1D *)Rf1->Get(Form("hMcInMult%dES9",j));
  hOutES0Mult[j]->Sumw2();
  hInES0Mult[j]->Sumw2();
  hOutES1Mult[j]->Sumw2();
  hInES1Mult[j]->Sumw2();
  hOutES2Mult[j]->Sumw2();
  hInES2Mult[j]->Sumw2();
  hOutES3Mult[j]->Sumw2();
  hInES3Mult[j]->Sumw2();  
  hOutES4Mult[j]->Sumw2();
  hInES4Mult[j]->Sumw2();
  hOutES5Mult[j]->Sumw2();
  hInES5Mult[j]->Sumw2();
  hOutES6Mult[j]->Sumw2();
  hInES6Mult[j]->Sumw2();
  hOutES7Mult[j]->Sumw2();
  hInES7Mult[j]->Sumw2();
  hOutES8Mult[j]->Sumw2();
  hInES8Mult[j]->Sumw2();
  hOutES9Mult[j]->Sumw2();
  hInES9Mult[j]->Sumw2();
  Printf("j=%d",j);
}

Printf("starting phi dist..");
TH2D* HPhiptInMult[12+1];
TH2D* HPhiptInES0Mult[12+1];
TH2D* HPhiptInES1Mult[12+1];
TH2D* HPhiptInES2Mult[12+1];
TH2D* HPhiptInES3Mult[12+1];
TH2D* HPhiptOutMult[12+1];
TH2D* HPhiptOutES0Mult[12+1];
TH2D* HPhiptOutES1Mult[12+1];
TH2D* HPhiptOutES2Mult[12+1];
TH2D* HPhiptOutES3Mult[12+1];


TH2D* HNPhiptInMult[12+1];
TH2D* HNPhiptInES0Mult[12+1];
TH2D* HNPhiptInES1Mult[12+1];
TH2D* HNPhiptInES2Mult[12+1];
TH2D* HNPhiptInES3Mult[12+1];


for(Int_t j=0; j<12+1; ++j){
  HNPhiptInMult[j]=new TH2D(Form("HNPhiptInMult%d",j),";;",nPtBins,xBins,64,0,2.0*TMath::Pi());
  HNPhiptInES0Mult[j]=new TH2D(Form("HNPhiptInES0Mult%d",j),";;",nPtBins,xBins,64,0,2.0*TMath::Pi());
  HNPhiptInES1Mult[j]=new TH2D(Form("HNPhiptInES1Mult%d",j),";;",nPtBins,xBins,64,0,2.0*TMath::Pi());
  HNPhiptInES2Mult[j]=new TH2D(Form("HNPhiptInES2Mult%d",j),";;",nPtBins,xBins,64,0,2.0*TMath::Pi());
  HNPhiptInES3Mult[j]=new TH2D(Form("HNPhiptInES3Mult%d",j),";;",nPtBins,xBins,64,0,2.0*TMath::Pi());
  

  HPhiptInMult[j]=(TH2D *)Rf1->Get(Form("hMcPhiInMult%d",j));
  HPhiptInES0Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiInMult%dES0",j));
  HPhiptInES1Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiInMult%dES1",j));
  HPhiptInES2Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiInMult%dES2",j));
  HPhiptInES3Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiInMult%dES3",j));
  HPhiptOutMult[j]=(TH2D *)Rf1->Get(Form("hMcPhiOutMult%d",j));
  HPhiptOutES0Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiOutMult%dES0",j));
  HPhiptOutES1Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiOutMult%dES1",j));
  HPhiptOutES2Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiOutMult%dES2",j));
  HPhiptOutES3Mult[j]=(TH2D *)Rf1->Get(Form("hMcPhiOutMult%dES3",j));


}

Double_t IntPhiptInMult=0;
Double_t IntPhiptInES0Mult=0;
Double_t IntPhiptInES1Mult=0;
Double_t IntPhiptInES2Mult=0;
Double_t IntPhiptInES3Mult=0;

Double_t contPhiptInMult=0;
Double_t contPhiptInES0Mult=0;
Double_t contPhiptInES1Mult=0;
Double_t contPhiptInES2Mult=0;
Double_t contPhiptInES3Mult=0;


for(Int_t j=0; j<12+1; ++j){
  for(Int_t binx=0; binx<nPtBins+1; ++binx){
    IntPhiptInMult= HPhiptInMult[j]->Integral(binx,binx);
    IntPhiptInES0Mult= HPhiptInES0Mult[j]->Integral(binx,binx);
    IntPhiptInES1Mult= HPhiptInES1Mult[j]->Integral(binx,binx);
    IntPhiptInES2Mult= HPhiptInES2Mult[j]->Integral(binx,binx);
    IntPhiptInES3Mult= HPhiptInES3Mult[j]->Integral(binx,binx);

    if(IntPhiptInMult>0){
     for(Int_t biny=0; biny<64+1; ++biny){
      contPhiptInMult=HPhiptInMult[j]->GetBinContent(binx,biny);
      HNPhiptInMult[j]->SetBinContent(binx,biny,contPhiptInMult/IntPhiptInMult); 
     }
    }
   if(IntPhiptInES0Mult>0){
     for(Int_t biny=0; biny<64+1; ++biny){
      contPhiptInES0Mult=HPhiptInES0Mult[j]->GetBinContent(binx,biny);
      HNPhiptInES0Mult[j]->SetBinContent(binx,biny,contPhiptInES0Mult/IntPhiptInES0Mult);
     }
    }
    if(IntPhiptInES1Mult>0){
     for(Int_t biny=0; biny<64+1; ++biny){
      contPhiptInES1Mult=HPhiptInES1Mult[j]->GetBinContent(binx,biny);
      HNPhiptInES1Mult[j]->SetBinContent(binx,biny,contPhiptInES1Mult/IntPhiptInES1Mult);
     }
    }
    if(IntPhiptInES2Mult>0){
     for(Int_t biny=0; biny<64+1; ++biny){
      contPhiptInES2Mult=HPhiptInES2Mult[j]->GetBinContent(binx,biny);
      HNPhiptInES2Mult[j]->SetBinContent(binx,biny,contPhiptInES2Mult/IntPhiptInES2Mult);
     }
    }
    if(IntPhiptInES3Mult>0){
     for(Int_t biny=0; biny<64+1; ++biny){
      contPhiptInES3Mult=HPhiptInES3Mult[j]->GetBinContent(binx,biny);
      HNPhiptInES3Mult[j]->SetBinContent(binx,biny,contPhiptInES3Mult/IntPhiptInES3Mult);
     }
    }



  }
}

Printf("ending phi dist");

TH1D* HeffAllMB;
TH1D* HeffAllMBp;
TH1D* HeffAllMBn;
TH1D* HeffMult[nMultbins+1];
TH1D* HeffES0Mult[nMultbins+1];
TH1D* HeffES1Mult[nMultbins+1];
TH1D* HeffES2Mult[nMultbins+1];
TH1D* HeffES3Mult[nMultbins+1];
TH1D* HeffES4Mult[nMultbins+1];
TH1D* HeffES5Mult[nMultbins+1];
TH1D* HeffES6Mult[nMultbins+1];
TH1D* HeffES7Mult[nMultbins+1];
TH1D* HeffES8Mult[nMultbins+1];
TH1D* HeffES9Mult[nMultbins+1];



Printf("starting eff ana...");
HeffAllMB=new TH1D("HeffAllMB",";;",nPtBins,xBins);
for(Int_t j=1; j<nMultbins; ++j){

  HeffMult[j]=new TH1D(Form("HeffMult%d",j),";;",nPtBins,xBins);
  HeffES0Mult[j]=new TH1D(Form("HeffES0Mult%d",j),";;",nPtBins,xBins);
  HeffES1Mult[j]=new TH1D(Form("HeffES1Mult%d",j),";;",nPtBins,xBins);
  HeffES2Mult[j]=new TH1D(Form("HeffES2Mult%d",j),";;",nPtBins,xBins);
  HeffES3Mult[j]=new TH1D(Form("HeffES3Mult%d",j),";;",nPtBins,xBins);
  HeffES4Mult[j]=new TH1D(Form("HeffES4Mult%d",j),";;",nPtBins,xBins);
  HeffES5Mult[j]=new TH1D(Form("HeffES5Mult%d",j),";;",nPtBins,xBins);
  HeffES6Mult[j]=new TH1D(Form("HeffES6Mult%d",j),";;",nPtBins,xBins);
  HeffES7Mult[j]=new TH1D(Form("HeffES7Mult%d",j),";;",nPtBins,xBins);
  HeffES8Mult[j]=new TH1D(Form("HeffES8Mult%d",j),";;",nPtBins,xBins);
  HeffES9Mult[j]=new TH1D(Form("HeffES9Mult%d",j),";;",nPtBins,xBins);

}
Printf("Dividing")
  HeffAllMB->Divide(hOutAll,hInAll);
for(Int_t j=1; j<nMultbins; ++j){
  Printf(" jfor div=%d",j);
  HeffMult[j]->Divide(hOutMult[j],hInMult[j]);
  HeffES0Mult[j]->Divide(hOutES0Mult[j],hInES0Mult[j]);
  HeffES1Mult[j]->Divide(hOutES1Mult[j],hInES1Mult[j]);
  HeffES2Mult[j]->Divide(hOutES2Mult[j],hInES2Mult[j]);
  HeffES3Mult[j]->Divide(hOutES3Mult[j],hInES3Mult[j]);
  HeffES4Mult[j]->Divide(hOutES4Mult[j],hInES4Mult[j]);
  HeffES5Mult[j]->Divide(hOutES5Mult[j],hInES5Mult[j]);
  HeffES6Mult[j]->Divide(hOutES6Mult[j],hInES6Mult[j]);
  HeffES7Mult[j]->Divide(hOutES7Mult[j],hInES7Mult[j]);
  HeffES8Mult[j]->Divide(hOutES8Mult[j],hInES8Mult[j]);
  HeffES9Mult[j]->Divide(hOutES9Mult[j],hInES9Mult[j]);
} 

Printf("saving ...");
   TFile *fout = TFile::Open(Form("%s/%s",outDir,outfile),"RECREATE");
   fout->cd();
   HeffAllMB->Write();
   hSecAll->Write();
   for(Int_t j=1; j<nMultbins; ++j){
   HeffMult[j]->Write();
   HeffES0Mult[j]->Write();
   HeffES1Mult[j]->Write();
   HeffES2Mult[j]->Write();
   HeffES3Mult[j]->Write();
   HeffES4Mult[j]->Write();
   HeffES5Mult[j]->Write();
   HeffES6Mult[j]->Write();
   HeffES7Mult[j]->Write();
   HeffES8Mult[j]->Write();
   HeffES9Mult[j]->Write();
   }

   fout->Close();
Printf("Saved. Printing canvas...");

  TCanvas* ceMult;
  TLegend* legeMult;
  ceMult= new TCanvas("ceMult","THeMult",200,10,900,600);
  ceMult->SetLogx();
  gStyle->SetOptStat(0);
  legeMult= new TLegend(0.2,0.1,0.5,0.5);
  legeMult->SetHeader("Efficiency p-p #sqrt{s}=13 TeV, No So selection");
  legeMult->AddEntry(HeffAllMB,"MB","p");
  legeMult->SetTextFont(42);
  legeMult->SetTextSize(0.052);
  legeMult->SetLineColor(kWhite);
  legeMult->SetLineWidth(0);
  legeMult->SetLineStyle(3);
  legeMult->SetShadowColor(kYellow);
  legeMult->SetFillColorAlpha(kWhite,0.05);
  TH1* hFrceMult = 0;
  hFrceMult= ceMult->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=1; j<8+1; ++j){  
   HeffMult[6*j]->SetMarkerStyle(24);
   HeffMult[6*j]->SetMarkerColor(106-6*j); 
   legeMult->AddEntry(HeffMult[6*j], Form("For %1.1f<Mult<%1.1f",Multbins[6*j],Multbins[6*j+1]),"p");
  }

  hFrceMult->GetYaxis()->SetLabelSize(0.05);
  hFrceMult->GetXaxis()->SetLabelSize(0.05);
  hFrceMult->GetXaxis()->SetTitleSize(0.045);
  hFrceMult->GetYaxis()->SetTitleSize(0.045);  
  hFrceMult->GetYaxis()->SetTitle("Efficiency");
  hFrceMult->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMult->GetYaxis()->SetRangeUser(0.1,1.0);
  hFrceMult->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMult->Draw("EP");
  for(Int_t j=1; j<8+1; ++j){ 
   HeffMult[6*j]->Draw("E Psames");
  }
  HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMult->Draw();

   

  TCanvas* ceMultES0;
  TLegend* legeMultES0;
  ceMultES0= new TCanvas("ceMultES0","THeMultES0",200,10,900,600);
  ceMultES0->SetLogx();
  gStyle->SetOptStat(0);
  legeMultES0= new TLegend(0.2,0.1,0.5,0.5);
  legeMultES0->SetHeader(Form("Efficiency p-p #sqrt{s}=13 TeV %1.0f ^{0}/_{0}<So_{pc}<%1.0f ^{0}/_{0}",Sobins[0]*100,Sobins[1]*100));
  legeMultES0->AddEntry(HeffAllMB,"MB","p");
  legeMultES0->SetTextFont(42);
  legeMultES0->SetTextSize(0.052);
  legeMultES0->SetLineColor(kWhite);
  legeMultES0->SetLineWidth(0);
  legeMultES0->SetLineStyle(3);
  legeMultES0->SetShadowColor(kYellow);
  legeMultES0->SetFillColorAlpha(kWhite,0.05);
  TH1* hFrceMultES0 = 0;
  hFrceMultES0= ceMultES0->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=1; j<8+1; ++j){  
   HeffES0Mult[6*j]->SetMarkerStyle(24);
   HeffES0Mult[6*j]->SetMarkerColor(106-6*j); 
   legeMultES0->AddEntry(HeffES0Mult[6*j], Form("For %1.1f<Mult<%1.1f",Multbins[6*j],Multbins[6*j+1]),"p");
  }
  hFrceMultES0->GetYaxis()->SetLabelSize(0.05);
  hFrceMultES0->GetXaxis()->SetLabelSize(0.05);
  hFrceMultES0->GetXaxis()->SetTitleSize(0.045);
  hFrceMultES0->GetYaxis()->SetTitleSize(0.045);  
  hFrceMultES0->GetYaxis()->SetTitle("Efficiency");
  hFrceMultES0->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMultES0->GetYaxis()->SetRangeUser(0.1,1);
  hFrceMultES0->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMultES0->Draw("EP");
  for(Int_t j=1; j<8+1; ++j){ 
   HeffES0Mult[6*j]->Draw("E Psames");
  }
    HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMultES0->Draw();

  /*
  TCanvas* ceMultES1;
  TLegend* legeMultES1;
  ceMultES1= new TCanvas("ceMultES1","THeMultES1",200,10,900,600);
  ceMultES1->SetLogx();
  gStyle->SetOptStat(0);
  legeMultES1= new TLegend(0.2,0.1,0.5,0.25);
  legeMultES1->SetHeader(Form("Efficiency p-p #sqrt{s}=13 TeV %1.1f<So<%1.1f",Sobins[1],Sobins[2]));
  legeMultES1->AddEntry(HeffAllMB,"MB","p");
   TH1* hFrceMultES1 = 0;
  hFrceMultES1= ceMultES1->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=5; j<12+1; ++j){  
   HeffES1Mult[5*j]->SetMarkerStyle(24);
   HeffES1Mult[5*j]->SetMarkerColor(135-7*j); 
   legeMultES1->AddEntry(HeffES1Mult[5*j], Form("For %1.1f<Mult<%1.1f",Multbins[5*j],Multbins[5*j+1]),"p");
  }
  hFrceMultES1->GetYaxis()->SetTitle("Efficiency");
  hFrceMultES1->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMultES1->GetYaxis()->SetRangeUser(0,1.2);
  hFrceMultES1->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMultES1->Draw("EP");
  for(Int_t j=5; j<12+1; ++j){ 
   HeffES1Mult[5*j]->Draw("E Psames");
  }
  HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMultES1->Draw();


  
  TCanvas* ceMultES2;
  TLegend* legeMultES2;
  ceMultES2= new TCanvas("ceMultES2","THeMultES2",200,10,900,600);
  ceMultES2->SetLogx();
  gStyle->SetOptStat(0);
  legeMultES2= new TLegend(0.2,0.1,0.5,0.25);
  legeMultES2->SetHeader(Form("Efficiency p-p #sqrt{s}=13 TeV %1.1f<So<%1.1f",Sobins[2],Sobins[3]));
  legeMultES2->AddEntry(HeffAllMB,"MB","p");
  TH1* hFrceMultES2 = 0;
  hFrceMultES2= ceMultES2->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=5; j<12+1; ++j){  
   HeffES2Mult[5*j]->SetMarkerStyle(24);
   HeffES2Mult[5*j]->SetMarkerColor(135-7*j); 
   legeMultES2->AddEntry(HeffES2Mult[5*j], Form("For %1.1f<Mult<%1.1f",Multbins[5*j],Multbins[5*j+1]),"p");
  }
  hFrceMultES2->GetYaxis()->SetTitle("Efficiency");
  hFrceMultES2->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMultES2->GetYaxis()->SetRangeUser(0,1.2);
  hFrceMultES2->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMultES2->Draw("EP");
  for(Int_t j=5; j<12+1; ++j){ 
   HeffES2Mult[5*j]->Draw("E Psames");
  }
  HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMultES2->Draw();
*/
   
  TCanvas* ceMultES3;
  TLegend* legeMultES3;
  ceMultES3= new TCanvas("ceMultES3","THeMultES3",200,10,900,600);
  ceMultES3->SetLogx();
  gStyle->SetOptStat(0);
  legeMultES3= new TLegend(0.2,0.1,0.5,0.5);
  legeMultES3->SetHeader(Form("Efficiency p-p #sqrt{s}=13 TeV %1.0f {}^{0}/_{0} <So_{pc}<%1.0f {}^{0}/_{0}",Sobins[3]*100,Sobins[4]*100));
  legeMultES3->AddEntry(HeffAllMB,"MB","p");
  legeMultES3->SetTextFont(42);
  legeMultES3->SetTextSize(0.052);
  legeMultES3->SetLineColor(kWhite);
  legeMultES3->SetLineWidth(0);
  legeMultES3->SetLineStyle(3);
  legeMultES3->SetShadowColor(kYellow);
  legeMultES3->SetFillColorAlpha(kWhite,0.05);
  TH1* hFrceMultES3 = 0;
  hFrceMultES3= ceMultES3->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=1; j<8+1; ++j){  
   HeffES3Mult[6*j]->SetMarkerStyle(24);
   HeffES3Mult[6*j]->SetMarkerColor(106-6*j); 
   legeMultES3->AddEntry(HeffES3Mult[6*j], Form("For %1.1f<Mult<%1.1f",Multbins[6*j],Multbins[6*j+1]),"p");
  }
  hFrceMultES3->GetYaxis()->SetLabelSize(0.05);
  hFrceMultES3->GetXaxis()->SetLabelSize(0.05);
  hFrceMultES3->GetXaxis()->SetTitleSize(0.045);
  hFrceMultES3->GetYaxis()->SetTitleSize(0.045);
  hFrceMultES3->GetYaxis()->SetTitle("Efficiency");
  hFrceMultES3->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMultES3->GetYaxis()->SetRangeUser(0.1,1);
  hFrceMultES3->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMultES3->Draw("EP");
  for(Int_t j=1; j<8+1; ++j){ 
   HeffES3Mult[6*j]->Draw("E Psames");
  }
  HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMultES3->Draw();


  TCanvas* ceMultES9;
  TLegend* legeMultES9;
  ceMultES9= new TCanvas("ceMultES9","THeMultES9",200,10,900,600);
  ceMultES9->SetLogx();
  gStyle->SetOptStat(0);
  legeMultES9= new TLegend(0.2,0.1,0.5,0.5);
  legeMultES9->SetHeader(Form("Efficiency p-p #sqrt{s}=13 TeV %1.0f ^{0}/_{0}<So_{pc}<%1.0f ^{0}/_{0}",Sobins[9]*100,Sobins[10]*100));
  legeMultES9->AddEntry(HeffAllMB,"MB","p");
  legeMultES9->SetTextFont(42);
  legeMultES9->SetTextSize(0.052);
  legeMultES9->SetLineColor(kWhite);
  legeMultES9->SetLineWidth(0);
  legeMultES9->SetLineStyle(3);
  legeMultES9->SetShadowColor(kYellow);
  legeMultES9->SetFillColorAlpha(kWhite,0.05);
  TH1* hFrceMultES9 = 0;
  hFrceMultES9= ceMultES9->DrawFrame(0.001,0,2e6,150);
  for(Int_t j=1; j<8+1; ++j){
   HeffES9Mult[6*j]->SetMarkerStyle(24);
   HeffES9Mult[6*j]->SetMarkerColor(106-6*j);
   legeMultES9->AddEntry(HeffES9Mult[6*j], Form("For %1.1f<Mult<%1.1f",Multbins[6*j],Multbins[6*j+1]),"p");
  }
  hFrceMultES9->GetYaxis()->SetLabelSize(0.05);
  hFrceMultES9->GetXaxis()->SetLabelSize(0.05);
  hFrceMultES9->GetXaxis()->SetTitleSize(0.045);
  hFrceMultES9->GetYaxis()->SetTitleSize(0.045);
  hFrceMultES9->GetYaxis()->SetTitle("Efficiency");
  hFrceMultES9->GetXaxis()->SetTitle("p_{T} (GeV/c) (|eta|<0.8)");
  hFrceMultES9->GetYaxis()->SetRangeUser(0.1,1);
  hFrceMultES9->GetXaxis()->SetRangeUser(0.15,10);
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();
  hFrceMultES9->Draw("EP");
  for(Int_t j=1; j<8+1; ++j){
   HeffES9Mult[6*j]->Draw("E Psames");
  }
  HeffAllMB->SetMarkerStyle(20);
  HeffAllMB->SetMarkerColor(1);
  HeffAllMB->Draw("E Psames");
  legeMultES9->Draw();

 

  

}

