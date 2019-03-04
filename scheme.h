//#pragma once
#include"ncs.h"
class Scheme {
public:
	string name;
	NCS ncs;
	int samples;
	vector <string> patterns;
	set <string> codes;
	set <string> new_codes;
	map <string, int> simplified;
	bool good;
	Scheme(string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <string>  bpatterns = {});
	bool check_codes();
	void simplify();
	bool check_patterns(vector <string> patterns);
	void sort();
	void add_new_codes(string new_pattern);
	void add_pattern(string new_pattern);
	bool try_pattern(string  new_pattern);
	Scheme direct_product(Scheme scheme);
	string full_str();
	void setscheme(string sname = "", NCS sncs = NCS(), int  bsamples = 0, vector <string>  bpatterns = {});
	bool operator<(const Scheme & t2);
};
bool operator==(const Scheme& s1, const Scheme& t2);
bool operator<(const Scheme& t1, const Scheme& t2);
