#include <cmath>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TGraphErrors.h"


Double_t singola(Double_t *x, Double_t *par)
{
 Double_t L=1.135;
 Double_t d = 0.06E-3;  
 Double_t k= 9.92918E6;

 Double_t xx=(TMath::Abs(par[0]-x[0]));
 Double_t theta = TMath::ATan(xx/L);
 Double_t args = k*d*TMath::Sin(theta)/2.;
 Double_t val = sin(args)/args;
 return par[1]*pow(val,2);
}


void grafico(){
 
 gStyle->SetOptStat(2210);
 gStyle->SetOptFit(1111);
 gStyle->SetFitFormat("7.6g");

 TCanvas *c1 = new TCanvas("c1","Singola Fenditura");

 TGraphErrors * graph =new TGraphErrors ("singerrore", "%lg %lg %*lg %lg");
    
 graph->GetXaxis()->SetTitle("Posizione (m)");
 graph->GetYaxis()->SetTitle("Intensita' luminosa (u arbitraria)");
 graph->SetTitle("Singola fenditura 5");
 graph->SetMarkerStyle(kOpenCircle);
 graph->SetMarkerColor(kBlue);
 graph->SetLineColor(kBlue);

 Double_t x, y;
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
  
  
 TF1 *f = new TF1("f",singola,0.01400, 0.099950, 3);

 f->SetParameters(0, max_x);
 f->SetParLimits(0, max_x-0.0001,max_x+0.0001);
 f->SetParameters(1, max_y);
 f->SetParLimits(1, max_y-1,max_y+1);
 
 f->SetLineColor(kRed); f->SetLineStyle(1);

 graph->GetXaxis()->SetRangeUser(0.014, 0.1);
 graph->Fit("f", "R");
 gStyle->SetOptFit(111);
 graph->Draw("AP");
 f->Draw("E, SAME");
}
