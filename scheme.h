//#pragma once
#include"ncs.h"
#include "PatternCodes.h"
class Scheme {
public:
	string name;
	NCS ncs;
	int samples;
	vector <int> patterns;
	set <int> codes;
	set <string> new_codes;
	map <string, int> simplified;

	//PatternsCodes code_table;

	bool good;
	Scheme();
	Scheme(PatternsCodes &patternscode, string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <int>  bpatterns = {});

        // Scheme( string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <int>  bpatterns = {});

	bool check_codes(PatternsCodes &patternscode);
	void simplify( PatternsCodes &patternscode  );
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(int new_pattern, PatternsCodes &patternscode);
	void add_pattern(int new_pattern, PatternsCodes &patternscode);
	bool try_pattern(int  new_pattern, PatternsCodes &patternscode);
	Scheme direct_product(Scheme scheme);
	string full_str(PatternsCodes &patternscode);
	void setscheme(PatternsCodes &patternscode, string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <int>  bpatterns = {});

	bool operator<(const Scheme & t2);
};
bool operator==(const Scheme& s1, const Scheme& t2);
bool operator<(const Scheme& t1, const Scheme& t2);
