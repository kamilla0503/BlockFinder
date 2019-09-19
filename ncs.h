//#pragma once
#ifndef NCS_H_INCLUDED
#define NCS_H_INCLUDED
#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<regex>
#include<tuple>
#include<time.h>
#include<algorithm>
#include<valarray>
#include<exception>


//#include<tr1>
using namespace std;

static constexpr int N_LABELTYPES = 8;

class UnknownNCS: public exception 
{
  private:
     std::string unknown_ncs_name_;
     std::string unknown_ncs_message_;
  public:
     explicit UnknownNCS(const std::string& ncs_name);
     virtual const char* what() const throw()
     {
        return unknown_ncs_message_.c_str();
     }
};

class labeltype {
public:
	//string name;
	//int  isotopes;
	//bool HN, CA, CO;
	char name; 
	bool label_HN, label_CA, label_CO;
	// 
	labeltype();
	labeltype(char lname, bool l_HN, bool l_CA, bool l_CO);
	/* Constructor is NMR-specific, the code is located in file nmr.cpp  */
	labeltype(char lname);

	bool operator<(const labeltype & t2);

};

//labeltype typeT("T", 1, 1, 0);

bool operator<(const labeltype& t1, const labeltype& t2);
bool operator==(const labeltype& t1, const string& s2);
bool operator==(const string& s1, const labeltype& t2);




class spectrum {
public:
	string name;
	spectrum(string sname);
	/* method is NMR-specific, the code is located in file nmr.cpp  */
	int has_signal(labeltype label_type_1, labeltype label_type_2);
};

typedef string pattern_type;

class NCS {
public:
	const vector <char> NITRO_TYPES = { 'N', 'D', 'S', 'T' };
   const vector<string> ALL_NCS_NAME = 
      { "NC2",    "NC2noX", 
        "NCD2",   "NCD2noX", 
        "NCD4",   "NCD4noX", 
        "NCD6",   "NCD6noX", 
        "NCDA8",  "NCDA8noX", 
        "2H-ND2", "2H-ND3",  
        "ALT12",  "ALT12noF", "NCDAT12", "ALT12noX" };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	//map<pattern_type, labeltype> label_dict
	map<char, labeltype> label_dict;
	vector <char> letters;
   int index_of_labeltype(labeltype);
   int index_of_labeltype(char);
	//vector <> spectra_numbers; 
	map<labeltype, int> label_power;
	map <labeltype, map <labeltype, string>> codes_dict;
	vector <vector <int>> vectors;
	//map <labeltype, string> subdict;
	
	//name, spectra_list, label_types, deuterated = False)
	//NCS(string name_ncs, vector<spectrum>spectra_list_ncs, vector<labeltype> label_types_ncs, bool deuterated_ncs = false);
	NCS();
	NCS(string name_ncs, vector<spectrum>spectra_list_ncs = {}, vector<labeltype> label_types_ncs = {}, bool deuterated_ncs = 0);
	/* Constructor is NMR-specific, the code is located in file nmr.cpp  */
	NCS(string name_ncs, vector<string>spectra_names = {}, string label_types_string = "", bool deuterated_ncs = 0);
	void make_coding_table(void); 
	NCS& operator=(NCS& other);
//	NCS operator=(NCS other);
	string calc_code(string pattern_1, string pattern_2);
	bool check_power(string new_pattern,int min_depth);
};
NCS get_NCS(string name);

#endif  // NCS_H_INCLUDED

