void thetaA() {
	TH1D* theta = new TH1D("theta", "theta distribution", 30, 0, 5);
	TRandom* fRandom = new TRandom();

	for(Int_t i = 0; i < 100000; i++) {
		Double_t fillTheta = acos(2.0 * fRandom->Rndm() - 1.0);
		theta->Fill(fillTheta);
	}

	theta->Draw();

}


