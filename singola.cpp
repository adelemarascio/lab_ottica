#include <iostream>
#include "TROOT.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TMatrixD.h"
#include "TFitResult.h"
#include "TFile.h"


void setStyle1(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

Double_t singola(Double_t *x, Double_t *par){
 Double_t xx=x[0];
 Double_t theta = TMath::ATan((TMath::Abs(par[4]-xx))/par[0]);
 Double_t arg = par[1]*par[2]*TMath::Sin(theta)/2.;
 Double_t val = sin(arg)/arg;
 return par[3]*TMath::pow(val,2);
}


void grafico(){

 TGraphErrors * graph =new TGraphErrors ("singerrore", "%lg %lg %lg");
    
 graph->SetTitle("Diffrazione da fenditura singola ;Distanza (m);Ampiezza");
 graph->SetMarkerStyle(kOpenCircle);
 graph->SetMarkerColor(kBlue);
 graph->SetLineColor(kBlue);

 Double_t x, y, e;
    graph->GetPoint(0, x, y);
    Double_t max_x = x, max_y = y;
    for(int i = 1; i < graph->GetN(); i++)
    { graph->GetPoint(i, x, y);
        if(y > max_y) {
           max_x = x; //considerare di usare questo dato come shift e non 0.057
           max_y = y;
        }
    }
    std::cout<<max_x<<"     "<<max_y<<'\n';
  
 Double_t L=1.135;
 Double_t lambda=632.8E-9;
 //Double_t k=(2*TMath::Pi())/lambda;
 Double_t d = 0.15E-3; 
 Double_t D = 0.75E-3; 
 Double_t k= 9.92918E6;
  
 TF1 *f = new TF1("f",singola,0.014, 0.099950,3);
 f->SetParameters(0, d);
 f->SetParameters(1, k);
 f->SetParameters(2, L);
 
 f->SetParameters(3, max_y);
 f->SetParLimits(3,max_y-1,max_y+1);
 f->SetParameters(4, max_x);
 f->SetParLimits(3,max_x-0.001,max_x+0.001);

 TCanvas *c1 = new TCanvas("c1","Singola Fenditura",200,10,600,400);
 f->SetLineColor(kRed); f->SetLineStyle(1);

 graph->GetXaxis()->SetRangeUser(0.014, 0.1);
 graph->Fit("f", "R");
 gStyle->SetOptFit(111);
 graph->Draw("AP");
 f->Draw("E, SAME");
}
