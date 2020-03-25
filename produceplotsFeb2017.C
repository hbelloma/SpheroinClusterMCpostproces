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


/*
  

  +++++++++++++++++++++++++++++++++++++++++++++++++++
  final program
  +++++++++++++++++++++++++++++++++++++++++++++++++++
  root
  .L DebugClassesMultESA2016.C+
  .L produceplotsFeb2017.C+

1.-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  MakeNchResponseMatrix("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root","BuildingNchRM_PER11")

  MakeNchResponseMatrix("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root","BuildingNchRM_PER11",1)  
2.-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  MakeTestEfficiency("Efficiencypt/EfficiencyPerc10_Per11.root", "PicturesEfficiency_EPOS")


3.-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  MakePerformanceResolutionsVsNtrk("SOpp13TeV_MERGE_newbinsSOPCSO_EPOS4corr.root", "PicturesEfficiency_EPOS")

4.-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  MakeCorrectionEfficiencyCorrPt("/Users/hbelloma/Desktop/FORMEANPT/DataLHC15fpass2/postprocesing/SOpp13TeV_MERGE_newbinsSOPCSO_LHC15fpass2.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 0, "MeanPtInput")  

  MakeCorrectionEfficiencyCorrPt("/Users/hbelloma/Desktop/FORMEANPT/DataLHC15fpass2/postprocesing/SOpp13TeV_MERGE_newbinsSOPCSO_LHC15fpass2.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 1, "MeanPtInput")  
  MakeCorrectionEfficiencyCorrPt("/Users/hbelloma/Desktop/FORMEANPT/DataLHC15fpass2/postprocesing/SOpp13TeV_MERGE_newbinsSOPCSO_LHC15fpass2.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 2, "MeanPtInput")  
  .
  .
 MakeCorrectionEfficiencyCorrPt("/Users/hbelloma/Desktop/FORMEANPT/DataLHC15fpass2/postprocesing/SOpp13TeV_MERGE_newbinsSOPCSO_LHC15fpass2.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 10, "MeanPtInput","kFALSE")  

5.-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  ---- Get the mean pt of Mc 
  ---  Important: change Bool_t isMcTrue=kTRUE;
MakeCorrectionEfficiencyCorrPt("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 0, "MeanPtInputMCTRUEPER11N") 

MakeCorrectionEfficiencyCorrPt("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 1, "MeanPtInputMCTRUEPER11N")
MakeCorrectionEfficiencyCorrPt("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 2, "MeanPtInputMCTRUEPER11N")
.
.
MakeCorrectionEfficiencyCorrPt("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", "PicturesEfficiency_EPOS/EfficiencyCorrection.root", 10, "MeanPtInputMCTRUEPER11N")


   ---- Now make the multiplicity correction for  inel

MakeMultCorrection("MeanPtInput/inel/MeanPtVsNm_inelf.root", "MeanPtInputMCTRUEPER11N/inel/MeanPtVsNm_inelf.root", "BuildingNchRM_PER11/ResponseMatrix_inel.root", "Input: Data(LHC15f pass2) pp #sqrt{s}= 13 TeV", 0, kTRUE, 60, "MeanPtInput/inel");


------ //corrected <pt> vs Ntrk for a given measured So interval -------

-&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

 //make So response matrices
  //measured vs true
  MakeSoRM("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", 0, kFALSE, "SoRM") //inel
  MakeSoRM("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", 1, kFALSE, "SoRM")
  MakeSoRM("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", 2, kFALSE, "SoRM")
  .
  .
  MakeSoRM("SOpp13TeV_MERGE_newbinsSOPCSO_PER114corr.root", 10, kFALSE, "SoRM")
 
  ProduceSoMvsSoTInNtrk("SoRM", kFALSE, "SoRM", "SOpp13TeV_MERGE_newbinsSOPCSO_EPOS4corr.root");

  //corrected <pt> vs Ntrk for a given  So (corrected) interval
 
  MakeMeanPtvsNtrkAtSoM("MeanPtInput", "SoRM/SoRM.root", "MeanPtInput")


     ---- Now make the multiplicity correction for  inel

MakeMultCorrection("MeanPtInput/EsBin0/FullyCorrectedMeanPtVsNm_EsBin0.root", "MeanPtInputMCTRUEPER11N/EsBin0/MeanPtVsNm_EsBin0f.root", "BuildingNchRM_EPOS/ResponseMatrix_inel.root", "Input: Perugia11 (LHC15g3c3) pp #sqrt{s}= 13 TeV", 1, kFALSE, 80, "MeanPtInput/EsBin0");

//MakeMultCorrection("MeanPtInput/EsBin0/FullyCorrectedMeanPtVsNm_EsBin0.root", "MeanPtInputMCTRUEPER11N/EsBin0/MeanPtVsNm_EsBin0.root", "BuildingNchRM_PER11/ResponseMatrix_inel.root", "Input: Data (LHC15f pass2) pp #sqrt{s}= 13 TeV", 1, kFALSE, 60, "MeanPtInput/EsBin0");
.
.
.
//MakeMultCorrection("MeanPtInput/EsBin9/FullyCorrectedMeanPtvsNm_EsBin9.root", "MeanPtInputMCTRUEPER11N/EsBin9/MeanPtVsNm_EsBin9.root", "BuildingNchRM_PER11/ResponseMatrix_EsBin9.root", "Input: Data (LHC15f pass2) pp #sqrt{s}= 13 TeV", 10, kFALSE, 60, "MeanPtInput/EsBin9");


  MakeMeanPtvsNtrkAtSoM(const Char_t * pathToData, const Char_t * nameFileSoRM, const Char_t *outDir)
*/

Double_t pi =  3.14159265358979323846264338327950288419716939937510;
TF1 *fcut[2];

const Int_t first_nchbin = 16; 
const Int_t last_nchbin = 31;


const Int_t init_point = 6; // 15, tpc multiplicity response is estrapolated starting from this bin
const Int_t last_point = 100; // 100, tpc multiplicity response is estrapolated up to nch = 100


Double_t minNtrk0[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,10.0};
Double_t maxNtrk0[nSobins]={70.0,70.0,60.0,50.0,40.0,40.0,40.0,30.0,40.0,30.0};
Double_t minNtrk1[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,10.0};
Double_t maxNtrk1[nSobins]={70.0,70.0,60.0,50.0,40.0,40.0,40.0,40.0,40.0,40.0};
Double_t minNtrk2[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,10.0};
Double_t maxNtrk2[nSobins]={70.0,70.0,60.0,50.0,40.0,40.0,40.0,40.0,40.0,40.0};
Double_t minNtrk3[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk3[nSobins]={50.0,60.0,60.0,60.0,40.0,40.0,40.0,40.0,40.0,40.0};
Double_t minNtrk4[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk4[nSobins]={50.0,60.0,60.0,60.0,40.0,50.0,40.0,40.0,40.0,40.0};
Double_t minNtrk5[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk5[nSobins]={50.0,60.0,60.0,60.0,40.0,50.0,50.0,40.0,40.0,40.0};
Double_t minNtrk6[nSobins]={30.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk6[nSobins]={50.0,60.0,60.0,60.0,40.0,50.0,50.0,40.0,40.0,50.0};
Double_t minNtrk7[nSobins]={20.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk7[nSobins]={40.0,60.0,60.0,60.0,40.0,50.0,50.0,40.0,40.0,50.0};
Double_t minNtrk8[nSobins]={15.0,30.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk8[nSobins]={40.0,50.0,60.0,60.0,40.0,50.0,50.0,40.0,40.0,50.0};
Double_t minNtrk9[nSobins]={20.0,20.0,30.0,30.0,20.0,20.0,20.0,20.0,20.0,20.0};
Double_t maxNtrk9[nSobins]={35.0,40.0,50.0,60.0,40.0,50.0,50.0,40.0,40.0,50.0};


const Double_t absetacmsforana=0.8;
const Double_t eta_for_ntrk = 0.8;
const Double_t eta_for_pt = 0.8;
const Double_t eta_for_es = 0.8;

const Char_t * DetailsMC = "EPOS-LHC, pp @ 13 TeV";

const Int_t nBinsNtrk = 100;
TH1D *hSoMAtNtrk[nBinsNtrk];
TH1D *hSoTAtNtrk[nBinsNtrk];

//const Int_t nMultbins = 13; 
//Double_t Multbins[nMultbins+1]={ 0.0, 1.0, 4.0, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0, 50.0, 60.0, 70.0, 140.0 };

void SetStyle(Bool_t graypalette=kFALSE);
void LoadLibs();
const Int_t n_esa = 12;
const Int_t n_pid = 8;
const Char_t * ParticleLeg[n_pid]={"ch","pi","k","p","k0s","lambda","phi","other"};
const Char_t * ParticleLatex[n_pid]={"all charged","#pi^{+}+#pi^{-}","K^{+}+K^{-}","p+#bar{p}","K_{S}^{0}","#Lambda","#phi","other"};
const Int_t markerSty[5] = {20, 24, 25, 26, 27};
const Double_t markerSize[5] = {1.0, 1.0, 1.0, 1.0, 1.4};
const Color_t ColorPid[n_pid] = {1, kRed, kGreen+2, kBlue, kGreen, kMagenta, kCyan, 1 };







//__________________________________________________________________
void MakeNchResponseMatrix(const Char_t * inFile, const Char_t * outDir, const Int_t i_So){

  //This is the output file
  TFile *foutFunct = 0;

  Long_t *id = 0;
  Long_t *size = 0;
  Long_t *flags = 0;
  Long_t *mt = 0;

    cout<<"initiating ..."<<endl;
  const Char_t * endName = "inel";
  //if(i_so==1)
  //  endName = "wellEs";
  //if(i_So>0)
  //  endName = Form( "EsBin%d", i_So-1 );
  if(i_So==1) endName="ESBin0";
  if(i_So==2) endName="ESBin1";
  if(i_So==3) endName="ESBin2";
  if(i_So==4) endName="ESBin3";
  if(i_So==5) endName="ESBin4";
  if(i_So==6) endName="ESBin5";
  if(i_So==7) endName="ESBin6";
  if(i_So==8) endName="ESBin7";
  if(i_So==9) endName="ESBin8";
  if(i_So==10) endName="ESBin9";

  // Load necessary libraries
  LoadLibs();
  // Set the default style
  SetStyle();




  if(gSystem->GetPathInfo(Form( "%s/ParametrizationsMuAndSigmaVsNch.root", outDir ),id,size,flags,mt)){
    cout << "File " << Form( "%s/ParametrizationsMuAndSigmaVsNch.root", outDir ) << " not found, making file... " << endl;
    
    TFile *fin = FindFileFresh(inFile);
    TH2D *hNchCorr;

    if(i_So==0) hNchCorr = (TH2D *)fin->Get("hRMmultCombAllUn");
    else hNchCorr = (TH2D *)fin->Get(Form("hRMmultCombAllUnSot%d",i_So-1));

    //remove the points with zero Ntrk but non zero 
    for(Int_t binx = 1; binx <= hNchCorr->GetNbinsX(); ++binx){

	    hNchCorr->SetBinContent(binx,1,0);
	    hNchCorr->SetBinError(binx,1,0);

    }



    //original nch response matrix
    TH2D *hNchRMo = 0;
    hNchRMo = (TH2D *)hNchCorr->Clone("hMBNchRM");
    GetResponseMatrix(hNchCorr, hNchRMo);

    TH1D *hNtrk[last_nchbin-first_nchbin+1];

    //graph with mu vs nch
    TGraphErrors *gmu = 0;
    gmu = new TGraphErrors();
    gmu->SetName("gmuvsnch");

    TGraphErrors *gsigma = 0;
    gsigma = new TGraphErrors();
    gsigma->SetName("gsigmavsnch");


    //Create directory
    CreateDir(outDir);



    for(Int_t ix = first_nchbin; ix <= last_nchbin; ++ix){

	    hNtrk[ix-first_nchbin] = 0;
	    hNtrk[ix-first_nchbin] = (TH1D *)hNchRMo->ProjectionY(Form("hNtrk_binNch_%d", ix), ix, ix);


	    Double_t mean = hNtrk[ix-first_nchbin]->GetMean();
	    Double_t sigma = hNtrk[ix-first_nchbin]->GetRMS();
	    //cout<<"mean="<<mean<<"  sigma="<<sigma<<endl;
	    TF1 *fgauss = 0;
	    fgauss = new TF1(Form("gaus%d",ix),"gaus", mean-3.5*sigma, mean+3.5*sigma);
	    fgauss->SetParameter(1,mean);
	    fgauss->SetParameter(2,sigma);

	    TCanvas *cEffy = 0;
	    cEffy = new TCanvas(Form("resolution_Nchbin%d",ix), "Alice Figure Template", 600, 600);
	    cEffy->SetLeftMargin(0.13);
	    cEffy->SetRightMargin(0.06);
	    cEffy->SetBottomMargin(0.15);

	    // Set Titles etc..
	    TH1 * hEffy = 0;
	    hEffy = cEffy->DrawFrame(0,1e-6,100.0, 0.5);


	    hEffy->SetYTitle("P(#it{N}_{trk})");
	    hEffy->SetXTitle(Form("#it{N}_{trk} (|#eta|<%1.1f)",eta_for_ntrk));
	    hEffy->GetXaxis()->SetTitleOffset(1.2);
	    hEffy->GetYaxis()->SetTitleOffset(1.2);

	    hNtrk[ix-first_nchbin]->SetMarkerStyle(24);
	    hNtrk[ix-first_nchbin]->SetMarkerColor(2);
	    hNtrk[ix-first_nchbin]->SetLineColor(2);
	    hNtrk[ix-first_nchbin]->Draw("samep");
	    hNtrk[ix-first_nchbin]->Fit(fgauss, "0", "R");




	    fgauss->SetLineColor(1);
	    fgauss->SetLineWidth(2);
	    fgauss->Draw("samel");

	    TLatex* latex = 0;
	    latex = new TLatex();
	    latex->SetNDC();
	    latex->SetTextAlign(22);
	    latex->SetTextAngle(0);
	    latex->SetTextFont(42);
	    latex->DrawLatex(0.54,0.9,Form("%d < #it{N}_{ch} < %d, |#eta|<%1.1f", ix-1, ix, eta_for_ntrk));
	    latex->DrawLatex(0.45,0.85,Form("#mu = %2.2f", fgauss->GetParameter(1)));
	    latex->DrawLatex(0.45,0.8,Form("#sigma = %2.2f", fgauss->GetParameter(2)));
	    latex->DrawLatex(0.45,0.75,Form("#chi^{2}/n.d.f. = %2.2f", fgauss->GetChisquare()/fgauss->GetNDF()));



	    cEffy->SaveAs(Form("%s/%s_%s.png", outDir, cEffy->GetName(),endName));


	    gmu->SetPoint(ix-first_nchbin, (2*ix-1)/2.0, fgauss->GetParameter(1));
	    gmu->SetPointError(ix-first_nchbin, 0, fgauss->GetParError(1));

	    gsigma->SetPoint(ix-first_nchbin, (2*ix-1)/2.0, fgauss->GetParameter(2));
	    gsigma->SetPointError(ix-first_nchbin, 0, fgauss->GetParError(2));


    }



    TCanvas *cMuVsNch = 0;
    cMuVsNch = new TCanvas("muNtrkVsNch", "Alice Figure Template", 600, 600);
    cMuVsNch->SetLeftMargin(0.13);
    cMuVsNch->SetRightMargin(0.06);
    cMuVsNch->SetBottomMargin(0.15);

    // Set Titles etc..
    TH1 * hMuVsNch = 0;
    hMuVsNch = cMuVsNch->DrawFrame(0,1,50.0, 50.0);

    //fitting function
    //TF1 *fmu = new TF1("fmu","pol1",28-9,last_nchbin-9);
    TF1 *fmu = new TF1("fmu","pol1",first_nchbin,last_nchbin);


    hMuVsNch->SetYTitle("#mu");
    hMuVsNch->SetXTitle(Form("#it{N}_{ch} (|#eta|<%1.1f)",eta_for_ntrk));
    hMuVsNch->GetXaxis()->SetTitleOffset(1.2);
    hMuVsNch->GetYaxis()->SetTitleOffset(1.2);
    gmu->SetMarkerStyle(24);
    gmu->SetMarkerColor(2);
    gmu->SetLineColor(2);
    gmu->SetMarkerSize(1);
    gmu->Fit(fmu, "0", "R");
    fmu->SetLineColor(1);
    fmu->SetLineWidth(2);
    gmu->Draw("samep");
    fmu->Draw("samel");

    TLatex* latex = 0;
    latex = new TLatex();
    latex->SetNDC();
    latex->SetTextAlign(22);
    latex->SetTextAngle(0);
    latex->SetTextFont(42);
    latex->DrawLatex(0.45,0.75,Form("#chi^{2}/n.d.f. = %2.2f", fmu->GetChisquare()/fmu->GetNDF()));



    cMuVsNch->SaveAs(Form("%s/%s_%s.png", outDir, cMuVsNch->GetName(),endName));

    TCanvas *cSigmaVsNch = 0;
    cSigmaVsNch = new TCanvas("sigmaNtrkVsNch", "Alice Figure Template", 600, 600);
    cSigmaVsNch->SetLeftMargin(0.13);
    cSigmaVsNch->SetRightMargin(0.06);
    cSigmaVsNch->SetBottomMargin(0.15);

    //fitting function
    TF1 *fsigma = new TF1("fsigma","pol1",first_nchbin,last_nchbin);

    // Set Titles etc..
    TH1 * hSigmaVsNch = 0;
    hSigmaVsNch = cSigmaVsNch->DrawFrame(0,1,50.0, 5.0);


    hSigmaVsNch->SetYTitle("#sigma");
    hSigmaVsNch->SetXTitle(Form("#it{N}_{ch} (|#eta|<%1.1f)",eta_for_ntrk));
    hSigmaVsNch->GetXaxis()->SetTitleOffset(1.2);
    hSigmaVsNch->GetYaxis()->SetTitleOffset(1.2);

    gsigma->SetMarkerStyle(24);
    gsigma->SetMarkerColor(2);
    gsigma->SetLineColor(2);
    gsigma->SetMarkerSize(1);
    gsigma->Fit(fsigma, "0", "R");
    fsigma->SetLineColor(1);
    fsigma->SetLineWidth(2);
    gsigma->Draw("samep");
    fsigma->Draw("samel");

    latex->DrawLatex(0.45,0.75,Form("#chi^{2}/n.d.f. = %2.2f", fsigma->GetChisquare()/fsigma->GetNDF()));

    cSigmaVsNch->SaveAs(Form("%s/%s_%s.png", outDir, cSigmaVsNch->GetName(),endName));

    foutFunct = new TFile( Form( "%s/ParametrizationsMuAndSigmaVsNch_%s.root", outDir,endName), "RECREATE" );
    foutFunct->cd();
    fmu->Write();
    fsigma->Write();
    hNtrk[3]->Write();
    hNchRMo->Write(); //= (TH2D *)hNchCorr->Clone("hMBNchRM");
    foutFunct->Close();

  }



  cout<<"flag!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

  TFile *fin2 = FindFileFresh(Form( "%s/ParametrizationsMuAndSigmaVsNch_%s.root", outDir,endName ));
  TF1 *fmu = (TF1 *)fin2->Get("fmu");
  TF1 *fsigma = (TF1 *)fin2->Get("fsigma");
  TH1D *hTemplate = (TH1D *)fin2->Get(Form("hNtrk_binNch_%d", first_nchbin+3));
  TH2D *hNchRMo = (TH2D *)fin2->Get("hMBNchRM");
  hTemplate->Reset();


  //build TPC response, according with the results I will start the extrapolation at nch=33, point = 33
  //const Int_t init_point = 33-9;
  const Int_t init_point = 33-18;
  const Int_t last_point = 100;
  const Int_t number_responses = 100000; 
  const Int_t ntotal_extrapolated = last_point - init_point + 1;

  gRandom->SetSeed(0);
  TH1D *hRMrandom[ntotal_extrapolated];
  //take the values of the fitted functions which describe mu and sigma
  TF1 *fmufinal = new TF1("fmufinal","pol1",0,100);
  for(Int_t i_par = 0; i_par < fmufinal->GetNpar(); ++i_par)
	  fmufinal->SetParameter(i_par, fmu->GetParameter(i_par));

  TF1 *fsigmafinal = new TF1("fsigmafinal","pol1",0,100);
  for(Int_t i_par = 0; i_par < fsigmafinal->GetNpar(); ++i_par)
	  fsigmafinal->SetParameter(i_par, fsigma->GetParameter(i_par));

  //cout<<"flag"<<endl;

  for(Int_t bin = init_point; bin <= last_point; ++bin){

	  Double_t mue = (2*fmufinal->Eval(bin) -1) / 2.0;
	  Double_t sigmae = fsigmafinal->Eval(bin);

	  //cout<<"mu="<<mue<<endl;
	  hRMrandom[bin-init_point] = 0;
	  TF1 *fgaussian = 0;
	  fgaussian = new TF1(Form("fgaussian%d",bin),"gaus",0, 100);
	  fgaussian->SetParameter(0, 100);
	  fgaussian->SetParameter(1, mue);
	  fgaussian->SetParameter(2, sigmae);

	  //cout<<fgaussian->GetParameter(2)<<" mean =" << fgaussian->GetParameter(1)<<endl;

	  hRMrandom[bin-init_point] = (TH1D *)hTemplate->Clone(Form("hNtrk_binNch_%d", bin));
	  hRMrandom[bin-init_point]->FillRandom(Form("fgaussian%d",bin), number_responses); 

	  hRMrandom[bin-init_point]->Scale(1.0/hRMrandom[bin-init_point]->GetEntries());


	  TCanvas *cEffy = 0;
	  cEffy = new TCanvas(Form("resolutionExtrapolated_Nchbin%d",bin), "Alice Figure Template", 600, 600);
	  cEffy->SetLeftMargin(0.13);
	  cEffy->SetRightMargin(0.06);
	  cEffy->SetBottomMargin(0.15);

	  // Set Titles etc..
	  TH1 * hEffy = 0;
	  hEffy = cEffy->DrawFrame(0,1e-6,100.0, 0.5);


	  hEffy->SetYTitle("P(#it{N}_{trk})");
	  hEffy->SetXTitle(Form("#it{N}_{trk} (|#eta|<%1.1f)",eta_for_ntrk));
	  hEffy->GetXaxis()->SetTitleOffset(1.2);
	  hEffy->GetYaxis()->SetTitleOffset(1.2);

	  hRMrandom[bin-init_point]->SetMarkerStyle(24);
	  hRMrandom[bin-init_point]->SetMarkerColor(2);
	  hRMrandom[bin-init_point]->SetLineColor(2);
	  hRMrandom[bin-init_point]->Draw("samep");



	  TLatex* latex = 0;
	  latex = new TLatex();
	  latex->SetNDC();
	  latex->SetTextAlign(22);
	  latex->SetTextAngle(0);
	  latex->SetTextFont(42);
	  latex->DrawLatex(0.54,0.9,Form("%d < #it{N}_{ch} < %d, |#eta|<%1.1f (from extrapolation)", bin-1, bin, eta_for_ntrk));
	  latex->DrawLatex(0.45,0.85,Form("mean = %2.2f", hRMrandom[bin-init_point]->GetMean() ) );
	  latex->DrawLatex(0.45,0.8,Form("RMS = %2.2f", hRMrandom[bin-init_point]->GetRMS() ) );    


	  cEffy->SaveAs(Form("%s/%s_%s.png", outDir, cEffy->GetName(),endName));


  }


  TH2D *hNchRM = (TH2D *)hNchRMo->Clone("hMBNchRMExtrapolated");
  //TH2D *hNchRMo = (TH2D *)fin2->Get("hMBNchRM");
  for(Int_t binx = init_point; binx <= last_point; ++binx){

	  for(Int_t biny = 1; biny <= hNchRM->GetNbinsY(); ++biny){

		  Double_t yield = 0;     
		  yield = hRMrandom[binx-init_point]->GetBinContent(biny);
		  Double_t e_yield = 0;     
		  e_yield = hRMrandom[binx-init_point]->GetBinError(biny);

		  hNchRM->SetBinContent(binx,biny,yield);
		  hNchRM->SetBinError(binx,biny,e_yield);
	  }

  }

  //save pictures png and root files

  TCanvas *cNchRM = 0;
  cNchRM = new TCanvas("ExtrapolatedRM", "Alice Figure Template", 600, 600);
  cNchRM->SetLeftMargin(0.12);
  cNchRM->SetRightMargin(0.14);
  cNchRM->SetBottomMargin(0.15);
  cNchRM->SetLogz(1);

  // Set Titles etc..
  TH1 * hBB = 0;
  hBB = cNchRM->DrawFrame(0,0,100,100);


  hBB->SetYTitle(Form("#it{N}_{trk} (|#eta|<%1.1f)",eta_for_ntrk));
  hBB->SetXTitle(Form("#it{N}_{ch} (|#eta|<%1.1f)",eta_for_ntrk));
  hBB->GetXaxis()->SetTitleOffset(1.1);
  hBB->GetYaxis()->SetTitleOffset(1.1);
  hBB->SetZTitle("#it{#it{N}_{trk}}");
  hNchRM->SetZTitle("#it{P}(#it{N}_{trk}) at #it{N}_{ch}");
  hNchRM->GetZaxis()->SetRangeUser(1e-3,1);
  hNchRM->Draw("colz same");
  cNchRM->SaveAs(Form("%s/%s_%s.png", outDir, cNchRM->GetName(),endName));

  TCanvas *cNchRMo = 0;
  cNchRMo = new TCanvas("OriginalRM", "Alice Figure Template", 600, 600);
  cNchRMo->SetLeftMargin(0.12);
  cNchRMo->SetRightMargin(0.14);
  cNchRMo->SetBottomMargin(0.15);
  cNchRMo->SetLogz(1);

  TH1 * hBB2 = 0;
  hBB2 = cNchRMo->DrawFrame(0,0,100,100);


  hBB2->SetYTitle(Form("#it{N}_{trk} (|#eta|<%1.1f)",eta_for_ntrk));
  hBB2->SetXTitle(Form("#it{N}_{ch} (|#eta|<%1.1f)",eta_for_ntrk));
  hBB2->GetXaxis()->SetTitleOffset(1.1);
  hBB2->GetYaxis()->SetTitleOffset(1.1);
  hNchRMo->SetZTitle("#it{P}(#it{N}_{trk}) at #it{N}_{ch}");
  hNchRMo->GetZaxis()->SetRangeUser(1e-3,1);
  hNchRMo->Draw("colz same");


//  cNchRM->SaveAs(Form("%s/%s_%d.png", outDir, cNchRM->GetName(),i_So));
  cNchRMo->SaveAs(Form("%s/%s_%s.png", outDir, cNchRMo->GetName(),endName));

  TFile *fout2 = new TFile(Form("%s/ResponseMatrix_%s.root",outDir,endName), "RECREATE");
  fout2->cd();

  hNchRM->Write();

  fout2->Close();



}

//__________________________________________________________________
void MakeTestEfficiency(const Char_t * inFile, const Char_t * outDir){


  Printf("looking file");
  TFile *fin = FindFileFresh(inFile);
  const Int_t nbinesntrk_2 = 60;
  const Int_t nMultmaxb=9;
  const Int_t a=TMath::Nint(nbinesntrk_2/nMultmaxb);
//  AliESACorrections* test = 0;
//  test = (AliESACorrections*)(fin->Get("CalculationCorrections"));

  TH1D *hEff[nMultbins+1];//Efficiency corrections in multiplicity, z, intervals
  TH1D *hSec[nMultbins+1];//Correction for secondaries in multiplicity, z, intervals
  Printf("getting histos ...");
  for(Int_t i = 0; i < nMultbins; ++i){
    hEff[i] = 0;
   // hEff[i] = test->GetHistsEfficiency(i,0);//second argument, 0: all, 1: q<0, 2: q>0
    if(i==0){
       hEff[i] = (TH1D *)fin->Get("HeffAllMB");
    }
    else{
       hEff[i] = (TH1D *)fin->Get(Form("HeffMult%d",i));
    }
    hSec[i] = 0;
  //  hSec[i] = test->GetHistsMCContamination(i,0);
    //if(i==0) 
    hSec[i] = (TH1D *)fin->Get("hSecAll");
    hEff[i]->SetMarkerColor(100-i);
    hEff[i]->SetLineColor(100-i);
    hEff[i]->SetMarkerStyle(25);
  }
  printf("histos loaded");
  LoadLibs();
  SetStyle();

  TCanvas *cEffy = 0;
  cEffy = new TCanvas("Efficiency", "Alice Figure Template", 600, 600);
  cEffy->SetLeftMargin(0.13);
  cEffy->SetRightMargin(0.06);
  cEffy->SetBottomMargin(0.15);

  TH1 * hEffy = 0;
  hEffy = cEffy->DrawFrame(0,0.0,10.0, 1.4);

  Printf("canvas loaded");
  hEffy->SetYTitle("Efficiency");
  hEffy->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hEffy->GetXaxis()->SetTitleOffset(1.2);
  hEffy->GetYaxis()->SetTitleOffset(1.2);

  hEff[0]->SetMarkerColor(1);
  hEff[0]->SetLineColor(kMagenta);
  hEff[0]->SetLineWidth(2);
  hEff[0]->SetMarkerStyle(25);

  for(Int_t i = 0; i < nMultmaxb; ++i)
    hEff[i*a]->Draw("samep");   // sust por parte entera
  Printf("efficienc printed");
  TF1 *fhpt = new TF1("fhpt","pol1",3,10);
  hEff[0]->Fit(fhpt,"0","0R",3,10);


 
  fhpt->SetLineColor(kMagenta);
  fhpt->SetLineWidth(3);
  fhpt->Draw("samel");


  TLegend * leg02 = 0;
  leg02 = new TLegend(  0.46,  0.18,  0.62, 0.52);
  leg02->SetFillStyle(0);
  leg02->SetTextSize(0.05);
  leg02->SetHeader(DetailsMC);

  leg02->AddEntry(hEff[0], "MB", "P");
  for(Int_t i = 1; i < nMultmaxb; ++i){
    leg02->AddEntry(hEff[i*a], Form("%1.1f < N_{trk} < %1.1f (%1.1f)", Multbins[i*a], Multbins[a*i+1], eta_for_ntrk ), "P");
  }
  leg02->Draw();

  TLatex* latex = 0;
  latex = new TLatex();
  latex->SetNDC();
  latex->SetTextAlign(22);
  latex->SetTextAngle(0);
  latex->SetTextFont(42);
  latex->DrawLatex(0.45,0.9,Form("TPCOnly+TPCrefit cuts (%1.1f)",eta_for_pt));
  TCanvas *cSecy = 0;
  cSecy = new TCanvas("Secondaries", "Alice Figure Template", 600, 600);
  cSecy->SetLeftMargin(0.13);
  cSecy->SetRightMargin(0.06);
  cSecy->SetBottomMargin(0.15);
  TH1 * hSecy = 0;
  hSecy = cSecy->DrawFrame(0,0.0,10.0, 0.4);

  hSecy->SetYTitle("cont secondaries");
  hSecy->SetXTitle("#it{p}_{T} (GeV/#it{c})");
  hSecy->GetXaxis()->SetTitleOffset(1.2);
  hSecy->GetYaxis()->SetTitleOffset(1.2);
  hSec[0]->SetMarkerColor(kMagenta);
  hSec[0]->SetLineColor(kMagenta);
  hSec[0]->SetLineWidth(2);
  hSec[0]->SetMarkerStyle(25);

  for(Int_t i = 0; i < 1; ++i)
  hSec[i]->Draw("samep");
  Printf("secondaries drawn");
  TLegend * leg03 = 0;
  leg03 = new TLegend(  0.46,  0.58,  0.62, 0.92);
  leg03->SetFillStyle(0);
  leg03->SetTextSize(0.05);
  leg03->SetHeader(DetailsMC);

  leg03->AddEntry(hSec[0], "MB", "P");
  leg03->Draw();

  TF1 *fhptsec = new TF1("fhptsec","pol0",3,10);
  hSec[0]->Fit(fhptsec,"0","0R",3,10);

  fhptsec->SetLineColor(kMagenta);
  fhptsec->SetLineWidth(3);
  fhptsec->Draw("samel");


  CreateDir(outDir);

  cSecy->SaveAs( Form( "%s/%s.png", outDir, cSecy->GetName() ) );
  cEffy->SaveAs( Form( "%s/%s.png", outDir, cEffy->GetName() ) );
  
  Printf("saving ...");
  TFile *fout = new TFile( Form( "%s/EfficiencyCorrection.root", outDir ),"RECREATE");
  fout->cd();
  hEff[0]->Write();
  fhpt->Write();
  hSec[0]->Write();
  fhptsec->Write();
  fout->Close();


}


//_______________________________________________________________________________

void MakePerformanceResolutionsVsNtrk(const Char_t * inFile, const Char_t * outDir){

  //const Int_t mult_int[3]={3,10,20};
//const Int_t nMultbins = 13; 
//const Int_t mult_int[nMultbins+1]={ 0.0, 1.0, 4.0, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0, 50.0, 60.0, 70.0, 140.0 };
TFile *fin = FindFileFresh(inFile);
const Int_t nMultmax=11;
  const Color_t colores_mult[13] = {1,100,96,92,88,84,80,76,72,68,64,60,56};
//  const Color_t colores_mult[3] = {2,4,kGreen+2,};
//const Int_t nSobins = 10;
//Int_t so_int[nSobins+1] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

//  Int_t so_int[3] = {0,2,4};
  const Char_t * leg_so[3] = { "0%<#it{S}_{Opc}^{true}<10% ",//, eta_for_es),
                               "50%<#it{S}_{Opc}^{true}<60% ",//, eta_for_es),
                               "#it{S}_{Opc}^{true}>90% "};//, eta_for_es) };


  TH2D *hRSo[nMultbins];
  for(Int_t i_n = 0; i_n < nMultbins; ++i_n){
    hRSo[i_n] = 0;
    hRSo[i_n] =(TH2D*)fin->Get(Form("h2newbins%d",i_n));
    hRSo[i_n]->Sumw2();
  }
  Printf("Getting");
  TH1D *hSoRes[nSobins][nMultbins];//5 true so intervals, 3 multiplicity intervals
  for(Int_t i_n = 0; i_n < nMultbins; ++i_n){
    cout<<"i_n="<<i_n<<endl;
    for(Int_t i_so = 0; i_so < nSobins; ++i_so){
      cout<<"i_so="<<i_so<<endl;
      hSoRes[i_so][i_n] = 0;
      hSoRes[i_so][i_n] = (TH1D *)hRSo[i_n]->ProjectionY(Form("hSoRes_tSo%d_Ntrk%d",i_so,i_n),i_so+1,i_so+1);
      Double_t entries = hSoRes[i_so][i_n]->GetEntries();
      hSoRes[i_so][i_n]->Scale(1.0/entries);

      hSoRes[i_so][i_n]->SetMarkerStyle(20);
      hSoRes[i_so][i_n]->SetMarkerColor(101-i_n);//colores_mult[i_n]);
      hSoRes[i_so][i_n]->SetLineColor(101-i_n);//colores_mult[i_n]);
      hSoRes[i_so][i_n]->SetLineWidth(2);
    }
  }

  Printf("frames");
  TH1D *hframe[3];

  for(Int_t j=0;j<3;++j)
    hframe[j] = new TH1D(Form("hframe_%d",j),Form("hframe_%d",j),1200,-0.1,1.1);
  gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);

  const char* yTitleRaaPions = "measured #it{P}(#it{S}_{O})";
  const char* xTitleRaaPions = Form("measured #it{S}_{O} (|#eta|<%1.1f)", eta_for_es);
  const Int_t nPadX = 3;
  const Int_t nPadY = 1;  //5;
  Float_t noMargin    = 0.0;
  Float_t topMargin   = 0.005;
  Float_t botMargin   = 0.09;
  Float_t leftMargin  = 0.06;
  Float_t rightMargin = 0.01;
  Float_t width       = (1-rightMargin-leftMargin)/nPadX;
  Float_t height      = (1-botMargin-topMargin)/nPadY;

  TCanvas* cRaaPionsAll = 0;
  cRaaPionsAll = new TCanvas("SoResVsNtrks", "Raa Pions", 1100, 500);
  cRaaPionsAll->SetFillStyle(0);
  TPad* pRaaPions[nPadX*nPadY];
  Float_t shift = 0.05;
  cRaaPionsAll->cd();
  TLatex* latex = 0;
  latex = new TLatex();
  latex->SetNDC();
  latex->SetTextAlign(22);
  latex->SetTextAngle(0);
  latex->SetTextFont(42);
  latex->DrawLatex(0.55,0.04,xTitleRaaPions);
  latex->SetTextAngle(90);
  latex->SetTextSize(0.055);
  latex->DrawLatex(0.03,0.58,yTitleRaaPions);
  latex->SetTextSize(0.07);
  latex->SetTextAngle(270);
  latex->SetTextSize(0.04);

  for (Int_t i = 1; i < 4; i++) {
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
    pRaaPions[i-1]->SetBottomMargin(0.08);
    if(i==1)
      pRaaPions[i-1]->SetLeftMargin(0.11);
    cRaaPionsAll->cd();
    pRaaPions[i-1]->Draw();
  }

  for (Int_t index = 1; index < 4; index++) {
    pRaaPions[index-1]->cd();
    pRaaPions[index-1]->SetTickx(1);
    pRaaPions[index-1]->SetTicky(1);
    pRaaPions[index-1]->SetLogy(0);
    hframe[index-1]->GetYaxis()->SetLabelSize(0.076);
    hframe[index-1]->GetXaxis()->SetNdivisions(10);
    hframe[index-1]->GetYaxis()->SetRangeUser(0,1); 
    hframe[index-1]->GetXaxis()->SetLabelSize(0.07);
    hframe[index-1]->GetXaxis()->SetTitle("");
    hframe[index-1]->GetYaxis()->SetTitle("");
    hframe[index-1]->SetLineColor(0);
    hframe[index-1]->Draw();   
    TLegend *leg1 = 0;
    leg1 = new TLegend(0.36,0.65,0.93,0.94);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.07);
    leg1->SetLineColor(kWhite);
    leg1->SetLineWidth(0);
    leg1->SetLineStyle(3);
    leg1->SetShadowColor(kWhite);
    leg1->SetFillColor(kWhite);
    leg1->SetFillStyle(0);
    leg1->SetHeader(leg_so[index-1]);
    for(Int_t i_n = 1; i_n < nMultmax; ++i_n){
    if(index==1)
      hSoRes[0][5*i_n]->Draw("samep");
    if(index==2)
      hSoRes[5][5*i_n]->Draw("samep");
    if(index==3) 
      hSoRes[9][5*i_n]->Draw("samep");
      if(index==1){
        leg1->AddEntry(hSoRes[0][5*i_n],Form("#it{N}_{trk}=%1.1f  (%1.1f)",Multbins[5*i_n], eta_for_ntrk),"P");
      }
    }
    leg1->Draw();

  }


  CreateDir(outDir);
  cRaaPionsAll->SaveAs(Form("%s/%s.png",outDir,cRaaPionsAll->GetName()));




}
//_______________________________________________________-


void MakeCorrectionEfficiencyCorrPt(const Char_t * inFileData, const Char_t * inFileEff, const Int_t i_so, const Char_t * outDir){

        TFile *fin = 0;
        fin = FindFileFresh(inFileData);
        TFile *finEfficiency = 0;
      
        Printf("file or no file?");
        Bool_t isMcTrue=kFALSE;
        Bool_t isEff1=isMcTrue;
          finEfficiency = FindFileFresh(inFileEff);
          TH1D *hEff = (TH1D *)finEfficiency->Get("HeffAllMB");
          TH1D *hSec = (TH1D *)finEfficiency->Get("hSecAll");
          TF1 *fEff = (TF1 *)finEfficiency->Get("fhpt");//pt > 3
          TF1 *fSec = (TF1 *)finEfficiency->Get("fhptsec");//pt > 3


        Printf("file Eff & Sec selected");
        const Char_t* endName = "";
        TString objectName(endName);
        if(i_so==0)
                objectName  += "inel";
        //else if(i_so==1)
        //        objectName += "wellEs";
        else if(i_so>=1)
                objectName +=  Form( "EsBin%d", i_so-1 );

        endName = objectName.Data();

        TH1D *hPtvsNm = 0; 
        hPtvsNm = new TH1D(Form("hPtvsNm_%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f); corrected #LT #it{p}_{T} #GT (GeV/#it{c})", absetacmsforana),200,0,200);

        TH1D *hPtmvsNm = 0; 
        hPtmvsNm = new TH1D(Form("hPtmvsNm_%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f); measured #LT #it{p}_{T} #GT (GeV/#it{c})", absetacmsforana),200,0,200);

        TH1D *hPtvsNmext = 0;
        hPtvsNmext = new TH1D(Form("hPtvsNmext_%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f); measured #LT #it{p}_{T} #GT (GeV/#it{c})", absetacmsforana),200,0,200);
        TH1D *hdivdatatoextmpt=0;
        hdivdatatoextmpt= new TH1D(Form("hdivdatatoextmpt%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f); ", absetacmsforana),200,0,200);
        TH1D *hChi2 = 0;
        hChi2 = new TH1D(Form("hChi2_%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f);  #it{#Chi}^{2}/ndf", absetacmsforana),200,0,200);
        TH1D *hChi2pl = 0;
        hChi2pl = new TH1D(Form("hChi2pl_%s",endName),Form("; #it{N}_{trk} (|#eta|<%1.1f);  #it{#Chi}^{2}/ndf", absetacmsforana),200,0,200);
 
 


        Double_t pStart = 0.14;
        Double_t pStop = 10.0;

        const Int_t binStart = hEff->GetXaxis()->FindBin(pStart+0.01);
        const Int_t binStop  = hEff->GetXaxis()->FindBin(pStop-0.01);
        cout<<"binStart="<<binStart<<"  binStop="<<binStop<<endl;
        CreateDir(outDir);
        CreateDir(Form("%s/%s",outDir,endName));


        cout<<"hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

        const Int_t initbin = 1;
        const Int_t nbinesntrk = 99;
        TH1D *hPtIn[nbinesntrk-initbin+1];
        TH1D *hPtInext[nbinesntrk-initbin+1];
        TH1D *hNorm[nbinesntrk-initbin+1];
        LoadLibs();
        SetStyle();

        TF1* ptfunction2[nbinesntrk-initbin+1];
        TF1* powerlaw4[nbinesntrk-initbin+1];
        TH1D* hdivdatatofit[nbinesntrk-initbin+1];
        Double_t chisptf2[nbinesntrk-initbin+1];
        Double_t chispl4[nbinesntrk-initbin+1];
        Int_t ndfptf2[nbinesntrk-initbin+1];
        Int_t ndfpl4[nbinesntrk-initbin+1];
        TLegend *leg23_1[nbinesntrk-initbin+1]; 
        for(Int_t i_ntrk = initbin; i_ntrk <= nbinesntrk; ++i_ntrk){

                hNorm[i_ntrk-initbin] = 0;
                hNorm[i_ntrk-initbin] =(TH1D* )fin->Get(Form("hSoM%d",i_ntrk));//kTRUE gives hsot at Ntrk
                cout<<"i_ntrk = "<<i_ntrk<<endl;
                Double_t nev = hNorm[i_ntrk-initbin]->GetEntries();
                cout<<"nev="<<nev<<endl;
                hPtIn[i_ntrk-initbin] = 0;
                if(i_so==0){
                  if(isMcTrue)hPtIn[i_ntrk-initbin] =(TH1D* )fin->Get(Form("hMcInMult%d",i_ntrk)); //hMcInMultTrue
                  else{
                    hPtIn[i_ntrk-initbin] =(TH1D* )fin->Get(Form("hMcOutMult%d",i_ntrk));
                    Printf("not MC TRUE");
                    hPtInext[i_ntrk-initbin] =(TH1D *)hPtIn[i_ntrk-initbin]->Clone(Form("hPtInext%d",i_ntrk)); 
                  }
                }
		else{
                   if(isMcTrue) hPtIn[i_ntrk-initbin] =(TH1D* )fin->Get(Form("hMcInMult%dES%d",i_ntrk, i_so-1)); //hMcTrueMult%dES%d
                   else{
                     hPtIn[i_ntrk-initbin] =(TH1D* )fin->Get(Form("hMcOutMult%dES%d",i_ntrk, i_so-1));
                    Printf("not MC TRUE");
                    hPtInext[i_ntrk-initbin] =(TH1D *)hPtIn[i_ntrk-initbin]->Clone(Form("hPtInext%d",i_ntrk));
                    }
		}
                Double_t totalpt = 0; 
                Double_t totalyield = 0; 
                Double_t e_totalpt = 0; 
                Double_t e_totalyield = 0; 
                Double_t totalptm = 0; 
                Double_t totalyieldm = 0; 
                Double_t e_totalptm = 0; 

                Double_t e_totalyieldm = 0; 
                for(Int_t bin = binStart; bin <= binStop; ++bin){    
                       Double_t pt =  hPtIn[i_ntrk-initbin]->GetBinCenter(bin);  
                     //  cout<<"  low edge, pt="<<hPtIn[i_ntrk-initbin]->GetBinLowEdge(bin)<<"   pt="<<pt<<endl;
                       Double_t dpt =  hPtIn[i_ntrk-initbin]->GetBinWidth(bin);  
                       Double_t deta = 1.6; 
                       Double_t yield = hPtIn[i_ntrk-initbin]->GetBinContent(bin);
                       Double_t e_yield = hPtIn[i_ntrk-initbin]->GetBinError(bin);
                           Double_t efficiency = hEff->GetBinContent(bin);
                           if(pt>3)
                                efficiency = fEff->Eval(pt);
                           Double_t contsec = hSec->GetBinContent(bin); 
                           if(pt>3)
                                contsec = fSec->Eval(pt);
                 
                       totalptm += yield*pt;
                       totalyieldm += yield;

                       e_totalptm += TMath::Power(e_yield*pt,2);
                       e_totalyieldm += TMath::Power(e_yield,2);
                        yield /= efficiency;
                        e_yield /= efficiency;

                        yield *= (1.0-contsec);
                        e_yield *= (1.0-contsec);
                       totalpt += yield*pt;
                        totalyield += yield;

                        e_totalpt += TMath::Power(e_yield*pt,2);
                        e_totalyield += TMath::Power(e_yield,2);

                        yield /= (2*pi*pt*dpt*deta*nev);
                        e_yield /= (2*pi*pt*dpt*deta*nev);

                        //cout<<"bin="<<bin<<"yield="<<yield<<endl;
                        hPtIn[i_ntrk-initbin]->SetBinContent(bin, yield);
                        hPtIn[i_ntrk-initbin]->SetBinError(bin, e_yield);

                }
                Double_t meanpt = 0;
                cout<<"totalpt="<<totalpt<<"totalyield="<<totalyield<<endl;
		 if(totalyield>0)
                        meanpt = totalpt / totalyield;
                Double_t e_meanpt = 0;
                if(totalyield>0)
                        e_meanpt = TMath::Power( meanpt, 2 )*( e_totalpt/(totalpt*totalpt) + e_totalyield/(totalyield*totalyield) );
                cout<<"bin="<<i_ntrk<<"   meanpt="<<meanpt<<endl;
                hPtvsNm->SetBinContent(i_ntrk+1,meanpt);
                hPtvsNm->SetBinError(i_ntrk+1,TMath::Sqrt(e_meanpt));

               //hdivdatatoextmpt=(TH1D *)hPtvsNm->Clone("hdivdatatoextmpt");
                Double_t meanptm = 0;
                if(totalyieldm>0)
                        meanptm = totalptm / totalyieldm;
                Double_t e_meanptm = 0;
                if(totalyieldm>0)
                        e_meanptm = TMath::Power( meanptm, 2 )*( e_totalptm/(totalptm*totalptm) + e_totalyieldm/(totalyieldm*totalyieldm) );
                hPtmvsNm->SetBinContent(i_ntrk+1,meanptm);
                hPtmvsNm->SetBinError(i_ntrk+1,TMath::Sqrt(e_meanptm));
// /*
                // Hagerdon
                ptfunction2[i_ntrk-initbin] = new TF1(Form("ptfunction2_%d",i_ntrk),"[0]*(x/sqrt(0.14*0.14+x*x))*(1+(x)/([2]))^((-1) * [1])",0.0,10.0);
                // power law
                powerlaw4[i_ntrk-initbin] = new TF1(Form("powerlaw4_%d",i_ntrk),"[0]*x^[1]",0.0,10.0);

                ptfunction2[i_ntrk-initbin]->SetParameter(0,80);
		ptfunction2[i_ntrk-initbin]->SetParameter(1,4.9);
		ptfunction2[i_ntrk-initbin]->SetParameter(2,0.71);
		ptfunction2[i_ntrk-initbin]->SetLineWidth(2);
                powerlaw4[i_ntrk-initbin]->SetParameter(0,54.931915);
                powerlaw4[i_ntrk-initbin]->SetParameter(1,-5.2);

                hPtIn[i_ntrk-initbin]->Fit(Form("ptfunction2_%d",i_ntrk),"MN","",0.16,2.0);
                hPtIn[i_ntrk-initbin]->Fit(Form("powerlaw4_%d",i_ntrk),"MN2","",2.0,10.0);
                hdivdatatofit[i_ntrk-initbin]=(TH1D *)hPtIn[i_ntrk-initbin]->Clone(Form("hdivdatatofit%d",i_ntrk));


                chisptf2[i_ntrk-initbin]=ptfunction2[i_ntrk-initbin]->GetChisquare();
                chispl4[i_ntrk-initbin]=powerlaw4[i_ntrk-initbin]->GetChisquare();
                ndfptf2[i_ntrk-initbin]=ptfunction2[i_ntrk-initbin]->GetNDF();
                ndfpl4[i_ntrk-initbin]=powerlaw4[i_ntrk-initbin]->GetNDF();
                cout<<"chi2ptf2="<<chisptf2[i_ntrk-initbin]<<"ndfptf2="<<ndfptf2[i_ntrk-initbin]<<endl;
                hChi2->SetBinContent(i_ntrk-initbin,chisptf2[i_ntrk-initbin]/ndfptf2[i_ntrk-initbin]);
                hChi2pl->SetBinContent(i_ntrk-initbin,chispl4[i_ntrk-initbin]/ndfpl4[i_ntrk-initbin]);

		Double_t totalpt2 = 0;
                Double_t totalyield2 = 0;
                Double_t e_totalpt2 = 0;
                Double_t e_totalyield2 = 0;
                for(Int_t bin = binStart; bin <= binStop; ++bin){ 
                      Double_t pt2 = hPtIn[i_ntrk-initbin]->GetBinCenter(bin);
                 //      cout<<"  low edge, pt="<<hPtIn[i_ntrk-initbin]->GetBinLowEdge(bin)<<"pt="<<pt2<<endl;
                      Double_t yield2 = ptfunction2[i_ntrk-initbin]->Eval(pt2);
                      if(pt2>=2.0)  yield2 = powerlaw4[i_ntrk-initbin]->Eval(pt2);
                      Double_t e_yield2 = hPtIn[i_ntrk-initbin]->GetBinError(bin);
                      Double_t dpt =  hPtIn[i_ntrk-initbin]->GetBinWidth(bin);
                      Double_t deta = 1.6;
                        e_totalpt2 += TMath::Power(e_yield2*pt2,2);
                        e_totalyield2 += TMath::Power(e_yield2,2);;
                        hPtInext[i_ntrk-initbin]->SetBinContent(bin, yield2);
                        hPtInext[i_ntrk-initbin]->SetBinError(bin, e_yield2);
                        yield2 =yield2*(2*pi*pt2*dpt*deta*nev);
                        totalpt2 += yield2*pt2;
                        totalyield2 += yield2;
                }
                Double_t meanpt2 = 0;
                cout<<"totalpt="<<totalpt2<<"totalyield="<<totalyield2<<endl;
                 if(totalyield2>0)
                        meanpt2 = totalpt2 / totalyield2;
                Double_t e_meanpt2 = 0;
                if(totalyield2>0)
                        e_meanpt2 = TMath::Power( meanpt2, 2 )*( e_totalpt2/(totalpt2*totalpt2) + e_totalyield2/(totalyield2*totalyield2) );
                cout<<"bin="<<i_ntrk<<"   meanpt="<<meanpt2<<endl;
                hPtvsNmext->SetBinContent(i_ntrk+1,meanpt2);
                hPtvsNmext->SetBinError(i_ntrk+1,TMath::Sqrt(e_meanpt2));
                hdivdatatofit[i_ntrk-initbin]->Divide(hPtInext[i_ntrk-initbin]);
                hdivdatatoextmpt->Divide(hPtvsNm,hPtvsNmext);

// *

TH1D *hframe[2][nMultbins+1];
TF1 *funo = new TF1("funo","0.0+pol0",1,10);
  funo->SetLineColor(1);
  funo->SetLineStyle(2);
  funo->SetLineWidth(2);
  TCanvas* cRaaPionsAll[nMultbins+1];

  for(Int_t j=0;j<2;++j)
  hframe[j][i_ntrk-initbin] = new TH1D(Form("hframe_%d_%d",j,(i_ntrk-initbin)),Form("hframe_%d_%d",j,(i_ntrk-initbin)),nPtBins,xBins);
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
  cRaaPionsAll[i_ntrk-initbin] = new TCanvas(Form("cspectra_%d",i_ntrk-initbin), "Raa Pions", 550, 800);
  cRaaPionsAll[i_ntrk-initbin]->SetFillStyle(0);
  TPad* pRaaPions[nPadX*nPadY][i_ntrk-initbin];
  Float_t shift = 0.05;
  const char* yTitleRaaPions = "Ratio to fit  d^{2}#it{N}_{ch} / (N_{ev} 2#pi#it{p}_{T}d#etad#it{p}_{T}) (GeV/#it{c})^{-2}";
// Form(" corrected - measured  #LT #it{p}_{T} #GT (GeV/#it{c}), (|#eta|<%1.1f)", eta_for_pt);
  const char* xTitleRaaPions ="(corrected) #it{p}_{T} (GeV/#it{c})";
// Form("N_{ch} (N_{trk}), (|#eta|<%1.1f)", eta_for_ntrk);
  cRaaPionsAll[i_ntrk-initbin]->cd();

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
     pRaaPions[i][i_ntrk-initbin] = new TPad(Form("padRaa%d_%d",i,i_ntrk-initbin),"", x1, y1, x2, y2, 0, 0, 0);
     Float_t mBot = noMargin;
     Float_t mTop = noMargin;
     Float_t mLeft = noMargin;
     Float_t mRight = noMargin;
     if(iY==0)       mTop   = shift;
     if(iY==nPadY-1) mBot   = shift;
     if(iX==0)       mLeft  = 0.08;
     if(iX==nPadX-1) mRight = 0.08;
     pRaaPions[i][i_ntrk-initbin]->SetBottomMargin(mBot);
     pRaaPions[i][i_ntrk-initbin]->SetTopMargin(mTop);
     pRaaPions[i][i_ntrk-initbin]->SetLeftMargin(mLeft);
     pRaaPions[i][i_ntrk-initbin]->SetRightMargin(mRight);
     pRaaPions[i][i_ntrk-initbin]->SetFillStyle(0);
     pRaaPions[i][i_ntrk-initbin]->SetLeftMargin(0.13);
     if(i==2)  pRaaPions[i][i_ntrk-initbin]->SetBottomMargin(0.08);
     cRaaPionsAll[i_ntrk-initbin]->cd();
     pRaaPions[i][i_ntrk-initbin]->Draw();

  } Printf("end first for");
    for (Int_t index = 1; index < 3; index++) {
     Printf("otro for");
    pRaaPions[index][i_ntrk-initbin]->cd();
    pRaaPions[index][i_ntrk-initbin]->SetTickx(1);
    pRaaPions[index][i_ntrk-initbin]->SetTicky(1);
    pRaaPions[index][i_ntrk-initbin]->SetLogy(0);
    pRaaPions[index][i_ntrk-initbin]->SetLogx();
    if(index==2) pRaaPions[index][i_ntrk-initbin]->SetGridy();
    hframe[index][i_ntrk-initbin]->GetYaxis()->SetLabelSize(0.076);
    hframe[index][i_ntrk-initbin]->GetXaxis()->SetTitle("");
    hframe[index][i_ntrk-initbin]->GetYaxis()->SetTitle("");
    hframe[index][i_ntrk-initbin]->GetXaxis()->SetRangeUser(0.10,10);
    hframe[index][i_ntrk-initbin]->SetLineColor(0);
    if(index == 1){
      pRaaPions[index][i_ntrk-initbin]->SetLogy();
      Printf("if");
      hframe[index][i_ntrk-initbin]->Draw();
      Printf("flag");
      hframe[index][i_ntrk-initbin]->GetYaxis()->SetRangeUser(1e-6,1000);
	hPtIn[i_ntrk-initbin]->SetMarkerStyle(24);
        hPtIn[i_ntrk-initbin]->SetMarkerColor(2);
        hPtIn[i_ntrk-initbin]->SetLineColor(2);
        hPtInext[i_ntrk-initbin]->SetMarkerStyle(22); 
        hPtInext[i_ntrk-initbin]->SetMarkerColor(kGreen);
        hPtInext[i_ntrk-initbin]->SetLineColor(kGreen);
        ptfunction2[i_ntrk-initbin]->SetLineColor(kBlue);
        powerlaw4[i_ntrk-initbin]->SetLineWidth(2);
        powerlaw4[i_ntrk-initbin]->SetLineColor(kGreen);
        powerlaw4[i_ntrk-initbin]->SetLineStyle(7); //was 7 for dashed
        powerlaw4[i_ntrk-initbin]->SetRange(2,10);
        powerlaw4[i_ntrk-initbin]->Draw("SAME");
        ptfunction2[i_ntrk-initbin]->SetLineStyle(1); //was 7 for dashed
        ptfunction2[i_ntrk-initbin]->SetRange(0.15,10);
        ptfunction2[i_ntrk-initbin]->Draw("SAME");
        leg23_1[i_ntrk-initbin] = new TLegend(0.5,0.6,0.9,0.9);
        leg23_1[i_ntrk-initbin]->SetHeader(Form("pp, %s for N_{trk}=%d, #sqrt{s} = 13 TeV, | #eta | < 0.8",endName,i_ntrk));
                //leg23_1[i_ntrk-initbin]->AddEntry("ALICE data","LP");
        leg23_1[i_ntrk-initbin]->AddEntry(hPtIn[i_ntrk-initbin],"Data","p");
        leg23_1[i_ntrk-initbin]->AddEntry(hPtInext[i_ntrk-initbin],"Data extrap","p");
        leg23_1[i_ntrk-initbin]->AddEntry(ptfunction2[i_ntrk-initbin],"mod. Hagedorn fit","L");
        leg23_1[i_ntrk-initbin]->AddEntry(powerlaw4[i_ntrk-initbin],"power law fit, p_{T} > 3 GeV/c","L");
        leg23_1[i_ntrk-initbin]->SetFillColor(0);
        leg23_1[i_ntrk-initbin]->SetLineColor(0);
               // leg23_1[i_ntrk-initbin]->SetTextSize(1.1);//size
        leg23_1[i_ntrk-initbin]->Draw();
        hPtIn[i_ntrk-initbin]->Draw("samep");
        hPtInext[i_ntrk-initbin]->Draw("samep");
        cRaaPionsAll[i_ntrk-initbin]->SaveAs(Form("%s/%s/%s.png",outDir,endName,cRaaPionsAll[i_ntrk-initbin]->GetName()));
        Printf("flag2");
    }
    else{
      Printf("else");
      hframe[index][i_ntrk-initbin]->GetYaxis()->SetRangeUser(0.0,2.0);
      hframe[index][i_ntrk-initbin]->GetXaxis()->SetLabelSize(0.08);
      hframe[index][i_ntrk-initbin]->Draw();
      funo->Draw("same");
      hdivdatatofit[i_ntrk-initbin]->SetLineWidth(2);
      hdivdatatofit[i_ntrk-initbin]->SetMarkerStyle(34);
      hdivdatatofit[i_ntrk-initbin]->Draw("samep");
    }

   
   }Printf("out index");

/*
                TCanvas *cPtCorrected = 0;
                cPtCorrected = new TCanvas(Form("PtCorrected_atNm%d",i_ntrk), "Alice Figure Template", 600, 600);
                cPtCorrected->SetLeftMargin(0.13);
                cPtCorrected->SetRightMargin(0.06);
                cPtCorrected->SetBottomMargin(0.15);
                cPtCorrected->SetLogy(1);
*/

		//powerlaw4->SetLineStyle(7);
		//powerlaw4->SetRange(3,10);
		//powerlaw4->DrawCopy("SAME");

		//ptfunction2->SetLineStyle(1);
		//ptfunction2->SetRange(0,4);
		//ptfunction2->DrawCopy("SAME");

//                TH1 * hFrame = 0;
//                hFrame = cPtCorrected->DrawFrame(0,1e-6,10.0, 1000);
//                hFrame->SetYTitle("d^{2}#it{N}_{ch} / (N_{ev} 2#pi#it{p}_{T}d#etad#it{p}_{T}) (GeV/#it{c})^{-2}");
//                hFrame->SetXTitle("(corrected) #it{p}_{T} (GeV/#it{c})");
//                hFrame->GetXaxis()->SetTitleOffset(1.2);
//                hFrame->GetYaxis()->SetTitleOffset(1.2);
//                hPtIn[i_ntrk-initbin]->SetMarkerStyle(24);
//                hPtIn[i_ntrk-initbin]->SetMarkerColor(2);
//                hPtIn[i_ntrk-initbin]->SetLineColor(2);
//                hPtInext[i_ntrk-initbin]->SetMarkerStyle(22); 
//                hPtInext[i_ntrk-initbin]->SetMarkerColor(kGreen);
//                hPtInext[i_ntrk-initbin]->SetLineColor(kGreen);
/*
                chisptf2[i_ntrk-initbin]=ptfunction2[i_ntrk-initbin]->GetChisquare();
                chispl4[i_ntrk-initbin]=powerlaw4[i_ntrk-initbin]->GetChisquare();
                ndfptf2[i_ntrk-initbin]=ptfunction2[i_ntrk-initbin]->GetNDF();
                ndfpl4[i_ntrk-initbin]=powerlaw4[i_ntrk-initbin]->GetNDF();
                cout<<"chi2ptf2="<<chisptf2[i_ntrk-initbin]<<"ndfptf2="<<ndfptf2[i_ntrk-initbin]<<endl;
                hChi2->SetBinContent(i_ntrk-initbin,chisptf2[i_ntrk-initbin]/ndfptf2[i_ntrk-initbin]);
                hChi2pl->SetBinContent(i_ntrk-initbin,chispl4[i_ntrk-initbin]/ndfpl4[i_ntrk-initbin]);
*/
            //    /*
/*		ptfunction2[i_ntrk-initbin]->SetLineColor(kBlue);
                powerlaw4[i_ntrk-initbin]->SetLineWidth(2);
                powerlaw4[i_ntrk-initbin]->SetLineColor(kGreen);
                powerlaw4[i_ntrk-initbin]->SetLineStyle(7); //was 7 for dashed
                powerlaw4[i_ntrk-initbin]->SetRange(2,10);
                powerlaw4[i_ntrk-initbin]->Draw("SAME");
                ptfunction2[i_ntrk-initbin]->SetLineStyle(1); //was 7 for dashed
                ptfunction2[i_ntrk-initbin]->SetRange(0.15,10);
                ptfunction2[i_ntrk-initbin]->Draw("SAME");
*/
/*
                leg23_1[i_ntrk-initbin] = new TLegend(0.5,0.6,0.9,0.9);
                leg23_1[i_ntrk-initbin]->SetHeader(Form("pp, %s for N_{trk}=%d, #sqrt{s} = 13 TeV, | #eta | < 0.8",endName,i_ntrk));
                leg23_1[i_ntrk-initbin]->AddEntry("ALICE data","LP");
                leg23_1[i_ntrk-initbin]->AddEntry(ptfunction2[i_ntrk-initbin],"mod. Hagedorn fit","L");
                leg23_1[i_ntrk-initbin]->AddEntry(powerlaw4[i_ntrk-initbin],"power law fit, p_{T} > 3 GeV/c","L");
                leg23_1[i_ntrk-initbin]->SetFillColor(0);
                leg23_1[i_ntrk-initbin]->SetLineColor(0);
                leg23_1[i_ntrk-initbin]->SetTextSize(1.1);//size
                leg23_1[i_ntrk-initbin]->Draw();

                hPtIn[i_ntrk-initbin]->Draw("samep");

                cPtCorrected->SaveAs(Form("%s/%s/%s.png",outDir,endName,cPtCorrected->GetName()));
*/
////////////////////////////////////////////////////////////////////////////////////////////
                // Yield and Meanpt from fit

/*
                Double_t totalpt2 = 0; 
                Double_t totalyield2 = 0; 
                Double_t e_totalpt2 = 0; 
                Double_t e_totalyield2 = 0; 
                for(Int_t bin = binStart; bin <= binStop; ++bin){
                  
                      Double_t pt2 = hPtIn[i_ntrk-initbin]->GetBinCenter(bin);
                 //      cout<<"  low edge, pt="<<hPtIn[i_ntrk-initbin]->GetBinLowEdge(bin)<<"pt="<<pt2<<endl;
                      Double_t yield2 = ptfunction2[i_ntrk-initbin]->Eval(pt2);
                      if(pt2>=2.0)  yield2 = powerlaw4[i_ntrk-initbin]->Eval(pt2);
                      Double_t e_yield2 = hPtIn[i_ntrk-initbin]->GetBinError(bin);
                      Double_t dpt =  hPtIn[i_ntrk-initbin]->GetBinWidth(bin);
                      Double_t deta = 1.6;
                        e_totalpt2 += TMath::Power(e_yield2*pt2,2);
                        e_totalyield2 += TMath::Power(e_yield2,2);
                        //cout<<"bin="<<bin<<"yield="<<yield<<endl;
                        hPtInext[i_ntrk-initbin]->SetBinContent(bin, yield2);
                        hPtInext[i_ntrk-initbin]->SetBinError(bin, e_yield2);
                        yield2 =yield2*(2*pi*pt2*dpt*deta*nev);
                        totalpt2 += yield2*pt2;
                        totalyield2 += yield2;
 
                }
                Double_t meanpt2 = 0;
                cout<<"totalpt="<<totalpt2<<"totalyield="<<totalyield2<<endl;
                 if(totalyield2>0)
                        meanpt2 = totalpt2 / totalyield2;
                Double_t e_meanpt2 = 0;
                if(totalyield2>0)
                        e_meanpt2 = TMath::Power( meanpt2, 2 )*( e_totalpt2/(totalpt2*totalpt2) + e_totalyield2/(totalyield2*totalyield2) );
                cout<<"bin="<<i_ntrk<<"   meanpt="<<meanpt2<<endl;
                hPtvsNmext->SetBinContent(i_ntrk+1,meanpt2);
                hPtvsNmext->SetBinError(i_ntrk+1,TMath::Sqrt(e_meanpt2));
                hdivdatatofit[i_ntrk-initbin]->Divide(hPtInext[i_ntrk-initbin]);
                hdivdatatoextmpt->Divide(hPtvsNm,hPtvsNmext);
*/
        }
// ---------
        TCanvas *cBB = 0;
        cBB = new TCanvas("MeanPtVsNm", "Alice Figure Template", 600, 600);
        cBB->SetLeftMargin(0.15);
        TH1 * hBB = 0;
        hBB = cBB->DrawFrame(0,0.4,100, 1.2);
        hBB->SetXTitle(Form("#it{N}_{trk}, (|#eta|<%1.1f)", eta_for_ntrk));
        hBB->SetYTitle(Form("corrected (Eff&sec) #LT #it{p}_{T} #GT (GeV/#it{c}), |#eta|<%1.1f", eta_for_pt));
        hBB->GetYaxis()->SetTitleOffset(1.5);
        hBB->GetXaxis()->SetTitleOffset(1.05);
        hPtvsNm->SetMarkerSize(1.0);
        hPtvsNm->SetMarkerStyle(20);
        hPtvsNm->SetMarkerColor(kBlue);
        hPtvsNm->Draw("samep");
        hPtvsNmext->Draw("samep");
         cBB->SaveAs(Form("%s/%s/%s.png",outDir,endName,cBB->GetName()));

        TFile *fout = new TFile(Form("%s/%s/MeanPtVsNm_%s.root",outDir,endName,endName),"RECREATE");
        fout->cd();
        hPtvsNm->Write();
        hPtmvsNm->Write();
        hPtvsNmext->Write();
        hdivdatatoextmpt->Write();
        hChi2->Write();
        hChi2pl->Write();
        for(Int_t i_ntrk = initbin; i_ntrk <= nbinesntrk; ++i_ntrk){
          hPtIn[i_ntrk-initbin]->Write();
          hPtInext[i_ntrk-initbin]->Write();
          ptfunction2[i_ntrk-initbin]->Write();
          powerlaw4[i_ntrk-initbin]->Write();
          hdivdatatofit[i_ntrk-initbin]->Write();
        }
        fout->Close();

}

//_________________________________________________________________________

void MakeMultCorrection(const Char_t * inFile, const Char_t * inMCFile, const Char_t * inFileRM, const Char_t * titleHisto, const Int_t i_so, Bool_t isInel, Double_t nchcut, const Char_t * outDir){
 
  
  cout<<"initiating ..."<<endl;
  const Char_t * endName = "inel";
  //if(i_so==1)
  //  endName = "wellEs";
  if(i_so>0)
    endName = Form( "EsBin%d", i_so-1 );


  cout<<"starting declaration of Histograms"<<endl; 
  //for MC
  TFile *finMC = 0;
  TH1D *htrue = 0;
  TH1D *hratio = 0;

  if(inMCFile){
    finMC = FindFileFresh(inMCFile);
  
  Bool_t isMCTrue=kTRUE;
  if(isMCTrue)  htrue =(TH1D *)finMC->Get("hPtmvsNm");// this is extrapo // Get(Form("hPtmvsNm_%s",endName)); // hPtmvsNm_%s this right
   // average true mean pt as a function of the true multiplicity
  else htrue =(TH1D *)finMC->Get(Form("hPtmvsNm_%s",endName)); // check!!!!!!
   // average true mean pt as a function of the measured multiplicity
 
   hratio = (TH1D *)htrue->Clone("hratioTocorrected");
  }
  cout<<"cloned hratio"<<endl;

  TF1 *fcutcorr = new TF1("fcutcorr",Form("(x<%2.2f)*(1.0+pol0)+(x>%2.2f)*(0.0+pol0)",nchcut,nchcut),0,100);
  TF1 *funo = new TF1("funo","1.0+pol0",1,100);
  funo->SetLineColor(1);
  funo->SetLineStyle(2);
  funo->SetLineWidth(2);
  TFile *fmeasurement = FindFileFresh(inFile);
  TFile *fcorrection = FindFileFresh(inFileRM);
  TH1D *hPtVsNm = 0;
  if(isInel)
    hPtVsNm = (TH1D *)fmeasurement->Get("hPtvsNm");// this is extrapo //Get(Form("hPtvsNm_%s",endName));
  else{ 
    Printf("isInel kFALSE");
    hPtVsNm = (TH1D *)fmeasurement->Get(Form("hFullyCorrectedPtvsNm_EsBin%d",i_so-1));//Get("hPtvsNm");//Get(Form("hFullyCorrectedPtvsNm_EsBin%d",i_so-1));
  }
  Printf("hPtVsNm selected."); 
  TH1D *hPtmVsNm = 0;
  hPtmVsNm = (TH1D *)fmeasurement->Get("hPtmvsNm");//Get("hPtmvsNm");//this is extrap //
  
  TH2D *hRM = (TH2D *)fcorrection->Get("hMBNchRMExtrapolated");

  Printf("hPtmvs 2");
  TH1D *hPtVsNch = (TH1D *)hPtVsNm->Clone("hPtVsNch"); // Problem
  Printf("hPtmvs 3");
  GetWeighting( hRM, hPtVsNm, hPtVsNch );
  Printf("hPtmvs 4");
//apply a cut to the corrected result
  hPtVsNch->Multiply(fcutcorr);
 cout<<"geted some hists"<<endl;

  if(inMCFile){
    hratio = (TH1D *)htrue->Clone("hratioTocorrected");
    hratio->Divide(hPtVsNch);
  }

  cout<<"printing histos ...."<<endl;
  TH1D *hframe[2];

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
  
  cout<<"declaring canvas"<<endl;

  TCanvas* cRaaPionsAll = new TCanvas("closureTest", "Raa Pions", 550, 800);
  cRaaPionsAll->SetFillStyle(0);

  TPad* pRaaPions[nPadX*nPadY];
  Float_t shift = 0.05;
 
  const char* yTitleRaaPions = Form("true / corrected  #LT #it{p}_{T} #GT (GeV/#it{c}), (|#eta|<%1.1f)", eta_for_pt);
  const char* xTitleRaaPions = Form("N_{ch}, (|#eta|<%1.1f)", eta_for_ntrk);
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
  Printf("iniciando for 2");
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
      Printf("Markers hPtmVsNm "); 
      hPtmVsNm->SetMarkerStyle(24);
      Printf("Markers Style ");
      hPtmVsNm->SetLineColor(kBlue);
      Printf("Markers LineColor ");
      hPtmVsNm->SetMarkerColor(kBlue);
      Printf("Markers Color ");
      Printf("... hPtmVsNm ");
  //    hPtmVsNm->Draw("samep");
      Printf("hPtmVsNm ...");
      hPtVsNch->SetMarkerStyle(21);
      hPtVsNch->SetMarkerColor(2);
      hPtVsNch->SetLineColor(2);
      hPtVsNch->SetLineWidth(2);
      Printf("... hPtVsNm");
      hPtVsNch->Draw("samep");
      Printf("sames");
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
      leg1->SetHeader(titleHisto);
      leg1->AddEntry(hPtVsNch,"corrected #LT #it{p}_{T} #GT vs #it{N}_{ch}","P");
      Printf("asking inMCFILE");
      if(inMCFile){
	htrue->SetMarkerStyle(25);
	htrue->SetMarkerColor(1);
	htrue->SetLineColor(1);
	htrue->SetLineWidth(2);
	htrue->Draw("samep");
	leg1->AddEntry(htrue,"true #LT #it{p}_{T} #GT vs #it{N}_{ch}","P");
      }
//      leg1->AddEntry(hPtmVsNm,"uncorrected #LT #it{p}_{T} #GT vs #it{N}_{trk}","P");
      leg1->Draw();

    }
    else{
      Printf("else");
      hframe[index-1]->GetYaxis()->SetRangeUser(0.905,1.105);
      hframe[index-1]->GetXaxis()->SetLabelSize(0.08);
      hframe[index-1]->Draw();
      funo->Draw("same");
      hratio->SetLineColor(1);
      hratio->SetLineWidth(2);
      hratio->SetMarkerStyle(21);
      hratio->Draw("samep");
    }

  }

  cout<<"creating output directory"<<endl;
  CreateDir(outDir);
  cRaaPionsAll->SaveAs(Form("%s/%s.png",outDir,cRaaPionsAll->GetName()));
  
  TFile *fout = 0;
  fout = new TFile(Form("%s/FullyCorrectedCorrelation.root",outDir),"RECREATE");
  fout->cd();
  hPtVsNch->Write();
  fout->Close();


}

//_____________________________________________________________________
void MakeSoRM(const Char_t * inFile, Int_t binSo, Bool_t isInverted, const Char_t * outDir){
  gStyle->SetOptStat(0);
  CreateDir(outDir);
  // Load necessary libraries
  LoadLibs();
  // Set the default style
  SetStyle();
  //corrections for pt above 3 GeV/c
  TString baseName(gSystem->BaseName(inFile));
  baseName.ReplaceAll(".root", "");

 TFile *finHighpt = FindFileFresh(inFile);
  if(!finHighpt)
    return;

 cout<<"flag"<<endl;

 // AliESACorrections* test = 0;
 // test = (AliESACorrections*)(finHighpt->Get("CalculationCorrections"));



  TH2D *hSo[nMultbins];
  TH2D *hSoTmp[nMultbins];
  TGraphErrors * gSoM[nSobins];
  for(Int_t i = 0; i < nSobins; ++i){
    gSoM[i] = 0;
    gSoM[i] = new TGraphErrors();
    gSoM[i]->SetName(Form("gPSTM%dAtSoT%d", i, binSo-1));
  }

for(Int_t i = 0; i < nMultbins; ++i){

    hSoTmp[i] = 0;
    hSoTmp[i] =(TH2D *)finHighpt->Get(Form("h2newbins%d",i));

    if(isInverted){
      //convert from M vs T  to   T vs M    
      hSo[i] = 0;
      hSo[i] = (TH2D *)hSoTmp[i]->Clone(Form("RMtmp%d",i));
      hSo[i]->Reset();
      for(Int_t binx = 1; binx <= hSoTmp[i]->GetNbinsX(); ++binx){
         for(Int_t biny = 1; biny <= hSoTmp[i]->GetNbinsY(); ++biny){
           Double_t n_x_y = hSoTmp[i]->GetBinContent( binx, biny );     
           Double_t e_n_x_y = hSoTmp[i]->GetBinError( binx, biny );     
           hSo[i]->SetBinContent(biny,binx,n_x_y);
           hSo[i]->SetBinError(biny,binx,e_n_x_y);
         }
      }
    }
    else{
      hSo[i] = 0;
      hSo[i] = hSoTmp[i];
    }

    TH1D *hSom = 0;
    if(isInverted) hSom = (TH1D *)hSo[i]->ProjectionY(Form("hSoT%dAtSoM%d",i,binSo), binSo, binSo);
    else hSom = (TH1D *)hSo[i]->ProjectionY(Form("hSoM%dAtSoT%d",i,binSo), binSo, binSo);

    Double_t ntrk = (i+i+1)/2.0;
    //Double_t yield2 = hSom->GetEntries();
    Double_t yield = hSom->Integral();
    //Printf("Yield2=%f, Yield=%f",yield2,yield);
    if(yield>0){
      //hSom->Sumw2();
      hSom->Scale(1.0/yield);
      for(Int_t binsom = 1; binsom <= nSobins; ++binsom){
         gSoM[binsom-1]->SetPoint(i, ntrk, hSom->GetBinContent(binsom));
         gSoM[binsom-1]->SetPointError(i, 0, hSom->GetBinError(binsom)/yield);
      }
    }
    else{
      for(Int_t binsom = 1; binsom <= nSobins; ++binsom){
         gSoM[binsom-1]->SetPoint(i, ntrk, 0);
         gSoM[binsom-1]->SetPointError(i, 0, 0);
      }
    }

 }


  TCanvas *cBB = 0;
  if(isInverted)
    cBB = new TCanvas(Form("PSoTAtSoM%d",binSo), "Alice Figure Template", 600, 600);
  else
    cBB = new TCanvas(Form("PSoMAtSoT%d",binSo), "Alice Figure Template", 600, 600);
  cBB->SetLeftMargin(0.15);
  cBB->SetLogy(1);

  // Set Titles etc..
  TH1 * hBB = 0;
  hBB = cBB->DrawFrame(0,1e-4,100, 10.0);
  hBB->SetXTitle(Form("#it{N}_{trk}, (|#eta|<%1.1f)", eta_for_ntrk));
  if(isInverted)
    hBB->SetYTitle("true #it{P}(#it{S}_{O})");
  else
    hBB->SetYTitle("reconstructed #it{P}(#it{S}_{O})");
  hBB->GetYaxis()->SetTitleOffset(1.5);
  hBB->GetXaxis()->SetTitleOffset(1.05);
 
  TF1 *fhighntrk[nSobins];

  Double_t *minNtrk = new Double_t[nSobins];
  Double_t *maxNtrk = new Double_t[nSobins];
  switch(binSo){
  case 1:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk0[i];
      maxNtrk[i] =  maxNtrk0[i];
    }
  }break;
  case 2:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk1[i];
      maxNtrk[i] =  maxNtrk1[i];
    }
  }break;
  case 3:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk2[i];
      maxNtrk[i] =  maxNtrk2[i];
    }
  }break;
  case 4:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk3[i];
      maxNtrk[i] =  maxNtrk3[i];
    }
  }break;
  case 5:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk4[i];
      maxNtrk[i] =  maxNtrk4[i];
    }
  }break;
  case 6:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk5[i];
      maxNtrk[i] =  maxNtrk5[i];
    }
  }break;
  case 7:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk6[i];
      maxNtrk[i] =  maxNtrk6[i];
    }
  }break;
  case 8:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk7[i];
      maxNtrk[i] =  maxNtrk7[i];
    }
  }break;
  case 9:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      maxNtrk[i] = 0;
      minNtrk[i] =  minNtrk8[i];
      maxNtrk[i] =  maxNtrk8[i];
    }
  }break;
  case 10:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      maxNtrk[i] = 0; 
      minNtrk[i] =  minNtrk9[i];
      maxNtrk[i] =  maxNtrk9[i];
    }    
  }break;
   
  }


  for(Int_t i = 0; i < nSobins; ++i){
    fhighntrk[i] = 0;
    //fhighntrk[i] = new TF1(Form("fhighntrk%d",i),"pol0",minNtrk[i],maxNtrk[i]);
    fhighntrk[i] = new TF1(Form("fhighntrk%d",i),"pol1",minNtrk[i],maxNtrk[i]);
    if(binSo==nSobins&&i==0&&isInverted)
      fhighntrk[i] = new TF1(Form("fhighntrk%d",i),"pol0",minNtrk[i],maxNtrk[i]);
    if(i+1==binSo){
      gSoM[i]->SetMarkerColor(2);
      gSoM[i]->SetLineColor(2);
      gSoM[i]->SetMarkerStyle(20);
    }
    else
      gSoM[i]->SetMarkerColor(100-i*5);
      gSoM[i]->SetMarkerStyle(21+i);  // check abs
    fhighntrk[i]->SetLineColor(1);
    gSoM[i]->Fit(fhighntrk[i],"0","R",minNtrk[i],maxNtrk[i]);
    gSoM[i]->Draw("ESAMEP");
    fhighntrk[i]->Draw("samel");
  }


  TLegend *leg1 = 0;
  leg1 = new TLegend(0.45,0.6,0.5,0.94);
  leg1->SetTextFont(42);
  leg1->SetTextSize(0.04);
  leg1->SetLineColor(kWhite);
  leg1->SetLineWidth(0);
  leg1->SetLineStyle(3);
  leg1->SetShadowColor(kWhite);
  leg1->SetFillColor(kWhite);
  leg1->SetFillStyle(0);
  if(isInverted){
    leg1->SetHeader(Form("%d < #it{S}_{Opc} (rec) < %d  (|#eta|<%1.1f)", (binSo-1)*(nSobins), binSo*(nSobins), eta_for_es ));
    for(Int_t i = 0; i < nSobins; ++i)
      leg1->AddEntry(gSoM[i],Form("%d < #it{S}_{Opc} (true) < %d", (i)*(nSobins), (i+1)*(nSobins)),"P");
  }
  else{
    leg1->SetHeader(Form("%d < #it{S}_{Opc} (true) < %d  (|#eta|<%1.1f)", (binSo-1)*(nSobins), binSo*(nSobins), eta_for_es ));
    for(Int_t i = 0; i < nSobins; ++i)
      leg1->AddEntry(gSoM[i],Form("%d < #it{S}_{Opc} (rec) < %d", (i)*(nSobins), (i+1)*(nSobins)),"P");
  }
  leg1->Draw();


  cBB->SaveAs(Form("%s/%s.png",outDir,cBB->GetName()));



  finHighpt->Close();
  if(minNtrk)
    delete[] minNtrk;
  if(maxNtrk)
    delete[] maxNtrk;

  TFile *fout = 0;
  if(isInverted)
    fout = new TFile(Form("%s/PSoTAtSoM%d.root",outDir,binSo-1),"RECREATE");
  else
    fout = new TFile(Form("%s/PSoMAtSoT%d.root",outDir,binSo-1),"RECREATE");
  fout->cd();
  for(Int_t i = 0; i < nSobins; ++i){
    gSoM[i]->Write();
    fhighntrk[i]->Write();
  }
  fout->Close();




}


//-----------------------------------

void ProduceSoMvsSoTInNtrk(const Char_t * pathToFile, Bool_t isInverted, const Char_t * outDir,const char *f1){

 
  CreateDir(outDir);

  cout<<"hello"<<endl;
   TFile *fin1 = TFile::Open(f1);
   if(!fin1)
   return;

  TFile *fin[nSobins];
  TGraphErrors *gPSTMAtSoT[nSobins][nSobins];//5: intervals of measured So, 5: intervals of true So
  TF1 *fPSTMAtSoT[nSobins][nSobins];

  for(Int_t i_soT = 0; i_soT < nSobins; ++i_soT){
    fin[i_soT] = 0;
    cout<<i_soT<<endl;
    if(isInverted)
      fin[i_soT] = FindFileFresh(Form("%s/PSoTAtSoM%d.root", pathToFile, i_soT));
    else
      fin[i_soT] = FindFileFresh(Form("%s/PSoMAtSoT%d.root", pathToFile, i_soT));

    for(Int_t i_soM = 0; i_soM < nSobins; ++i_soM){
      gPSTMAtSoT[i_soM][i_soT] = 0;
      gPSTMAtSoT[i_soM][i_soT] = (TGraphErrors *)fin[i_soT]->Get(Form("gPSTM%dAtSoT%d",i_soM, i_soT));

      fPSTMAtSoT[i_soM][i_soT] = 0;
      fPSTMAtSoT[i_soM][i_soT] = (TF1 *)fin[i_soT]->Get(Form("fhighntrk%d",i_soM));

    }
  }
 
  TH2D *RSO[nMultbins];
  TH2D *hSo[nMultbins];

  for(Int_t i_ntrk = 0; i_ntrk < nMultbins; ++i_ntrk){
    RSO[i_ntrk]=(TH2D*)fin1->Get(Form("h2newbins%d",i_ntrk));
    hSo[i_ntrk] = 0;
    hSo[i_ntrk] = (TH2D*)RSO[i_ntrk]->Clone(Form("hRMNtrk%d",i_ntrk)); 
    if(isInverted){
      hSo[i_ntrk]->SetXTitle(" rec #it{S}_{O}");
      hSo[i_ntrk]->SetYTitle(" true #it{S}_{O}");
    }
    else{
      hSo[i_ntrk]->SetXTitle(" true #it{S}_{O}");
      hSo[i_ntrk]->SetYTitle(" rec #it{S}_{O}");
    }
      //hSo[i_ntrk] = new TH2D(Form("hRMNtrk%d",i_ntrk),"; true #it{S}_{O}; rec #it{S}_{O}",5,0,1,5,0,1);

    Double_t ntrk = (2*i_ntrk + 1)/2.0;

    for(Int_t i_soT = 0; i_soT < nSobins; ++i_soT){

      Double_t *minNtrk = new Double_t[nSobins];
     
      switch(i_soT){
      case 1:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      minNtrk[i] =  minNtrk0[i];
    }
      }break;
      case 2:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      minNtrk[i] =  minNtrk1[i];
    }
      }break;
      case 3:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      minNtrk[i] =  minNtrk2[i];
    }
      }break;
      case 4:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      minNtrk[i] =  minNtrk3[i];
    }
      }break;
      case 5:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0;
      minNtrk[i] =  minNtrk4[i];
    }
      }break;
      case 6:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      minNtrk[i] =  minNtrk5[i];
    }    
      }break;
      case 7:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      minNtrk[i] =  minNtrk6[i];
    }    
      }break;
     case 8:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      minNtrk[i] =  minNtrk7[i];
    }    
      }break;
     case 9:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      minNtrk[i] =  minNtrk8[i];
    }    
      }break;
     case 10:{
    for(Int_t i = 0; i<nSobins; ++i){
      minNtrk[i] = 0; 
      minNtrk[i] =  minNtrk9[i];
    }    
      }break; 

   
      }


     
      for(Int_t i_soM = 0; i_soM < nSobins; ++i_soM){

    Double_t yield = 0;
    if( i_ntrk < minNtrk[i_soM] )
      yield = gPSTMAtSoT[i_soM][i_soT]->GetY()[i_ntrk];
    else
      yield = fPSTMAtSoT[i_soM][i_soT]->Eval(ntrk);

   
    hSo[i_ntrk]->SetBinContent(i_soT+1,i_soM+1,yield);
    hSo[i_ntrk]->SetBinError(i_soT+1,i_soM+1,0);
   
      }

      delete[] minNtrk;

    }
   
  }

 


  //normalize to 1
  for(Int_t i_ntrk = 0; i_ntrk < nMultbins; ++i_ntrk){
    for(Int_t i_soT = 0; i_soT < nSobins; ++i_soT){
      Double_t integral = hSo[i_ntrk]->Integral(i_soT+1, i_soT+1, 1, hSo[i_ntrk]->GetNbinsY());     
      for(Int_t i_soM = 0; i_soM < nSobins; ++i_soM){
         Double_t yield = hSo[i_ntrk]->Integral(i_soT+1, i_soT+1, i_soM+1, i_soM+1);
         yield /= integral;
         hSo[i_ntrk]->SetBinContent(i_soT+1,i_soM+1,yield);
        hSo[i_ntrk]->SetBinError(i_soT+1,i_soM+1,0);
      }
    }
  }
 

  TFile *fout = 0;
  if(isInverted)
    fout = new TFile(Form("%s/SoRMInverted.root",outDir),"RECREATE");
  else
    fout = new TFile(Form("%s/SoRM.root",outDir),"RECREATE");

  fout->cd();
  for(Int_t i_ntrk = 0; i_ntrk < nMultbins; ++i_ntrk)
    hSo[i_ntrk]->Write();
  fout->Close();

 
}




//________________________________________________________________
///*
void MakeMeanPtvsNtrkAtSoM(const Char_t * pathToData, const Char_t * nameFileSoRM, const Char_t *outDir){
  TFile *finmeanpt[nSobins];
  TH1D *hptvsntrkatmso[nSobins];
  TH1D *hmptvsntrkatmso[nSobins];
  TH1D *hptvsntrkatso[nSobins];
  // Load necessary libraries
  LoadLibs();
  // Set the default style
  SetStyle();

 // const Char_t *nameFiles[];
  const Char_t *Sopcin[nSobins+1]={"0%","10%","20%","30%","40%","50%","60%","70%","80%","90%","100%"};
  const Char_t *nameFiles[nSobins]={"EsBin0","EsBin1","EsBin2","EsBin3","EsBin4","EsBin5","EsBin6","EsBin7","EsBin8","EsBin9"};
  //for(Int_t n=0; n<nSobins; n++){
  //  nameFiles[n]= Form("EsBin%d",n);
  //}

  for(Int_t i_mso = 0; i_mso < nSobins; ++i_mso){

    finmeanpt[i_mso] = 0;
    finmeanpt[i_mso] = FindFileFresh(Form("%s/%s/MeanPtVsNm_%sf.root", pathToData, nameFiles[i_mso], nameFiles[i_mso]));
    hptvsntrkatmso[i_mso] = 0;
    hptvsntrkatmso[i_mso] = (TH1D *)finmeanpt[i_mso]->Get("hPtvsNm");//Get(Form("hPtvsNm_%s",nameFiles[i_mso]));
    hmptvsntrkatmso[i_mso] = 0;
    hmptvsntrkatmso[i_mso] = (TH1D *)finmeanpt[i_mso]->Get("hPtmvsNm");//Get(Form("hPtmvsNm_%s",nameFiles[i_mso]));
    
    hptvsntrkatso[i_mso] = new TH1D(Form("hFullyCorrectedPtvsNm_%s",nameFiles[i_mso]),"",200,0,200);
  }

  TFile *finrmso = 0;
  finrmso = FindFileFresh(nameFileSoRM);
  TH2D * hSoRM[nMultbins]; //100

  for(Int_t i_ntrk = 0; i_ntrk < nMultbins; ++i_ntrk){ //100
    hSoRM[i_ntrk] = 0;
    hSoRM[i_ntrk] = (TH2D *)finrmso->Get(Form("hRMNtrk%d",i_ntrk));
    for( Int_t i_soT = 0; i_soT < nSobins; ++i_soT ){
     
      Double_t yield = 0;
      Double_t e_yield = 0;
      for( Int_t i_soM = 0; i_soM < nSobins; ++i_soM ){
         yield += hptvsntrkatmso[i_soM]->GetBinContent(i_ntrk+1)*hSoRM[i_ntrk]->Integral(i_soT+1,i_soT+1,i_soM+1,i_soM+1);
         e_yield += hptvsntrkatmso[i_soM]->GetBinError(i_ntrk+1)*hptvsntrkatmso[i_soM]->GetBinError(i_ntrk+1)*hSoRM[i_ntrk]->Integral(i_soT+1,i_soT+1,i_soM+1,i_soM+1)*hSoRM[i_ntrk]->Integral(i_soT+1,i_soT+1,i_soM+1,i_soM+1);
      }      
      hptvsntrkatso[i_soT]->SetBinContent(i_ntrk+1,yield);
      hptvsntrkatso[i_soT]->SetBinError(i_ntrk+1,TMath::Sqrt(e_yield));

    }    
  }

 //-----  Canvas -------
  for( Int_t i_soT = 0; i_soT < nSobins; ++i_soT ){
    TCanvas *cBB = 0;
    cBB = new TCanvas(Form("CorrectedPtVsNm_SoM_%d",i_soT), "Alice Figure Template", 600, 600);
    cBB->SetLeftMargin(0.15);

    TH1 * hBB = 0;
    hBB = cBB->DrawFrame(0,0.4,100, 2.2);

    hBB->SetXTitle(Form("#it{N}_{trk}, (|#eta|<%1.1f)", eta_for_ntrk));
    hBB->SetYTitle(Form("corrected #LT #it{p}_{T} #GT (GeV/#it{c}), (|#eta|<%1.1f)", eta_for_pt));
    hBB->GetYaxis()->SetTitleOffset(1.5);
    hBB->GetXaxis()->SetTitleOffset(1.05);
    hBB->GetYaxis()->SetRangeUser(0.4,1.2);

    hptvsntrkatso[i_soT]->SetMarkerStyle(20);
    hptvsntrkatso[i_soT]->SetMarkerColor(1);
    hptvsntrkatso[i_soT]->SetLineColor(1);
    hptvsntrkatso[i_soT]->Draw("SAMEP");
    hptvsntrkatmso[i_soT]->SetMarkerStyle(24);
    hptvsntrkatmso[i_soT]->SetMarkerColor(kBlue);
    hptvsntrkatmso[i_soT]->SetLineColor(kBlue);
    hptvsntrkatmso[i_soT]->Draw("SAMEP");
    
    TLegend *leg1 = 0;
    leg1 = new TLegend(0.18,0.65,0.75,0.94); //0.48
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetLineColor(kWhite);
    leg1->SetLineWidth(0);
    leg1->SetLineStyle(3);
    leg1->SetShadowColor(kWhite);
    leg1->SetFillColor(kWhite);
    leg1->SetFillStyle(0);
    leg1->SetHeader(Form("%s < #it{S}_{Opc}  < %s, (|#eta|<%1.1f)", Sopcin[i_soT], Sopcin[i_soT+1], eta_for_es));
      //AliESAMeanPtVsMultiplicityMC* testMC = 0;
    leg1->AddEntry(hptvsntrkatso[i_soT],"corrected for #it{S}_{O}","P");
    leg1->AddEntry(hptvsntrkatmso[i_soT],"no #it{S}_{O} corr. but eff & sec corr","P");
    leg1->Draw();
    cBB->SaveAs(Form("%s/%s/%s.png",outDir,nameFiles[i_soT],cBB->GetName()));    
  }

  CreateDir(outDir);
  TFile *outf[nSobins];

  for(Int_t i = 0; i<nSobins; ++i){
    outf[i] = new TFile(Form("%s/%s/FullyCorrectedMeanPtVsNm_EsBin%d.root", outDir, nameFiles[i], i), "RECREATE");
    outf[i]->cd();
    hptvsntrkatso[i]->Write();
    hptvsntrkatmso[i]->Write();
    hmptvsntrkatmso[i]->Write();
    outf[i]->Close();
  }



}






//________________________________
void LoadLibs() {
	gSystem->Load("libCore.so");  
	gSystem->Load("libGeom.so");
	gSystem->Load("libPhysics.so");
	gSystem->Load("libVMC");
	gSystem->Load("libTree");
	gSystem->Load("libMinuit");
	gSystem->Load("libSTEERBase");
	gSystem->Load("libESD");
	gSystem->Load("libAOD");
	gSystem->Load("libANALYSIS");
	gSystem->Load("libANALYSISalice");
	gSystem->Load("libCORRFW");
	gSystem->Load("libPWGTools");
}
//______________________________________________
void SetStyle(Bool_t graypalette) {
	cout << "Setting style!" << endl;

	gStyle->Reset("Plain");
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	if(graypalette) gStyle->SetPalette(8,0);
	else gStyle->SetPalette(1);
	gStyle->SetCanvasColor(10);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetFrameFillColor(kWhite);
	gStyle->SetPadColor(10);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);

	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetPadLeftMargin(0.12);

	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.03);

	gStyle->SetHistLineWidth(1);
	gStyle->SetHistLineColor(kRed);
	gStyle->SetFuncWidth(2);
	gStyle->SetFuncColor(kGreen);
	gStyle->SetLineWidth(2);
	gStyle->SetLabelSize(0.045,"xyz");
	gStyle->SetLabelOffset(0.01,"y");
	gStyle->SetLabelOffset(0.01,"x");
	gStyle->SetLabelColor(kBlack,"xyz");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleOffset(0.95,"y");
	gStyle->SetTitleOffset(0.95,"x");
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetTextSizePixels(26);
	gStyle->SetTextFont(42);

	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(kWhite);
	//  gStyle->SetFillColor(kWhite);
	gStyle->SetLegendFont(42);


}

