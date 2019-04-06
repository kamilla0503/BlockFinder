//
// Created by kamilla on 06.03.19.
//

#include"PatternCodes.h"



PatternsCodes::PatternsCodes( vector<string> a_patterns, NCS a_ncs , int min_d      ){
    patterns=a_patterns;
    n_patterns = patterns.size();
    ncs = a_ncs;
    min_depth = min_d;

    create_simplified_table();
    create_codes_table();

}


void PatternsCodes::create_simplified_table()
{
    simple_form={};
    unique_simplified_patterns= {};
    simplified_ints = {};
    set <string> simplified_set = {};
    int unique_simple_count = 0;
    for(int i =0; i<patterns.size(); i++){
      string simple_pattern = simplify_pattern(patterns[i]);
      if (find(simplified_set.begin(), simplified_set.end(), simple_pattern) == simplified_set.end() ){
        unique_simplified_patterns.push_back(simple_pattern);
        simplified_set.insert(simple_pattern);
	unique_simple_count++;
      }
      simple_form.push_back(simple_pattern);
      simplified_ints.push_back(unique_simple_count);
    }
    n_simplified = unique_simplified_patterns.size();
}

PatternsCodes::PatternsCodes() {
    patterns={};
    n_patterns = 0;

}

void PatternsCodes::setPatternsCodes(vector<string> a_patterns, NCS a_ncs , int min_d ) {

    patterns=a_patterns;
    n_patterns = patterns.size();
    ncs = a_ncs;
    min_depth = min_d;
    //int n=patterns.size();
    //valarray<int> codes(n*n);

    create_simplified_table();
    create_codes_table();

}


void PatternsCodes::create_codes_table() {
    string symbol_code;
    int code_number;

    int n=patterns.size();

    codes.resize(n*n);
   // valarray <int>  codes(n*n); // mb
    for(int i=0; i<n; i++){
        //codes.push_back({});
        for (int j=0; j<n; j++){
            symbol_code= ncs.calc_code(patterns[i], patterns[j]);

            if( find(codes_list.begin(), codes_list.end(), symbol_code)!=codes_list.end()   ){
                code_number=distance(codes_list.begin(),    find(codes_list.begin(), codes_list.end(), symbol_code) );
            }
            else{
                code_number=codes_list.size();
                code_to_number[symbol_code]=code_number;
                codes_list.push_back(symbol_code);
            }


            codes[i*n+j]=code_number;





        }



    }



}
