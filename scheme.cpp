#include"scheme.h"
//#include<algorithm>

bool operator<(const Scheme& t1, const Scheme& t2) {
    //return (t1.simplified < t2.simplified);
    //cout << (t1.simplified == t2.simplified).sum() << " " << t1.number_of_patterns << " "<< ((t1.simplified == t2.simplified).sum()==t1.number_of_patterns) << endl;
    bool result = true;
    //if ( t1.number_of_patterns <  t2.number_of_patterns){
    //    return true;
    //}
    for (int i=0; i< t2.number_of_patterns; i++){
        if (t1.simplified[i] >= t2.simplified[i])
            return false;
    }
    return true;
    //return (t1.simplified < t2.simplified).sum()==t1.simplified.size();
}

bool operator<(const Scheme_compact& t1, const Scheme_compact& t2) {
    //return (t1.simplified < t2.simplified);
    bool result = true;

    /**if ( t1.number_of_patterns <  t2.number_of_patterns){
        return true;
    } **/

    for (int i=0; i< t2.number_of_patterns; i++){
        if (t1.simplified[i] >= t2.simplified[i])
        return false;
    }
    return true;
    //return (t1.simplified < t2.simplified).sum()==t1.simplified.size();
}

bool Scheme::operator<(const Scheme& t2) {
    //return (this->simplified < t2.simplified);
    //cout << (this->simplified == t2.simplified).sum() << " " << this->number_of_patterns << " "<< ((this->simplified == t2.simplified).sum()==this->number_of_patterns) << endl;
    bool result = true;

    /**if ( this->number_of_patterns <  t2.number_of_patterns){
        return true;
    }**/

    for (int i=0; i< t2.number_of_patterns; i++){
        if (this->simplified[i] >= t2.simplified[i])
        return false;
    }
    return true;
    //return (this->simplified < t2.simplified).sum()==this->simplified.size();
}

bool operator==(const Scheme& t1, const Scheme& t2) {
    //return (t1.simplified == s2.simplified);
    //cout << (t1.simplified == s2.simplified).sum() << " " << t1.number_of_patterns << " "<< ((t1.simplified == s2.simplified).sum()==t1.number_of_patterns) << endl;

    bool result = true;

    if ( t1.number_of_patterns !=  t2.number_of_patterns){
        return false;
    }


    for (int i=0; i< t2.number_of_patterns; i++){
        if (t1.simplified[i] != t2.simplified[i])
        return false;
    }
    return true;

    //return (t1.simplified == s2.simplified).sum()==t1.simplified.size() && t1.simplified.size()==s2.simplified.size();
}

bool operator==(const Scheme_compact& t1, const Scheme_compact& t2) {
    //return (t1.simplified == s2.simplified);
    //cout << (t1.simplified == s2.simplified).sum() << " " << t1.number_of_patterns << " "<< ((t1.simplified == s2.simplified).sum()==t1.number_of_patterns) << endl;

    bool result = true;

    if ( t1.number_of_patterns !=  t2.number_of_patterns){
        return false;
    }

    for (int i=0; i< t2.number_of_patterns; i++){
        if (t1.simplified[i] != t2.simplified[i])
        return false;
    }
    return true;
    //return (t1.simplified == s2.simplified).sum()==t1.simplified.size() && t1.simplified.size()==s2.simplified.size();
}

Scheme::Scheme() {
	patterns={};
}

bool Scheme::check_codes() {
	int code;
	bool first = true; 
	codes = false;

	//for (int i: patterns) {
		//for ( int j : patterns) {
    for ( int i=0; i<number_of_patterns; i++ ) {
        for ( int j=0; j<number_of_patterns; j++) {
			//code =  patternscode.codes[ patternscode.patterns.size()*i  +j]; //!!!
			code =  code_tab_ptr->calc_code_fast(patterns[i], patterns[j]);
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


void Scheme::setscheme(int listsize, PatternsCodes *patternscode , string sname, NCS *sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
//	valarray<int> patterns( bpatterns.data(), bpatterns.size());
    //patterns=bpatterns;
    patterns.resize(listsize, -1);
    simplified.resize(listsize, -1);
    number_of_patterns = bpatterns.size(); // пока с учетом того, что сначала массив паттернов пустой

    for (int i =0; i < number_of_patterns; i++)
    {
        patterns[ bpatterns[i]] = patterns[ bpatterns[i]]+1;
    }
    //number_of_patterns = 0;
    samples = bsamples;
	code_tab_ptr = patternscode;
	ncs_ptr = sncs;
	codes.resize(code_tab_ptr->n_codes, false);
	new_codes.resize(code_tab_ptr->n_codes, false) ;

	good = check_codes();
	simplify();

}

void Scheme::simplify() {
	//simplified.assign(code_tab_ptr->n_simplified, 0);
	simplified.resize(code_tab_ptr->n_simplified, 0);
	//for (int pattern : patterns) {
    for (int i=0; i<number_of_patterns; i++) {
	   simplified[code_tab_ptr->simple_ints[patterns[i]]]++;
	}
}

Scheme::Scheme(int listsize, PatternsCodes *patternscode, string sname, NCS *sncs, int  bsamples, vector <int>  bpatterns) {
	name = sname;
    patterns.resize(listsize, 0);
    number_of_patterns = bpatterns.size();
	samples = bsamples;
	code_tab_ptr = patternscode; 
	ncs_ptr  = sncs;
	valarray <bool> codes(false, code_tab_ptr->n_codes); //
	good = check_codes();
	simplify();
	valarray <bool> new_codes(false, code_tab_ptr->n_codes);
}

void Scheme::sort(){

	//std::sort(patterns.begin(), patterns.end());
	if(number_of_patterns>1) {
	    //std::size_t end = number_of_patterns - 1;
        std::sort(&patterns[0], &patterns[number_of_patterns -1]); //
    }
}


void Scheme_compact::sort(){

    //std::sort(patterns.begin(), patterns.end());
    if(number_of_patterns>1) {
        //std::size_t end = number_of_patterns - 1;
        std::sort(&patterns[0], &patterns[number_of_patterns -1]); //
    }

}

void Scheme::add_new_codes(int new_pattern) {
	//int n = distance(patterns.begin(), find(patterns.begin(), patterns.end(), new_pattern));
	//int m=code_tab_ptr->patterns.size(); //??? ???
    //int m=code_tab_ptr->;
    int m=code_tab_ptr->patterns.size();
    int n=new_pattern;
	//for ( int i =0; i<patterns.size(); i++) {
	//for ( int i :patterns) {
	for (int i=0; i<number_of_patterns; i++) {
	    //std:: cout << i < " ";
	    codes[code_tab_ptr->calc_code_fast(patterns[i],n)] = true;
		codes[code_tab_ptr->calc_code_fast(n,patterns[i]) ] = true;

	}
	//std:: cout <<std::endl;
    codes [  code_tab_ptr->calc_code_fast(n,n)] = true;
	//codes.insert(code_tab_ptr->calc_code_fast(n,n));

}

void Scheme::add_pattern(int new_pattern) {
	//patterns.push_back(new_pattern);
	patterns[number_of_patterns]=new_pattern;
	number_of_patterns=number_of_patterns+1;
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
	//for (int i=0; i<patterns.size(); i++) {
    for (int i=0; i<number_of_patterns; i++) {
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

	//for (int i : patterns) {
    for (int i=0; i<number_of_patterns; i++) {
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
    number_of_patterns = scheme.number_of_patterns;
}

string Scheme_compact::full_str() {
    string header= "[ELB ";
    string all_p = "";
    string sv = "[SV";
    string s;

    header = header + "samples = " + to_string(samples) + " patterns = " + to_string(number_of_patterns) + "]\n";
    //for (int int_simple : simplified) {
    for (int int_simple =0; int_simple<number_of_patterns; int_simple++ ) {
      sv = sv + " "+ to_string(simplified[int_simple]);
    }
    sv = sv + " ]\n";
    //for (int i : patterns) {
    for (int i=0; i<number_of_patterns; i++) {
        all_p = all_p + code_tab_ptr->patterns[patterns[i]] + "\n";
    }
    s = header + sv + all_p;
    //s = header + all_p;
    return s;
}