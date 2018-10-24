
TRandom* fRandom = new TRandom();
fRandom->SetSeed(300);

void phiA() {
	TH1D* phi = new TH1D("phi", "phi distribution", 50, 0, 3.14);
	TH1D* theta = new TH1D("theta", "theta distribution", 50, 0, 3.14);
	

	//TRandom* fRandom = new TRandom();

	for(Int_t i = 0; i < 1000000; i++) {
		//Double_t fillPhi = fRandom->Rndm() * 2.0 * 3.14;
		phi->Fill(phiRandom());
		
		//Double_t fillTheta = acos(2.0 * fRandom->Rndm() - 1.0);
		theta->Fill(thetaRandom());

	}


	TCanvas *c1 = new TCanvas("c1", "c1", 800, 1000);
	c1->Divide(1,2);
	c1->cd(1);
	phi->Draw();
	c1->cd(2);
	theta->Draw();
	c1->cd();

}

double phiRandom() {
	//TRandom* fRandom = new TRandom();
	double x = fRandom->Rndm();
 	return x * 2.0 * TMath::Pi();
}

double thetaRandom() {
	//TRandom* fRandom = new TRandom();
	double y = fRandom->Rndm();
	return acos(2.0 * y - 1.0);
}



