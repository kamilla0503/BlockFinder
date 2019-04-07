//
// Created by kamilla on 06.03.19.
//

#include"PatternCodes.h"



PatternsCodes::PatternsCodes( vector<string> a_patterns, NCS a_ncs      ){
    patterns=a_patterns;
    n_patterns = patterns.size();
    ncs = a_ncs;

    create_simplified_table();
    create_labeltype_flags();
    create_codes_table();

}

PatternsCodes::PatternsCodes() {
    patterns={};
    n_patterns = 0;

}


void PatternsCodes::create_labeltype_flags(){
    have_labeltype_simplified_flag.resize(n_simplified);
    have_labeltype_pattern_flag.resize(n_patterns);
    have_labeltype_simplified_flag = false;
    have_labeltype_pattern_flag = false;
    for(int p=0; p<n_patterns; p++){
	string pattern = codes_list[p];
	int s = simple_ints[p];
	for(int l=0; l< ncs.label_types.size(); l++){
	  labeltype lt = ncs.label_types[l];
	  if(find(pattern.begin(), pattern.end(), lt.name)!=pattern.end()){
	     have_labeltype_pattern_flag[p][l] = true;
	     have_labeltype_simplified_flag[s][l] = true;
	  }
	}
    }
}

void PatternsCodes::setPatternsCodes(vector<string> a_patterns, NCS a_ncs ) {

    patterns=a_patterns;
    n_patterns = patterns.size();
    ncs = a_ncs;
    //int n=patterns.size();
    //valarray<int> codes(n*n);

    create_simplified_table();
    create_labeltype_flags();
    create_codes_table();
}


void PatternsCodes::create_simplified_table()
{
    simple_form={};
    unique_simplified_patterns= {};
    simple_ints = {};
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
      simple_ints.push_back(unique_simple_count);
    }
    n_simplified = unique_simplified_patterns.size();
}


void PatternsCodes::create_codes_table() {
    string symbol_code;
    int code_number;

    codes.resize(n_patterns*n_patterns);
    for(int i=0; i<n_patterns; i++){
        for (int j=0; j<n_patterns; j++){
            symbol_code= ncs.calc_code(patterns[i], patterns[j]);

            if( find(codes_list.begin(), codes_list.end(), symbol_code)!=codes_list.end()   ){
                code_number=distance(codes_list.begin(),    find(codes_list.begin(), codes_list.end(), symbol_code) );
            }
            else{
                code_number=codes_list.size();
                code_to_number[symbol_code]=code_number;
                codes_list.push_back(symbol_code);
            }
            codes[i*n_patterns+j]=code_number;
        }
    }
}
