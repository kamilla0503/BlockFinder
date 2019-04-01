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


    valarray <int>  codes;
    vector <string> codes_list;
    vector<string> simple_form;
    map <string, int> code_to_number;

    int calc_code_fast(int pattern1, int pattern2);





    int min_depth;

    PatternsCodes( vector<string> a_patterns, NCS ncs  , int min_depth=1  );
    PatternsCodes();
    void create_codes_table();
    void setPatternsCodes(vector<string> a_patterns, NCS a_ncs , int min_depth=1 );



};




bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);
map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns);
tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type);
int index_of_type(labeltype label_type);
tuple<int, int > count_type_in_list_of_patterns(vector<int>  patterns,labeltype label_type, PatternsCodes &patternscode);





#endif //FORWORK_PATTERNCODES_H
