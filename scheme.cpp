#include"scheme.h"
//#include<algorithm>




bool operator<(const Scheme& t1, const Scheme& t2) {
    return (t1.simplified < t2.simplified);
}


bool operator<(const Scheme_compact& t1, const Scheme_compact& t2) {
    return (t1.simplified < t2.simplified);
}



bool Scheme::operator<(const Scheme& t2) {
    return (this->simplified < t2.simplified);
}

bool operator==(const Scheme& t1, const Scheme& s2) {
    return (t1.simplified == s2.simplified);
}


bool operator==(const Scheme_compact& t1, const Scheme_compact& s2) {
    return (t1.simplified == s2.simplified);
}



/**
bool operator<(const Scheme& t1, const Scheme& t2) {
	//return (t1.simplified < t2.simplified);

	for (int i=0; i<t1.simplified.size(); i++ ){
		if (t1.simplified[i]>t2.simplified[i]){
			return false;
		}
	}
	return true;


}


bool operator<(const Scheme_compact& t1, const Scheme_compact& t2) {
    //return (t1.simplified < t2.simplified);

	for (int i=0; i<t1.simplified.size(); i++ ){
		if (t1.simplified[i]>t2.simplified[i]){
			return false;
		}
	}
	return true;


}



bool Scheme::operator<(const Scheme& t2) {
	//return (this->simplified < t2.simplified);

	for (int i=0; i<t2.simplified.size(); i++ ){
		if (this->simplified[i]>t2.simplified[i]){
			return false;
		}
	}
	return true;


}

bool operator==(const Scheme& t1, const Scheme& s2) {
	//bool flag = true;
	for (int i=0; i<t1.simplified.size(); i++ ){
		if (t1.simplified[i]!=s2.simplified[i]){
			return false;
		}
	}
	return true;
}


bool operator==(const Scheme_compact& t1, const Scheme_compact& s2) {
    //return (t1.simplified == s2.simplified);
	for (int i=0; i<t1.simplified.size(); i++ ){
		if (t1.simplified[i]!=s2.simplified[i]){
			return false;
		}
	}
	return true;
}
**/
Scheme::Scheme() {
	patterns={};
}

bool Scheme::check_codes() {
	int code;
	bool first = true; 
	codes = false;

    //cout << " check codes[1]" << codes[1] << endl;
    //codes= codes.shift(false);
	for (int i: patterns) {
		for ( int j : patterns) {
			//code =  patternscode.codes[ patternscode.patterns.size()*i  +j]; //!!!
			code =  code_tab_ptr->calc_code_fast(i, j);
			if (first) {
				first = false;
				continue;
			}
			else if (codes[code]==true) {
				return false;
			}
			else {
				//codes.insert(code);
				codes[code] = true;
			}
		}
	}
	return true;
}


void Scheme::setscheme( PatternsCodes *patternscode , string sname, NCS *sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
//	valarray<int> patterns( bpatterns.data(), bpatterns.size());
    patterns=bpatterns;
	samples = bsamples;
	code_tab_ptr = patternscode;
	ncs_ptr = sncs;
	codes.resize(code_tab_ptr->n_codes, false);
	new_codes.resize(code_tab_ptr->n_codes, false) ;

	good = check_codes();
	simplify();

}


void Scheme::simplify() {
	simplified.assign(code_tab_ptr->n_simplified, 0);
	for (int pattern : patterns) {
	   simplified[code_tab_ptr->simple_ints[pattern]]++;
	}
}



Scheme::Scheme(PatternsCodes *patternscode, string sname, NCS *sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
	//patterns = bpatterns;

//	valarray<int> patterns( bpatterns.data(), bpatterns.size());
    	patterns = bpatterns;
	samples = bsamples;
	code_tab_ptr = patternscode; 
	ncs_ptr  = sncs;
	valarray <bool> codes(false, code_tab_ptr->n_codes); //
	good = check_codes();
	simplify();
	valarray <bool> new_codes(false, code_tab_ptr->n_codes);
	//code_table.setPatternsCodes(patterns, ncs);

}

bool Scheme::check_patterns(vector <string> patterns) {
	if (patterns.size() == 0) {
		return false;
	}
	int sizep;
	sizep = patterns[0].size();
	for (string pattern : patterns) {
		for (char label_type : pattern) {
			if (find(ncs_ptr->label_types.begin(), ncs_ptr->label_types.end(), to_string(label_type)) == ncs_ptr->label_types.end()) { //-/ 
				return false;
			}
		}
		if (pattern.size() != sizep) {
			return false;
		}
	}
	return true;
}


void Scheme::sort(){

	std::sort(patterns.begin(), patterns.end());

}


void Scheme_compact::sort(){

    std::sort(patterns.begin(), patterns.end());

}

void Scheme::add_new_codes(int new_pattern) {
	//int n = distance(patterns.begin(), find(patterns.begin(), patterns.end(), new_pattern));
	int m=code_tab_ptr->patterns.size();
	int n=new_pattern;
	//for ( int i =0; i<patterns.size(); i++) {
	for ( int i :patterns) {
		//codes.insert(patternscode.codes[i*m+n]);
		//codes.insert(patternscode.codes[n*m+i]);
		//codes.insert(code_tab_ptr->calc_code_fast(i,n));
		//codes.insert(code_tab_ptr->calc_code_fast(n,i));
		//cout << " no " << code_tab_ptr->calc_code_fast(i,n) << " " <<code_tab_ptr->calc_code_fast(n,i) << endl;
		codes[code_tab_ptr->calc_code_fast(i,n)] = true;
		codes[code_tab_ptr->calc_code_fast(n,i) ] = true;
	}
    codes [  code_tab_ptr->calc_code_fast(n,n)] = true;
	//codes.insert(code_tab_ptr->calc_code_fast(n,n));

}

void Scheme::add_pattern(int new_pattern) {
	patterns.push_back(new_pattern);
	//patternscode.setPatternsCodes(patterns, ncs);
	add_new_codes(new_pattern);
	simplify();
}



bool Scheme::try_pattern(int  new_pattern) {
	if (good == false) {
		return false;
	}
	new_codes = false;
	int code_1, code_2;
	/*if (find(patterns.begin(), patterns.end(), new_pattern) != patterns.end()) {
		return false;
	}*/
	//int n = distance(patterns.begin(), find(patterns.begin(), patterns.end(), new_pattern));
   	int n = new_pattern;
//	int m = code_tab_ptr->patterns.size();
	for (int i=0; i<patterns.size(); i++) {
		//code_1 = patternscode.codes[patterns[i]*m+n];

		//code_1 = patternscode.codes[patterns[i]*m+n];
		//code_2 = patternscode.codes[n*m+patterns[i]];
		code_1 = code_tab_ptr->calc_code_fast(patterns[i],n);
		code_2 = code_tab_ptr->calc_code_fast(n,patterns[i]);
		
		if (codes[code_1]==true || codes[code_2]==true || (code_2 == code_1) || new_codes[code_1]==true || new_codes[code_2]==true) {

			return false;
		}
		else {
			new_codes[code_1]=true;
			new_codes[code_2]=true;
		}

	}
	//int self_code = patternscode.codes[n*m+n];
	int self_code = code_tab_ptr->calc_code_fast(n,n);
	if (codes[self_code] ==true|| new_codes[self_code]==true) {
		return false;

	}
	else {
		new_codes[self_code]=true;
	}
	return true;
}


string Scheme::full_str() {
	string s = "";
	string all_p = "";

	for (int i : patterns) {
		all_p = all_p + code_tab_ptr->patterns[i] + "\n";
	}
	s = "[ELB samples = " + to_string(samples) + " patterns = " + to_string(patterns.size()) + "]\n" + all_p;
	return s;
}



Scheme_compact::Scheme_compact() {}


Scheme_compact::Scheme_compact(Scheme &scheme) {
    code_tab_ptr = scheme.code_tab_ptr;
    patterns     = scheme.patterns;
    simplified   = scheme.simplified;
    samples      = scheme.samples;


}



string Scheme_compact::full_str() {
    string header= "[ELB ";
    string all_p = "";
    string sv = "[SV";
    string s;

    header = header + "samples = " + to_string(samples) + " patterns = " + to_string(patterns.size()) + "]\n";
    for (int int_simple : simplified) {
      sv = sv + " "+ to_string(int_simple);
    }
    sv = sv + " ]\n";
    for (int i : patterns) {
        all_p = all_p + code_tab_ptr->patterns[i] + "\n";
    }
    s = header + sv + all_p;
    //s = header + all_p;
    return s;
}

