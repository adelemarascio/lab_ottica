#include <cmath>
#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TGraphErrors.h"


void grafico(){

gStyle->SetOptFit(1100);

//Asse x ovvero seno dell'angolo iniziale
 Double_t sint_1[10]{0, 0.087155743, 0.173648178, 0.258819045, 0.342020143, 0.422618262, 0.5, 0.573576436, 0.64278761, 0.707106781};
  //errore come derivata parziale
 Double_t err_x[10]{0.008726646, 0.008693439, 0.008594069, 0.008429293, 0.008200365, 0.007909027, 0.007557497, 0.00714845, 0.006684999, 0.006170671};

//Asse y ovvero seno dell'angolo nel mezzo
 Double_t sint_2[10]{0, 0.059776533, 0.112150789, 0.152272155, 0.202706514, 0.251111845, 0.307636588, 0.342455075, 0.398448987, 0.445747933}; 
  //errore somma in quadratura delle derivate parziali
 Double_t err_y[10]{0.008730227, 0.008741083, 0.008788394, 0.008876258, 0.008998628, 0.009165606, 0.009375739, 0.00966954, 0.010017596, 0.010475285};

 TCanvas *c1 = new TCanvas("c1","Legge di Snell",200,10,700,500);
 
 TGraphErrors *gr = new TGraphErrors(10,sint_1,sint_2,err_x,err_y);
 gr->SetTitle("Legge di Snell");
 //gr->SetMarkerColor(4);
 gr->SetMarkerStyle(4);
 gr->GetXaxis()->SetTitle("sin(#theta1)");
 gr->GetXaxis()->SetTitleOffset(0.9);
 gr->GetXaxis()->SetTitleSize(0.045);
 gr->GetYaxis()->SetTitle("sin(#theta2)");
 gr->GetYaxis()->SetTitleOffset(0.9);
 gr->GetYaxis()->SetTitleSize(0.045);
 gr->GetXaxis()->SetRangeUser(0., 0.75);
 gr->GetYaxis()->SetRangeUser(0., 0.5);
 gr->Draw("AP");

 gr->Fit("pol1"); //[0]+[1]*x
 TF1 *fitFunc = gr->GetFunction("pol1");

 std::cout << "Parametro q:" << fitFunc->GetParameter(0) <<
  "\nParametro m: n1/n2 = " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << 
  "\nIndice di rifrazione stimato: n2 = " << 1.0002/fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << endl;
 Double_t chiSquare = fitFunc->GetChisquare();
 Double_t nDOF = fitFunc->GetNDF();
 Double_t Prob = fitFunc->GetProb();
 std::cout << "ChiSquare = " <<chiSquare << " , nDOF " << nDOF <<endl;
 std::cout << "ChiSquare ridotto = " <<chiSquare/nDOF<<endl;
 std::cout << "ChiSquare Probability= " <<Prob <<endl;
 
 c1->Print("int1.jpg");
 c1->Print("int1.root");

 
}
