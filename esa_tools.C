#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TMath.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#include <iostream>

using namespace std;



//_____________________________________________________________________________




TFile* FindFileFresh(const Char_t* fileName);
TFile* FindFile(const Char_t* fileName);
void CutHistogram(TH1* hist, Double_t xMin, Double_t xMax);
void SetHistError(TH1* hist, Double_t error);
void CreateDir(const Char_t* dirName);


//______________________________________________________________________
TFile* FindFileFresh(const Char_t* fileName)
{
  // Find file
  TFile *file = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName);
  if(file) {
    file->Close();
    delete file;
  }

  file = TFile::Open(fileName, "READ");

  if(!file)
    cout << "File : " << fileName << " was not found" << endl;

  return file;
}

//______________________________________________________________________
TFile* FindFile(const Char_t* fileName)
{
  // Find file
  TFile *file = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName);
  if(file) {
    return file;
  }

  file = TFile::Open(fileName, "READ");

  if(!file)
    cout << "File : " << fileName << " was not found" << endl;

  return file;
}

//______________________________________________________________________
void CutHistogram(TH1* hist, Double_t xMin, Double_t xMax)
{
  const Int_t n = hist->GetNbinsX();
  
  for(Int_t bin = 1; bin <= n; bin++) {
    
    Float_t x = hist->GetXaxis()->GetBinCenter(bin);
    if(x < xMin) {
      hist->SetBinContent(bin, 0);
      hist->SetBinError(bin, 0);
    } else if(x > xMax) {
      hist->SetBinContent(bin, 0);
      hist->SetBinError(bin, 0);
    }

  }
}

//______________________________________________________________________
void SetHistError(TH1* hist, Double_t error)
{
  const Int_t n = hist->GetNbinsX();
  
  for(Int_t bin = 1; bin <= n; bin++) {
    
    //    Float_t x = hist->GetXaxis()->GetBinCenter(bin);
    hist->SetBinError(bin, error);
  }
}

//______________________________________________________________________
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

//___________________________________________________________________
void GetWeighting( TH2D * hR, TH1D * hin, TH1 * hout ){
  
  hout->Reset();
// modified by Hector
  // por default empieza en nbinsX0=3, 
//  const Int_t nbinsX0 =2; //jetty
//  const Int_t nbinsX =60;//
  const Int_t nbinsX0 =1; //inc
 // const Int_t nbinsX =80;//inc
  const Int_t nbinsX = 100;//hR->GetNbinsX();
 // const Int_t nbinsY0 =2;//jetty
 // const Int_t nbinsY =60;//
  const Int_t nbinsY0 =1;//inc
  const Int_t nbinsY = 100; //hR->GetNbinsY();

//---------------------------------------
  //Double_t Resp[nbinsX][nbinsY];
  //Double_t RespE[nbinsX][nbinsY];

  //Double_t **Resp;
  //Double_t **RespE;

  //Double_t *arr = new Double_t[10];

  Double_t** Resp = new Double_t*[nbinsX];
  for (Int_t i=0;i<nbinsX;i++) 
    Resp[i] = new Double_t[nbinsY];
 

  Double_t** RespE = new Double_t*[nbinsX];
  for (Int_t i=0;i<nbinsX;i++) 
    RespE[i] = new Double_t[nbinsY];


  for( Int_t ix=1; ix <= nbinsX; ++ix ){
    
    Double_t entries= hR->Integral(ix, ix, 1, nbinsY);
    
    
    if(entries>0){
      for( Int_t iy = 1; iy <= nbinsY; ++iy ){
	
	Resp[ix-1][iy-1] = 0;
	RespE[ix-1][iy-1] = 0;
	
	Resp[ix-1][iy-1] = (1.0*hR->GetBinContent(ix,iy))/(1.0*entries);
	RespE[ix-1][iy-1] = (1.0*hR->GetBinError(ix,iy))/(1.0*entries);
	
	
	
      }
    }
    else{
      for( Int_t iy = 1; iy <= nbinsY; ++iy ){
	Resp[ix-1][iy-1] = 0;
	RespE[ix-1][iy-1] = 0;
      }
    }
    
  }
  
  

  
  for( Int_t ix=nbinsX0; ix <= nbinsX; ++ix ){
    
    
    Double_t yield = 0;
    Double_t e_yield = 0;
    
    for( Int_t iy = nbinsY0; iy <= nbinsY; ++iy ){
    
      yield += hin->GetBinContent(iy)*Resp[ix-1][iy-1];
      e_yield += TMath::Power( hin->GetBinContent(iy)*RespE[ix-1][iy-1], 2 );
      e_yield += TMath::Power( hin->GetBinError(iy)*Resp[ix-1][iy-1], 2 );      
      //e_yield += TMath::Power( hin->GetBinError(iy), 2 ); 
	
    }

    if(ix==1){
      hout->SetBinContent( ix, 0 );
      hout->SetBinError( ix, 0 );
    }
    else{
      hout->SetBinContent( ix, yield );
      hout->SetBinError( ix, TMath::Sqrt(e_yield) );
      //hout->SetBinError( ix,  hin->GetBinError(ix) );
    }

    
  }
  
  delete []Resp;
  delete []RespE;

  
}





//_______________________________________________________________________
TH1D * CloneBinningFromTProfileToHisto( TProfile * hin, const Char_t * namehisto ){

  TH1D *hout = 0;
  const Int_t nbins = hin->GetNbinsX();
  cout<<"nbins="<<nbins<<endl;
  Double_t *xval = new Double_t[nbins+1];
  for(Int_t i = 1; i<=hin->GetNbinsX()+1;++i){
    
      xval[i-1] = 0;
      if(i<=hin->GetNbinsX())
      xval[i-1] = hin->GetBinLowEdge(i);
      else
      xval[i-1] = hin->GetBinLowEdge(hin->GetNbinsX()) + hin->GetBinWidth(hin->GetNbinsX());
    
    cout<<"i="<<i<<"  xval="<<xval[i-1]<<endl;
  }
  
  hout = new TH1D( namehisto, "",  nbins, xval);

  delete[] xval;
  cout<<"bye"<<endl;
  return hout;

}
//___________________________________________________________________
void GetResponseMatrix( TH2D * hR, TH2D * hout ){
  
  
  hout->Reset();

  const Int_t nbinsX = hR->GetNbinsX();
  const Int_t nbinsY = hR->GetNbinsY();



  for( Int_t ix=1; ix <= nbinsX; ++ix ){
    
    Double_t entries= hR->Integral(ix, ix, 1, nbinsY);
 

    if(entries>0){
      for( Int_t iy = 1; iy <= nbinsY; ++iy ){
	
	Double_t yield = (1.0*hR->GetBinContent(ix,iy))/(1.0*entries);
	Double_t e_yield = (1.0*hR->GetBinError(ix,iy))/(1.0*entries);

	hout->SetBinContent(ix,iy,yield);
	hout->SetBinError(ix,iy,e_yield);

	
	
      }
    }
    else{
      for( Int_t iy = 1; iy <= nbinsY; ++iy ){

	hout->SetBinContent(ix,iy,0);
	hout->SetBinError(ix,iy,0);

      }
    }
    
  }
  
 
  
}
