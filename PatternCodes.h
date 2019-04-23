//
// Created by kamilla on 06.03.19.
//

#ifndef FORWORK_PATTERNCODES_H
#define FORWORK_PATTERNCODES_H
#include"ncs.h"


class PatternsCodes{
public:
    vector <string> patterns;
    NCS ncs;
    unsigned long n_patterns;     /* number of patterns */
    unsigned long n_simplified;   /* number of unique simplified patterns */
    unsigned long n_codes;        /* number of different codes in table */

    valarray <int>  codes; /* of size n_patterns * n_patterns */
    vector <string> codes_list;  
    vector <string> simple_form;  /* of size n_patterns */
    vector <int>    simple_ints;  /* of size n_patterns, 
	 index of simple_form in unique_simplified_patterns */
    vector <string> unique_simplified_patterns; /* of size n_simplified */
    map <string, int> code_to_number;

    valarray<bitset<N_LABELTYPES> > have_labeltype_simplified_flag; /* of size n_simplified */
    valarray<bitset<N_LABELTYPES> > have_labeltype_pattern_flag;    /* of size n_patterns */

    inline int calc_code_fast(int pattern1, int pattern2) const{
      return codes[pattern1*n_patterns+pattern2];
    }
    
    inline bool check_label_in_simplified(int simplified, int index_of_label_type) const {
      return have_labeltype_simplified_flag[simplified][index_of_label_type];
    }

    inline bool check_label_in_pattern(int pattern, int index_of_label_type) const {
      return have_labeltype_pattern_flag[pattern][index_of_label_type];
    }

    PatternsCodes( vector<string> a_patterns, NCS ncs );
    PatternsCodes();
    void setPatternsCodes(vector<string> a_patterns, NCS a_ncs );
    void print_flags();
    
    void  simplify_list_of_patterns(const vector<int> & list_of_patterns, vector<int> & result);
    tuple<int, int > count_type_in_list_of_simplified(const vector <int> & simplified, int index_of_type);
    tuple<int, int > count_type_in_list_of_patterns(const vector <int> &  patterns, int index_of_typr);
private:
    void create_simplified_table();
    void create_labeltype_flags();
    void create_codes_table();



};



bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);





#endif //FORWORK_PATTERNCODES_H
