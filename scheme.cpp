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

Scheme::Scheme() {
	patterns={};
}

bool Scheme::check_codes(PatternsCodes &patternscode) {
	set <int> codes;
	int code;
	bool first = true;

	for (int i: patterns) {
		for ( int j : patterns) {
			//code =  patternscode.codes[ patternscode.patterns.size()*i  +j]; //!!!
			code =  patternscode.calc_code_fast(i, j);
			if (first) {
				first = false;
				continue;
			}
			else if (codes.find(code) != codes.end()) {
				return false;
			}
			else {
				codes.insert(code);
			}
		}
	}
	return true;
}


void Scheme::setscheme( PatternsCodes &patternscode , string sname, NCS &sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	ncs = sncs;

	set <string> codes; 
	good = check_codes( patternscode  );
	//map <string, int> simplified;
	simplify(patternscode);
	set <string> new_codes;
	//code_table.setPatternsCodes(patterns, ncs);

}


void Scheme::simplify(PatternsCodes &patternscode) {
	//string simple_pattern;
	//simplified = {};
	simplified.assign(patternscode.n_simplified, 0);
	for (int pattern : patterns) {
	   simplified[patternscode.simple_ints[pattern]]++;
	}
}



Scheme::Scheme(PatternsCodes &patternscode, string sname, NCS &sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	ncs = sncs;
	set <string> codes; //
	good = check_codes(patternscode);
	simplify(patternscode);
	set <string> new_codes;
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
			if (find(ncs.label_types.begin(), ncs.label_types.end(), to_string(label_type)) == ncs.label_types.end()) { //-/ 
				return false;
			}
		}
		if (pattern.size() != sizep) {
			return false;
		}
	}
	return true;
}

/**void Scheme::sort() {
	string temp_pattern;
	for (int i = 0; i < (patterns.size() - 1); i++) {
		for (int j = 0; j < (patterns.size() - i - 1); j++) {
			if (pattern_bigger(patterns[i], patterns[i + j + 1])) {
				temp_pattern = patterns[i];
				patterns[i] = patterns[i + j + 1];
				patterns[i + j + 1] = temp_pattern;
			}
		}
	}
}**/

void Scheme::sort(){

	std::sort(patterns.begin(), patterns.end());

}


void Scheme_compact::sort(){

    std::sort(patterns.begin(), patterns.end());

}

void Scheme::add_new_codes(int new_pattern, PatternsCodes &patternscode) {
	//int n = distance(patterns.begin(), find(patterns.begin(), patterns.end(), new_pattern));
	int m=patternscode.patterns.size();
	int n=new_pattern;
	//for ( int i =0; i<patterns.size(); i++) {
	for ( int i :patterns) {
		//codes.insert(patternscode.codes[i*m+n]);
		//codes.insert(patternscode.codes[n*m+i]);
		codes.insert(patternscode.calc_code_fast(i,n));
		codes.insert(patternscode.calc_code_fast(n,i));
	}

	codes.insert(patternscode.calc_code_fast(n,n));

}

void Scheme::add_pattern(int new_pattern , PatternsCodes &patternscode) {
	patterns.push_back(new_pattern);
	//patternscode.setPatternsCodes(patterns, ncs);
	add_new_codes(new_pattern, patternscode);
	simplify(patternscode);
}



bool Scheme::try_pattern(int  new_pattern, PatternsCodes &patternscode) {
	if (good == false) {
		return false;
	}
	set <int> new_codes;
	int code_1, code_2;
	if (find(patterns.begin(), patterns.end(), new_pattern) != patterns.end()) {
		return false;
	}
	//int n = distance(patterns.begin(), find(patterns.begin(), patterns.end(), new_pattern));
   int n = new_pattern;
	int m = patternscode.patterns.size();
	for (int i=0; i<patterns.size(); i++) {
		//code_1 = patternscode.codes[patterns[i]*m+n];

		//code_1 = patternscode.codes[patterns[i]*m+n];
		//code_2 = patternscode.codes[n*m+patterns[i]];
		code_1 = patternscode.calc_code_fast(patterns[i],n);
		code_2 = patternscode.calc_code_fast(n,patterns[i]);
		
		if (codes.find(code_1) != codes.end() || codes.find(code_2) != codes.end() || (code_2 == code_1) || new_codes.find(code_1) != new_codes.end() || new_codes.find(code_2) != new_codes.end()) {

			return false;
		}
		else {
			new_codes.insert(code_1);
			new_codes.insert(code_2);
		}

	}
	//int self_code = patternscode.codes[n*m+n];
	int self_code = patternscode.calc_code_fast(n,n);
	if (codes.find(self_code) != codes.end() || new_codes.find(self_code) != new_codes.end()) {
		return false;

	}
	else {
		new_codes.insert(self_code);
	}
	return true;
}

/**
Scheme Scheme::direct_product(Scheme scheme) {
	vector <string>  new_patterns;

	for (string pattern_1 : patterns) {
		for (string pattern_2 : scheme.patterns) {
			new_patterns.push_back(pattern_1 + pattern_2);
		}
	}
	string new_name = name + "_X_" + scheme.name;
	samples = new_patterns[0].size(); // n or o 
	Scheme new_scheme = Scheme(new_name, ncs, samples, new_patterns);
	return new_scheme;
}
**/

string Scheme::full_str(PatternsCodes &patternscode) {
	string s = "";
	string all_p = "";

	for (int i : patterns) {
		all_p = all_p + patternscode.patterns[i] + "\n";
	}
	s = "[ELB samples = " + to_string(samples) + " patterns = " + to_string(patterns.size()) + "]\n" + all_p;
	return s;
}



Scheme_compact::Scheme_compact() {}


Scheme_compact::Scheme_compact(Scheme &scheme) {
    patterns = patterns;
    simplified=simplified;
    samples = scheme.samples;


}



string Scheme_compact::full_str(PatternsCodes &patternscode) {
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
        all_p = all_p + patternscode.patterns[i] + "\n";
    }
    s = header + sv + all_p;
    //s = header + all_p;
    return s;
}

