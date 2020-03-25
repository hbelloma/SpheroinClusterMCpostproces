#include "TGaxis.h"
#include <TH1D.h>
#include <TH2D.h>
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
//#include "esa_tools.C"
#include "Rtypes.h"
#include "my_settings.C"

#include <iostream>


void plotcomparinmptSo(){



const Double_t absetacmsforana=0.8;
const Double_t eta_for_ntrk = 0.8; 
const Double_t eta_for_pt = 0.8; 
const Double_t eta_for_es = 0.8; 

TFile *fppm = TFile::Open("inel/MeanPtVsNm_inelf.root");
TFile *fppfullycorr = TFile::Open("inel/FullyCorrectedCorrelation.root");
//TFile *fppSoc = TFile::Open("inel/FullyCorrectedMeanPtVsNm_inel.root");
//TFile *fppm2 = TFile::Open("inel/MeanPtVsNm_inelf.root");
//TFile *fppm2 = TFile::Open("inel/FullyCorrectedCorrelation.root");

TFile *fppmEsBin[nSobins];
TFile *fppmEsBin2[nSobins];
TFile *fppSoc[nSobins];
TFile *fppfullycorrEsBin[nSobins];

for(Int_t i=0; i<nSobins; i++){
  fppmEsBin[i]= TFile::Open(Form("EsBin%d/MeanPtVsNm_EsBin%df.root",i,i));
  fppmEsBin2[i]= TFile::Open(Form("EsBin%d/MeanPtVsNm_EsBin%df.root",i,i));
  fppSoc[i]= TFile::Open(Form("EsBin%d/FullyCorrectedMeanPtVsNm_EsBin%d.root",i,i));
  fppfullycorrEsBin[i]=TFile::Open(Form("EsBin%d/FullyCorrectedCorrelation.root",i));
  //fppmEsBin2[i]= TFile::Open(Form("EsBin%d/FullyCorrectedCorrelation.root",i));
}
 TFile* outFile = new TFile("comparisonpt_Sobins.root", "RECREATE");

TH1D *hmeanptppinel;
TH1D *hmeanptmppinel;
TH1D *hmeanptfcppinel;
TH1D *hmeanptppEsBin[nSobins];
TH1D *hmeanptmppEsBin[nSobins];
TH1D *hmeanptfcppEsBin[nSobins];
TH1D *hsum;

TH1D *hdivmeanptppinel;
TH1D *hdivmeanptppEsBin[nSobins];
TH1D *hdivMBsum;

TH1D *hptppinel[nMultbins];
TH1D *hptppEsBin[nMultbins][nSobins];
/*
TH1D *hmeanptppEsBin0;
TH1D *hmeanptppEsBin1;
TH1D *hmeanptppEsBin2;
TH1D *hmeanptppEsBin3;
TH1D *hmeanptppEsBin4;
TH1D *hmeanptppEsBin5;
TH1D *hmeanptppEsBin6;
TH1D *hmeanptppEsBin7;
TH1D *hmeanptppEsBin8;
TH1D *hmeanptppEsBin9;
*/


//hmeanptppinel=(TH1D *)fppm->Get("hPtmvsNm_inel");
hmeanptppinel=(TH1D *)fppfullycorr->Get("hPtVsNch");
//hmeanptppinel=(TH1D *)fppm2->Get("hPtVsNch");
hmeanptmppinel=(TH1D *)fppm->Get("hPtmvsNm_inel");
hmeanptfcppinel=(TH1D *)fppfullycorr->Get("hPtVsNch");

hdivmeanptppinel=(TH1D *)hmeanptppinel->Clone("hdivmeanptppinel");
//hdivmeanptppinel->Divide(hmeanptmppinel);
hdivmeanptppinel->Add(hmeanptmppinel,-1);


for(Int_t n=0; n<nMultbins; n++){
 hptppinel[n]=(TH1D *)fppm->Get(Form("hMcOutMult%d",n));
}
for(Int_t i=0; i<nSobins; i++){  
  // corrected
 // hmeanptppEsBin[i]=(TH1D *)fppSoc[i]->Get("hPtmvsNm"); // measured
//  hmeanptppEsBin[i]=(TH1D *)fppSoc[i]->Get("hPtvsNm"); // eff & sec corr
//  hmeanptppEsBin[i]=(TH1D *)fppSoc[i]->Get(Form("hFullyCorrectedPtvsNm_EsBin%d",i)); //So corr
 hmeanptppEsBin[i]=(TH1D *)(TH1D *)fppfullycorrEsBin[i]->Get("hPtVsNch"); // fully corrected
//  hmeanptmppEsBin[i]=(TH1D *)fppmEsBin[i]->Get(Form("hPtmvsNm_EsBin%d",i)); // not extrap
  hmeanptmppEsBin[i]=(TH1D *)fppmEsBin[i]->Get("hPtmvsNm");  // con low Nch extrap
//  hmeanptppEsBin[i]=(TH1D *)fppmEsBin2[i]->Get("hPtVsNch");
  hmeanptfcppEsBin[i]=(TH1D *)fppfullycorrEsBin[i]->Get("hPtVsNch");// all corrected So & Nch unf 
  hdivmeanptppEsBin[i]=(TH1D *)hmeanptppEsBin[i]->Clone(Form("hmeanptmppEsBin%d",i));
  //hdivmeanptppEsBin[i]->Divide(hmeanptmppEsBin[i]);
  hdivmeanptppEsBin[i]->Add(hmeanptmppEsBin[i],-1);

  for(Int_t n=0; n<nMultbins; n++){
    hptppEsBin[n][i]=(TH1D *)fppmEsBin[i]->Get(Form("hMcOutMult%dES%d",n,i));
  }
}

hsum=(TH1D *)hmeanptmppEsBin[0]->Clone("hsuma");

for(Int_t i=1; i<nSobins; i++){
 hsum->Add(hmeanptmppEsBin[i]);
}
hsum->Scale(0.1);
hsum->SetMarkerColor(kBlue);
hdivMBsum=(TH1D *)hmeanptmppinel->Clone("hdivMBsum");
hdivMBsum->Divide(hsum);

/*
TCanvas* cptsJ = new TCanvas("cptsJ","THptsJ",200,10,900,600);
 gStyle->SetOptStat(0);
cptsJ->SetLogx();
cptsJ->SetLogy(); 
TLegend* legptsJ = new TLegend(0.2, 0.1,0.5, 0.5); 
hptppEsBin[3][0]->SetMarkerStyle(20);
hptppEsBin[3][0]->SetXTitle("(corrected) #it{p}_{T} (GeV/#it{c})");
hptppEsBin[3][0]->SetYTitle("d^{2}#it{N}_{ch} / (N_{ev} 2#pi#it{p}_{T}d#etad#it{p}_{T}) (GeV/#it{c})^{-2}");
hptppEsBin[3][0]->GetXaxis()->SetRangeUser(0.15,10);
hptppEsBin[3][0]->GetYaxis()->SetRangeUser(0.000001,1000);
hptppEsBin[3][0]->GetYaxis()->SetLabelSize(0.05);
hptppEsBin[3][0]->GetXaxis()->SetLabelSize(0.05);
hptppEsBin[3][0]->GetXaxis()->SetTitleSize(0.045);
hptppEsBin[3][0]->GetYaxis()->SetTitleSize(0.045);
  legptsJ->SetTextFont(42);
  legptsJ->SetTextSize(0.04);
  legptsJ->SetLineColor(kWhite);
  legptsJ->SetLineWidth(0);
  legptsJ->SetLineStyle(3);
  legptsJ->SetShadowColor(kYellow);
  legptsJ->SetFillColorAlpha(kWhite,0.05);
legptsJ->SetHeader(Form("pp 13 TeVs LHC15g3c3:  %1.0f ^{0}/_{0}<So_{pc}<%1.0f ^{0}/_{0}",Sobins[0]*100,Sobins[0+1]*100));
legptsJ->AddEntry(hptppEsBin[3][0],"Nch=3","p");
hptppEsBin[3][0]->Draw();
for(Int_t i=1; i<10; i++){
  hptppEsBin[i*6][0]->SetMarkerStyle(20);
  hptppEsBin[i*6][0]->SetMarkerColor(100-i*5);
  legptsJ->AddEntry(hptppEsBin[i*6][0],Form("Nch=%1.0f",Multbins[i*6]),"p");
  hptppEsBin[i*6][0]->Draw("same");
}
legptsJ->Draw();


TCanvas* cptsI = new TCanvas("cptsI","THptsI",200,10,900,600);
 gStyle->SetOptStat(0);
cptsI->SetLogx();
cptsI->SetLogy(); 
TLegend* legptsI = new TLegend(0.2, 0.1,0.5, 0.5); 
hptppEsBin[3][9]->SetMarkerStyle(20);
hptppEsBin[3][9]->SetXTitle("(corrected) #it{p}_{T} (GeV/#it{c})");
hptppEsBin[3][9]->SetYTitle("d^{2}#it{N}_{ch} / (N_{ev} 2#pi#it{p}_{T}d#etad#it{p}_{T}) (GeV/#it{c})^{-2}");
hptppEsBin[3][9]->GetXaxis()->SetRangeUser(0.15,10);
hptppEsBin[3][9]->GetYaxis()->SetRangeUser(0.000001,1000);
hptppEsBin[3][9]->GetYaxis()->SetLabelSize(0.05);
hptppEsBin[3][9]->GetXaxis()->SetLabelSize(0.05);
hptppEsBin[3][9]->GetXaxis()->SetTitleSize(0.045);
hptppEsBin[3][9]->GetYaxis()->SetTitleSize(0.045);
  legptsI->SetTextFont(42);
  legptsI->SetTextSize(0.04);
  legptsI->SetLineColor(kWhite);
  legptsI->SetLineWidth(0);
  legptsI->SetLineStyle(3);
  legptsI->SetShadowColor(kYellow);
  legptsI->SetFillColorAlpha(kWhite,0.05);
legptsI->SetHeader(Form("pp 13 TeVs LHC15g3c3:  %1.0f ^{0}/_{0}<So_{pc}<%1.0f ^{0}/_{0}",Sobins[9]*100,Sobins[9+1]*100));
legptsI->AddEntry(hptppEsBin[3][9],"Nch=3","p");
hptppEsBin[3][9]->Draw();
for(Int_t i=1; i<10; i++){
  hptppEsBin[i*6][9]->SetMarkerStyle(20);
  hptppEsBin[i*6][9]->SetMarkerColor(100-i*5);
  legptsI->AddEntry(hptppEsBin[i*6][9],Form("Nch=%1.0f",Multbins[i*6]),"p");
  hptppEsBin[i*6][9]->Draw("same");
}
legptsI->Draw();



TCanvas* cpts = new TCanvas("cpts","THpts",200,10,900,600);
 gStyle->SetOptStat(0);
cpts->SetLogx();
cpts->SetLogy(); 
TLegend* legpts = new TLegend(0.2, 0.1,0.5, 0.5); 
hptppinel[3]->SetMarkerStyle(20);
hptppinel[3]->SetXTitle("(corrected) #it{p}_{T} (GeV/#it{c})");
hptppinel[3]->SetYTitle("d^{2}#it{N}_{ch} / (N_{ev} 2#pi#it{p}_{T}d#etad#it{p}_{T}) (GeV/#it{c})^{-2}");
hptppinel[3]->GetXaxis()->SetRangeUser(0.15,10);
hptppinel[3]->GetYaxis()->SetRangeUser(0.000001,1000);
hptppinel[3]->GetYaxis()->SetLabelSize(0.05);
hptppinel[3]->GetXaxis()->SetLabelSize(0.05);
hptppinel[3]->GetXaxis()->SetTitleSize(0.045);
hptppinel[3]->GetYaxis()->SetTitleSize(0.045);
  legpts->SetTextFont(42);
  legpts->SetTextSize(0.04);
  legpts->SetLineColor(kWhite);
  legpts->SetLineWidth(0);
  legpts->SetLineStyle(3);
  legpts->SetShadowColor(kYellow);
  legpts->SetFillColorAlpha(kWhite,0.05);
legpts->SetHeader("pp 13 TeVs LHC15g3c3:");
legpts->AddEntry(hptppinel[3],"Nch=3","p");
hptppinel[3]->Draw();
for(Int_t i=1; i<10; i++){
  hptppinel[i*6]->SetMarkerStyle(20);
  hptppinel[i*6]->SetMarkerColor(100-i*5);
  legpts->AddEntry(hptppinel[i*6],Form("Nch=%1.0f",Multbins[i*6]),"p");
  hptppinel[i*6]->Draw("same");
}
legpts->Draw();

*/

TCanvas* cptm = new TCanvas("cptm","THptm",200,10,900,600);
 gStyle->SetOptStat(0);
TLegend* legptm = new TLegend(0.2, 0.1,0.5, 0.5); 
TLegend* legptm2 = new TLegend(0.2, 0.1,0.5, 0.5);
hmeanptppinel->SetMarkerStyle(34);
hmeanptppinel->SetMarkerColor(kBlack);
hmeanptppinel->GetXaxis()->SetRangeUser(0,70);
hmeanptppinel->GetYaxis()->SetRangeUser(0.4,1.2);
hmeanptppinel->GetYaxis()->SetLabelSize(0.05);
hmeanptppinel->GetXaxis()->SetLabelSize(0.05);
hmeanptppinel->GetXaxis()->SetTitleSize(0.045);
hmeanptppinel->GetYaxis()->SetTitleSize(0.045);
  legptm->SetTextFont(42);
  legptm->SetTextSize(0.04);
  legptm->SetLineColor(kWhite);
  legptm->SetLineWidth(0);
  legptm->SetLineStyle(3);
  legptm->SetShadowColor(kYellow);
  legptm->SetFillColorAlpha(kWhite,0.05);
legptm2->SetTextFont(42);
  legptm2->SetTextSize(0.04);
  legptm2->SetLineColor(kWhite);
  legptm2->SetLineWidth(0);
  legptm2->SetLineStyle(3);
  legptm2->SetShadowColor(kYellow);
  legptm2->SetFillColorAlpha(kWhite,0.05);
  legptm->SetHeader("pp 13 TeVs LHC15g3c3:");
  legptm2->SetHeader("Pythia Per2011 corrected with EPOS:");
  legptm->AddEntry(hmeanptppinel,"No So Sel. (MB)","p");
hmeanptppinel->Draw();
hmeanptppEsBin[0]->SetMarkerStyle(20);
hmeanptppEsBin[0]->SetMarkerColor(100);
legptm->AddEntry(hmeanptppEsBin[0],Form("%1.0f  ^{0}/_{0} <So_{pc}<%1.0f ^{0}/_{0} ",Sobins[0]*100,Sobins[1]*100),"p");
hmeanptppEsBin[0]->Draw("same");

for(Int_t i=1; i<10; i++){
  hmeanptppEsBin[i]->SetMarkerStyle(24+i);
  hmeanptppEsBin[i]->SetMarkerColor(100-i*5);
  legptm->AddEntry(hmeanptppEsBin[i],Form("%1.0f  ^{0}/_{0} <So_{pc}<%1.0f ^{0}/_{0} ",Sobins[i]*100,Sobins[i+1]*100),"p");
  hmeanptppEsBin[i]->Draw("same");
}
legptm->Draw();
legptm2->Draw();

/*
TCanvas* cptmm = new TCanvas("cptmm","THptmm",200,10,900,600);
 gStyle->SetOptStat(0);
TLegend* legptmm = new TLegend(0.2, 0.1,0.5, 0.5);
TLegend* legptmm2 = new TLegend(0.2, 0.1,0.5, 0.5);
hmeanptmppinel->SetMarkerStyle(28);
hmeanptmppinel->SetMarkerColor(kBlack);
hmeanptmppinel->GetXaxis()->SetRangeUser(0,70);
hmeanptmppinel->GetYaxis()->SetRangeUser(0.4,1.2);
hmeanptmppinel->GetYaxis()->SetLabelSize(0.05);
hmeanptmppinel->GetXaxis()->SetLabelSize(0.05);
hmeanptmppinel->GetXaxis()->SetTitleSize(0.045);
hmeanptmppinel->GetYaxis()->SetTitleSize(0.045);
  legptmm->SetTextFont(42);
  legptmm->SetTextSize(0.04);
  legptmm->SetLineColor(kWhite);
  legptmm->SetLineWidth(0);
  legptmm->SetLineStyle(3);
  legptmm->SetShadowColor(kYellow);
  legptmm->SetFillColorAlpha(kWhite,0.05);
legptmm2->SetTextFont(42);
  legptmm2->SetTextSize(0.04);
  legptmm2->SetLineColor(kWhite);
  legptmm2->SetLineWidth(0);
  legptmm2->SetLineStyle(3);
  legptmm2->SetShadowColor(kYellow);
  legptmm2->SetFillColorAlpha(kWhite,0.05);
  legptmm->SetHeader("pp 13 TeVs LHC15g3c3:");
  legptmm2->SetHeader("Pythia Per2011 measured with EPOS:");
  legptmm->AddEntry(hmeanptppinel,"No So Sel. (MB)","p");
  legptmm->AddEntry(hmeanptmppinel,"No So Sel. (MB) meas","p");
hmeanptmppinel->Draw();
hmeanptppinel->Draw("same");
hmeanptmppEsBin[0]->SetMarkerStyle(24);
hmeanptmppEsBin[0]->SetMarkerColor(100-0*5);
legptmm->AddEntry(hmeanptmppEsBin[0],Form("%1.0f  ^{0}/_{0} <So_{pc}<%1.0f ^{0}/_{0} ",Sobins[0]*100,Sobins[1]*100),"p");
hmeanptmppEsBin[0]->Draw("same");
hmeanptmppEsBin[9]->SetMarkerStyle(27);
hmeanptmppEsBin[9]->SetMarkerColor(100-9*5);
legptmm->AddEntry(hmeanptmppEsBin[9],Form("%1.0f  ^{0}/_{0} <So_{pc}<%1.0f ^{0}/_{0} ",Sobins[9]*100,Sobins[10]*100),"p");
hmeanptmppEsBin[9]->Draw("same");
legptmm->Draw();
legptmm2->Draw();
*/



 TH1D *hframe[2];
TF1 *funo = new TF1("funo","0.0+pol0",1,100);
  funo->SetLineColor(1);
  funo->SetLineStyle(2);
  funo->SetLineWidth(2);
  for(Int_t j=0;j<2;++j)
    hframe[j] = new TH1D(Form("hframe_%d",j),Form("hframe_%d",j),50,0,100);
  gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  const Int_t nPadX = 1;
  const Int_t nPadY = 2;
  Float_t noMargin    = 0.0;
  Float_t topMargin   = 0.005;
  Float_t botMargin   = 0.09;
  Float_t leftMargin  = 0.06;
  Float_t rightMargin = 0.01;
  Float_t width       = (1-rightMargin-leftMargin)/nPadX;
  Float_t height      = (1-botMargin-topMargin)/nPadY;
  TCanvas* cRaaPionsAll = new TCanvas("closureTest", "Raa Pions", 550, 800);
  cRaaPionsAll->SetFillStyle(0);
  TPad* pRaaPions[nPadX*nPadY];
  Float_t shift = 0.05;
  const char* yTitleRaaPions = Form(" corrected - measured  #LT #it{p}_{T} #GT (GeV/#it{c}), (|#eta|<%1.1f)", eta_for_pt);
  const char* xTitleRaaPions = Form("N_{ch} (N_{trk}), (|#eta|<%1.1f)", eta_for_ntrk);
  cRaaPionsAll->cd();

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextAlign(22);
  latex->SetTextAngle(0);
  latex->SetTextFont(42);
  latex->DrawLatex(0.5,0.04,xTitleRaaPions);
  latex->SetTextAngle(90);
  latex->SetTextSize(0.055);
  latex->DrawLatex(0.05,0.52,yTitleRaaPions);
  latex->SetTextSize(0.07);
  latex->SetTextAngle(270);
  latex->SetTextSize(0.04);

  Printf("iniciando for");
  for (Int_t i = 1; i < 3; i++) {

    Int_t iX = (i-1)%nPadX;
    Int_t iY = (i-1)/nPadX;
    Float_t x1 = leftMargin + iX*width;
   if(iX==2)
      x1-=0.01;//it was 0.01
    else if(iX==1)
      x1+=0.01;//it was 0.01
   Float_t x2 = leftMargin + (iX + 1)*width;
     if(iX==0)
       x2+=0.01;
     else if(iX==1)
       x2-=0.01;
     Float_t y1 = 1 - topMargin - (iY +1)*height;
     Float_t y2 = 1 - topMargin - iY*height;
     pRaaPions[i-1] = new TPad(Form("padRaa%d",i),"", x1, y1, x2, y2, 0, 0, 0);
     Float_t mBot = noMargin;
     Float_t mTop = noMargin;
     Float_t mLeft = noMargin;
     Float_t mRight = noMargin;
     if(iY==0)       mTop   = shift;
     if(iY==nPadY-1) mBot   = shift;
     if(iX==0)       mLeft  = 0.08;
     if(iX==nPadX-1) mRight = 0.08;
     pRaaPions[i-1]->SetBottomMargin(mBot);
     pRaaPions[i-1]->SetTopMargin(mTop);
     pRaaPions[i-1]->SetLeftMargin(mLeft);
     pRaaPions[i-1]->SetRightMargin(mRight);
     pRaaPions[i-1]->SetFillStyle(0);
     pRaaPions[i-1]->SetLeftMargin(0.13);
     if(i==2)
       pRaaPions[i-1]->SetBottomMargin(0.08);
     cRaaPionsAll->cd();
     pRaaPions[i-1]->Draw();

  }
  for (Int_t index = 1; index < 3; index++) {

    pRaaPions[index-1]->cd();
    pRaaPions[index-1]->SetTickx(1);
    pRaaPions[index-1]->SetTicky(1);
    pRaaPions[index-1]->SetLogy(0);
    if(index==2) pRaaPions[index-1]->SetGridy();
    hframe[index-1]->GetYaxis()->SetLabelSize(0.076);
    hframe[index-1]->GetXaxis()->SetTitle("");
    hframe[index-1]->GetYaxis()->SetTitle("");
    hframe[index-1]->SetLineColor(0);
    if(index == 1){
      Printf("if");
      hframe[index-1]->Draw();
      hframe[index-1]->GetYaxis()->SetRangeUser(0.4,1.2);
      //Printf("Markers hPtmVsNm ");
/*
      hmeanptppinel->SetMarkerStyle(24);
      hmeanptppEsBin[0]->SetMarkerStyle(24);
      hmeanptppEsBin[9]->SetMarkerStyle(24);
      hmeanptmppinel->SetMarkerStyle(20);
      hmeanptmppEsBin[0]->SetMarkerStyle(20);
      hmeanptmppEsBin[9]->SetMarkerStyle(20);
      //Printf("Markers Style ");
      hmeanptppinel->SetLineColor(kBlack);
      hmeanptmppinel->SetLineColor(kBlack);
      //Printf("Markers LineColor ");
      hmeanptppEsBin[0]->SetMarkerColor(kRed);
      hmeanptppEsBin[9]->SetMarkerColor(kBlue);
      hmeanptmppEsBin[0]->SetMarkerColor(kRed);
      hmeanptmppEsBin[9]->SetMarkerColor(kBlue);
*/
      //Printf("Markers Color ");
      //Printf("... hPtmVsNm ");
//      hmeanptppinel->Draw("samep");
//      hmeanptppEsBin[0]->Draw("samep");
//      hmeanptppEsBin[9]->Draw("samep");
      hsum->Draw("samep");
      hmeanptmppinel->Draw("samep");
//      hmeanptmppEsBin[0]->Draw("samep");
//      hmeanptmppEsBin[9]->Draw("samep");
      //Printf("hPtmVsNm ...");
      TLegend *leg1 = 0;
      leg1 = new TLegend(0.26,0.55,0.93,0.94);
      leg1->SetTextFont(42);
      leg1->SetTextSize(0.052);
      leg1->SetLineColor(kWhite);
      leg1->SetLineWidth(0);
      leg1->SetLineStyle(3);
      leg1->SetShadowColor(kWhite);
      leg1->SetFillColor(kWhite);
      leg1->SetFillStyle(0);
      leg1->SetHeader("#LT #it{p}_{T} #GT");
      leg1->AddEntry(hsum, "Sum of all So bins");
//      leg1->AddEntry(hmeanptppinel,"Inclusive So corr","P");
//      leg1->AddEntry(hmeanptppEsBin[0],"Jetty So corr","P");
//      leg1->AddEntry(hmeanptppEsBin[9],"Isot So corr","P");
      leg1->AddEntry(hmeanptmppinel,"Inclusive meas","P");
//      leg1->AddEntry(hmeanptmppEsBin[0],"Jetty meas","P");
//      leg1->AddEntry(hmeanptmppEsBin[9],"Isot meas","P");
      leg1->Draw();
    }
    else{
      Printf("else");
      hframe[index-1]->GetYaxis()->SetRangeUser(-0.05,0.05);
      hframe[index-1]->GetXaxis()->SetLabelSize(0.08);
      hframe[index-1]->Draw();
      funo->Draw("same");
/*
      hdivmeanptppinel->SetLineColor(kBlack);
      hdivmeanptppinel->SetLineWidth(2);
      hdivmeanptppinel->SetMarkerStyle(34);
      hdivmeanptppinel->Draw("samep");
      hdivmeanptppEsBin[0]->SetMarkerColor(kRed);
      hdivmeanptppEsBin[0]->SetLineWidth(2);
      hdivmeanptppEsBin[0]->SetMarkerStyle(20);
      hdivmeanptppEsBin[0]->Draw("samep");
      hdivmeanptppEsBin[9]->SetMarkerColor(kBlue);
      hdivmeanptppEsBin[9]->SetLineWidth(2);
      hdivmeanptppEsBin[9]->SetMarkerStyle(33);
      hdivmeanptppEsBin[9]->Draw("samep");
      hdivMBsum->SetLineColor(kBlack);
*/
     hdivMBsum->SetLineWidth(2);
     hdivMBsum->SetMarkerStyle(34);
     hdivMBsum->Draw("samep");
    }

  }








}
