#include"ncs.h"


NCS get_NCS(string name) {
	//NCS ncs; 
	vector<spectrum> spectra;
	vector<labeltype> ncslabeltype;

	if (name == "NC2") {
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NC2noX") {
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NCD2") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;

	}
	else if (name == "NCD2noX") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;

	}
	else if (name == "NCD4") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;

	}
	else if (name == "NCD4noX") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NCD6") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NCD6noX") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NCDA8") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		spectra.push_back(spectrum("COfHNCA"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		ncslabeltype.push_back(labeltype('A', 0, 1, 0));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "NCDA8noX") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		spectra.push_back(spectrum("COfHNCA"));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		ncslabeltype.push_back(labeltype('A', 0, 1, 0));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "2H-ND2") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype, true);
		return ncs;
	}
	else if (name == "2H-ND3") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		NCS ncs(name, spectra, ncslabeltype, true);
		return ncs;
	}
	else if (name == "ALT12") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		spectra.push_back(spectrum("COfHNCA"));
		spectra.push_back(spectrum("HNCACO"));
		ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		ncslabeltype.push_back(labeltype('A', 0, 1, 0));
		//ncslabeltype.push_back(labeltype('S', 0, 0, 1));
		ncslabeltype.push_back(labeltype('T', 1, 1, 0));
		ncslabeltype.push_back(labeltype('F', 0, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}
	else if (name == "ALT12noX") {
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		spectra.push_back(spectrum("HNCA"));
		spectra.push_back(spectrum("HNCOCA"));
		spectra.push_back(spectrum("DQHNCA"));
		spectra.push_back(spectrum("COfHNCA"));
		spectra.push_back(spectrum("HNCACO"));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		ncslabeltype.push_back(labeltype('D', 1, 1, 1));
		ncslabeltype.push_back(labeltype('A', 0, 1, 0));
		ncslabeltype.push_back(labeltype('T', 1, 1, 0));
		ncslabeltype.push_back(labeltype('F', 0, 1, 1));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;
	}

	else{
		/*ncslabeltype.push_back(labeltype('X', 0, 0, 0));
		ncslabeltype.push_back(labeltype('N', 1, 0, 0));
		ncslabeltype.push_back(labeltype('C', 0, 0, 1));
		spectra.push_back(spectrum("HSQC"));
		spectra.push_back(spectrum("HNCO"));
		NCS ncs(name, spectra, ncslabeltype);
		return ncs;*/
	  	cout<<"Unknown NCS name: "<<name<<endl;
		NCS ncs(name, spectra, ncslabeltype);
	   	return ncs;
	}


	
}
