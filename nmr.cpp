#include"ncs.h"

labeltype::labeltype(char lname){
   name = lname;
   if      (name == 'X') { label_HN = 0; label_CA = 0; label_CO = 0; }
   else if (name == 'N') { label_HN = 1; label_CA = 0; label_CO = 0; }
   else if (name == 'C') { label_HN = 0; label_CA = 0; label_CO = 1; }
   else if (name == 'D') { label_HN = 1; label_CA = 1; label_CO = 1; }
   else if (name == 'A') { label_HN = 0; label_CA = 1; label_CO = 0; }
   else if (name == 'T') { label_HN = 1; label_CA = 1; label_CO = 0; }
   else if (name == 'S') { label_HN = 1; label_CA = 0; label_CO = 1; }
   else if (name == 'F') { label_HN = 0; label_CA = 1; label_CO = 1; }
   else {
     cerr<<"Error: Unknown labeling type name: \'"<<lname<<"\'"<<endl;
     /* TODO: Generate exception */
   }
}


int spectrum::has_signal(labeltype lt1, labeltype lt2) {
	if (name == "HSQC") {
		return int(lt2.label_HN);
	}
	else if (name == "HNCO") {
		return int(lt2.label_HN &&  lt1.label_CO);
	}
	else if (name == "HNCA") {
		return int(lt2.label_HN && (lt1.label_CA || lt2.label_CA));
	}
	else if (name == "HNCOCA") {
		return int(lt2.label_HN && lt1.label_CO && lt1.label_CA);
	}
	else if (name == "COfHNCA") {
		return int(lt2.label_HN  && lt1.label_CA &&  !(lt1.label_CO));
	}
	else if (name == "DQHNCA") {
		return int(lt2.label_HN && lt1.label_CA &&    lt2.label_CA);
	}
	else if (name == "HNCACO") {
		return int(lt2.label_HN &&  lt2.label_CA && lt2.label_CO);
	}
	else if (name == "HNCAfCO") 
		return int(lt2.label_HN && !(lt2.label_CA) && lt2.label_CO);
	else{
 		cerr<<"Error: Unknown NMR spectrum name: \'"<<name<<"\'"<<endl;
	     	/* TODO: Generate exception */
		return 0;
	}
}


NCS get_NCS(string name) {

	if (name == "NC2") {
		NCS ncs(name, {"HSQC", "HNCO"}, "XNC");
		return ncs;
	}else if (name == "NC2noX") {
		NCS ncs(name, {"HSQC", "HNCO"}, "NC");
		return ncs;
	}else if (name == "NCD2") {
		NCS ncs(name, {"HSQC", "HNCO"}, "XNCD");
		return ncs;
	}else if (name == "NCD2noX") {
		NCS ncs(name, {"HSQC", "HNCO"}, "NCD");
		return ncs;
	}else if (name == "NCD4") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA"}, "XNCD");
		return ncs;
	}else if (name == "NCD4noX") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA"}, "NCD");
		return ncs;
	}else if (name == "NCD6") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", "DQHNCA"}, "XNCD");
		return ncs;
	}else if (name == "NCD6noX") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", "DQHNCA"}, "NCD");
		return ncs;
	}else if (name == "NCDA8") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", "DQHNCA", "COfHNCA"}, "XNCDA");
		return ncs;
	}
	else if (name == "NCDA8noX") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", "DQHNCA", "COfHNCA"}, "NCDA");
		return ncs;
	}
	else if (name == "2H-ND2") {
		NCS ncs(name, {"HSQC", "HNCO"}, "XND", true);
		return ncs;
	}else if (name == "2H-ND3") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA"}, "XND", true);
		return ncs;
	}else if (name == "ALT12") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", 
		               "DQHNCA", "COfHNCA", "HNCACO"}, "XNCDATF" /*NO S*/);
		return ncs;
	}else if (name == "ALT12noF") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", 
		               "DQHNCA", "COfHNCA", "HNCACO"}, "XNCDAT" /*NO SF*/);
		return ncs;
	}

	else if (name == "ALT12noX") {
		NCS ncs(name, {"HSQC", "HNCO", "HNCA", "HNCOCA", 
		               "DQHNCA", "COfHNCA", "HNCACO"}, "NCDATF" /*NO S*/);
		return ncs;
	}

	else{
	  	cerr<<"Error: Unknown NCS name: "<<name<<endl;
		NCS ncs(name, {}, "");
		/* TODO: Generate exception */
	   	return ncs;
	}
}
