#include"scheme.h"


bool operator<(const Scheme& t1, const Scheme& t2) {
	return (t1.simplified < t2.simplified);
}

bool Scheme::operator<(const Scheme& t2) {
	return (this->simplified < t2.simplified);
}

bool operator==(const Scheme& t1, const Scheme& s2) {
	return (t1.simplified == s2.simplified);
}

bool Scheme::check_codes() {
	set <string> codes;
	string code; 
	bool first = true;
	for (string pattern_1 : patterns) {
		for (string pattern_2 : patterns) {
			code = ncs.calc_code(pattern_1, pattern_2);
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


void Scheme::setscheme(string sname, NCS sncs, int  bsamples, vector <string>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	ncs = sncs;
	set <string> codes; 
	good = check_codes();
	map <string, int> simplified;
	simplify();
	set <string> new_codes;
}


void Scheme::simplify() {
	string simple_pattern;
	simplified = {};
	for (string pattern : patterns) {
		simple_pattern = simplify_pattern(pattern);
		if ((simplified.size() != 0) && (simplified.find(simple_pattern) != simplified.end())) {
			simplified[simple_pattern] = simplified[simple_pattern] + 1;
		}
		else {
			simplified[simple_pattern] = 1;
		}
	}
}

Scheme::Scheme(string sname, NCS sncs, int  bsamples, vector <string>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	ncs = sncs;
	set <string> codes; //
	good = check_codes();
	simplify();
	set <string> new_codes;
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

void Scheme::sort() {  
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
}

void Scheme::add_new_codes(string new_pattern) {
	for (string pattern : patterns) {
		codes.insert(ncs.calc_code(pattern, new_pattern));
		codes.insert(ncs.calc_code(new_pattern, pattern));
	}

	codes.insert(ncs.calc_code(new_pattern, new_pattern));

}

void Scheme::add_pattern(string new_pattern) {
	patterns.push_back(new_pattern);
	add_new_codes(new_pattern);
	simplify();
}



bool Scheme::try_pattern(string  new_pattern) {
	if (good == false) {
		return false;
	}
	set <string> new_codes;
	string code_1, code_2;
	if (find(patterns.begin(), patterns.end(), new_pattern) != patterns.end()) {
		return false;
	}
	for (string pattern : patterns) {

		code_1 = ncs.calc_code(pattern, new_pattern);
		code_2 = ncs.calc_code(new_pattern, pattern);
		
		if (codes.find(code_1) != codes.end() || codes.find(code_2) != codes.end() || (code_2 == code_1) || new_codes.find(code_1) != new_codes.end() || new_codes.find(code_2) != new_codes.end()) {

			return false;
		}
		else {
			new_codes.insert(code_1);
			new_codes.insert(code_2);
		}

	}
	string self_code = ncs.calc_code(new_pattern, new_pattern);
	if (codes.find(self_code) != codes.end() || new_codes.find(self_code) != new_codes.end()) {
		return false;

	}
	else {
		new_codes.insert(self_code);
	}
	return true;
}

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


string Scheme::full_str() {
	string s = "";
	string all_p = "";

	for (string i : patterns) {
		all_p = all_p + i + "\n";
	}
	s = "[ELB samples = " + to_string(samples) + " patterns = " + to_string(patterns.size()) + "]\n" + all_p;
	return s;
}