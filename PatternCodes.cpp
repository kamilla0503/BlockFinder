//
// Created by kamilla on 06.03.19.
//

#include"PatternCodes.h"



PatternsCodes::PatternsCodes( vector<string> a_patterns, NCS a_ncs , int min_d      ){
    patterns=a_patterns;
    ncs = a_ncs;
    min_depth = min_d;
    create_codes_table();

    simple_form={};
    for(int i =0; i<patterns.size(); i++){
        simple_form.push_back(simplify_pattern(patterns[i]));
    }


}

PatternsCodes::PatternsCodes() {
    patterns={};

}

void PatternsCodes::setPatternsCodes(vector<string> a_patterns, NCS a_ncs , int min_d ) {

    patterns=a_patterns;
    ncs = a_ncs;
    min_depth = min_d;
    int n=patterns.size();
    //valarray<int> codes(n*n);

    create_codes_table();

    simple_form={};
    for(int i =0; i<patterns.size(); i++){
        simple_form.push_back(simplify_pattern(patterns[i]));
    }



}


int PatternsCodes::calc_code_fast(int pattern1, int pattern2) {
    int n =patterns.size();
    return codes[pattern1*n+pattern2];

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