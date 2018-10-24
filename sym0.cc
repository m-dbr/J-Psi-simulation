#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>

#include "TLorentzVector.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TMath.h"
#include "TVector3.h"

using namespace std;


double electron_momentum();
double phiRandom();
double thetaRandom();
TVector3 J_PsiGenerator();

// declaration of random generator
TRandom* fRandom = new TRandom();

// declaration of histograms for J/Psi
TH1D* yHist;
TH1D* mtHist; 
TH1D* ptHist; 
TH1D* phiHist1; 

// mass in MeV/c^2
const double J_Psi_mass = 3096.916;
const double e_mass = 0.511; 

int main() {

	cout << "Number of events: ";
	int events;
	cin >> events;

	TString home_path = Form("/home/rs/CERN/NA61/czarmonium/simulation/root_files/psi.root");
	// declaration of histograms for angles distributions
	
	TFile outFile(home_path.Data(), "recreate");

	yHist = new TH1D("yHist", "Gaus", 50, -5, 5);
	mtHist = new TH1D("mtHist", "mt->Exp", 50, 3000, 5000);
	ptHist = new TH1D("ptHist", "pt", 50, 0, 3000);
	phiHist1 = new TH1D("phiHist1", "phi", 50, 0, 4);

	
	TH1D* phiHist = new TH1D("phi", "phi distribution", 50, 0, 3.14);
	TH1D* thetaHist = new TH1D("theta", "theta distribution", 50, 0, 3.14);

	// main loop
	for(int i = 0; i < events; i++) {
		double p, px1, py1, pz1, px2, py2, pz2;
		double theta = thetaRandom();
		double phi = phiRandom();
		p = electron_momentum();

	// filling the histograms for angles distributions
		phiHist->Fill(theta);
		thetaHist->Fill(phi);

	// coordinates for electron
		px1 = p * sin(theta) * cos(phi);
		py1 = p * sin(theta) * sin(phi);
		pz1 = p * cos(theta);

	// coordinates for pozyton
		px2 = -p * sin(theta) * cos(phi);
		py2 = -p * sin(theta) * sin(phi);
		pz2 = -p * cos(theta);

		TLorentzVector e1(px1, py1, pz1, e_mass);
		TLorentzVector e2(px2, py2, pz2, e_mass);

	//generating J/Psi TVector3
		const TVector3 J_PsiL = J_PsiGenerator();

	// boost e1 and e2
		e1.Boost(J_PsiL);
		e2.Boost(J_PsiL);

	}

	cout << "All histograms are in: " << home_path.Data() << endl;
	
	outFile.Write();
	outFile.Close();


	return 0;
}


double electron_momentum() {
	return sqrt((pow(J_Psi_mass, 2) + 2*pow(e_mass, 2) - 2*J_Psi_mass*e_mass - 4*e_mass - 2*e_mass * J_Psi_mass)/(4*pow(J_Psi_mass, 2)));
}

double phiRandom() {
 	return fRandom->Rndm() * 2.0 * TMath::Pi();
}

double thetaRandom() {
	return acos(2.0 * fRandom->Rndm() - 1.0);
}

// J/Psi generator
TVector3 J_PsiGenerator() {
	
	double sigma = 1;
	double temp = 175; // MeV -> default

	double y = fRandom->Gaus(0, sigma);
	double mt = fRandom->Exp(temp) + J_Psi_mass; 
	double pt = TMath::Sqrt((pow(mt, 2))-(pow(J_Psi_mass, 2)));
	double phi = phiRandom();

	yHist->Fill(y);
	mtHist->Fill(mt);
	ptHist->Fill(pt);
	phiHist1->Fill(phi);

	double pxJ = pt * TMath::Cos(phi);
	double pyJ = pt * TMath::Sin(phi);
	double pzJ = mt * TMath::SinH(y);
	double EnJ = mt * TMath::CosH(y);

	TLorentzVector J_Psi(pxJ, pyJ, pzJ, EnJ);

	return J_Psi.BoostVector();
}
