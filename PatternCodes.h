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
    int n_patterns;     /* number of patterns */
    int n_simplified;   /* number of unique simplified patterns */

    valarray <int>  codes; /* of size n_patterns * n_patterns */
    vector <string> codes_list;  
    vector <string> simple_form; /* of size n_patterns */
    vector <string> unique_simplified_patterns; /* of size n_simplified */
    vector <int>    simplified_ints;  /* of size n_patterns, 
					 index of simple_form in unique_simplified_patterns */
    map <string, int> code_to_number;

    int calc_code_fast(int pattern1, int pattern2) const;





    int min_depth;

    PatternsCodes( vector<string> a_patterns, NCS ncs  , int min_depth=1  );
    PatternsCodes();
    void setPatternsCodes(vector<string> a_patterns, NCS a_ncs , int min_depth=1 );
private:
    void create_codes_table();
    void create_simplified_table();



};


inline int PatternsCodes::calc_code_fast(int pattern1, int pattern2) const {
    int n =patterns.size();
    return codes[pattern1*n+pattern2];
}



bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);
map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns);
tuple<int, int > count_type_in_list_of_simplified(PatternsCodes & patternscodes, vector <int>& simplified, int index_of_type);
int index_of_type(labeltype label_type);
tuple<int, int > count_type_in_list_of_patterns(vector<int>  patterns,labeltype label_type, PatternsCodes &patternscode);





#endif //FORWORK_PATTERNCODES_H
