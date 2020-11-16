#pragma once
#include"ncs.h"
#include <stdexcept>
#include "PatternCodes.h"
#include <vector>

/*
#ifdef __AVX512__
const int Align=64;
#else
const int Align=32;
#endif
* */

typedef valarray<bool> Vbool;
/*
class Vbool: public valarray<bool> {
    public:
    Vbool():valarray<bool>(){};
    Vbool(bool v, int N):valarray<bool>(v, N){};
    using valarray<bool>::operator =;
    Vbool& set_true(const uint *a, int n){
        for(int i=0; i<n; ++i)(*this)[a[i]]=true;
        return *this;
    }
    bool is_true(const uint *a, int n)const{
        for(int i=0; i<n; ++i){
            if((*this)[a[i]]) return true;
        }
        return false;
    }
};
* */

class Scheme {
public:
	string name;
	NCS *ncs_ptr;
	PatternsCodes *code_tab_ptr; 
	int samples;
	vector <int> patterns;
	Vbool codes;
	// Vbool new_codes;
    vector <int> simplified;

	bool good;
	Scheme();
	Scheme(PatternsCodes *patternscode, string sname , NCS *sncs, 
            int bsamples=0, vector<int> bpatterns = {});

	bool check_codes();
	void simplify();
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(int new_pattern);
	void add_pattern(int new_pattern);
	bool try_pattern(int  new_pattern);
	Scheme direct_product(Scheme scheme);
	string full_str();
	void setscheme(PatternsCodes *patternscode, string sname, NCS *sncs, 
            int bsamples=0, vector<int> bpatterns = {});

	bool operator<(const Scheme & t2);
};
bool operator==(const Scheme& s1, const Scheme& t2);
bool operator<(const Scheme& t1, const Scheme& t2);


class Scheme_compact{
public:
	int samples;
	PatternsCodes *code_tab_ptr;
    vector <int> patterns;
    vector <int> simplified;
    Scheme_compact(){};
	Scheme_compact(Scheme &scheme);
	void sort();

	string full_str();

};
bool operator==(const Scheme_compact& s1, const Scheme_compact& t2);
bool operator<(const Scheme_compact& t1, const Scheme_compact& t2);
