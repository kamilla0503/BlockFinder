//#pragma once
#include"ncs.h"
#include "PatternCodes.h"
class Scheme {
public:
	string name;
	NCS *ncs_ptr;
	PatternsCodes *code_tab_ptr; 
	int samples;
	//vector <int> patterns;
	valarray<int> patterns;
	int number_of_patterns;
	//set <int> codes;
	valarray <bool> codes;
	//set <string> new_codes;
	valarray <bool> new_codes;
//	map <string, int> simplified;
    valarray<int> simplified;
        //vector <int> simplified;

	//PatternsCodes code_table;

	bool good;
	Scheme();
	Scheme(int listsize, PatternsCodes *patternscode, string sname , NCS *sncs , int  bsamples = 0, vector <int>  bpatterns = {});

	bool check_codes();
	void simplify();
	//bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(int new_pattern);
	void add_pattern(int new_pattern);
	bool try_pattern(int  new_pattern);
	Scheme direct_product(Scheme scheme);
	string full_str();
	void setscheme(int listsize, PatternsCodes *patternscode, string sname, NCS *sncs , int  bsamples = 0, vector <int>  bpatterns = {});

	bool operator<(const Scheme & t2);
};
bool operator==(const Scheme& s1, const Scheme& t2);
bool operator<(const Scheme& t1, const Scheme& t2);

class Scheme_compact{
public:
	int samples;
	PatternsCodes *code_tab_ptr;
	valarray <int> patterns;
	valarray <int> simplified;

    int number_of_patterns;

    Scheme_compact();
	Scheme_compact(Scheme &scheme);
	void sort();

	string full_str();

};


bool operator==(const Scheme_compact& s1, const Scheme_compact& t2);
bool operator<(const Scheme_compact& t1, const Scheme_compact& t2);
