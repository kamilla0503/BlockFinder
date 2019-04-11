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
    /*cout<<"@@@  create_labeltype_flags @@@";*/
    for(int p=0; p<n_patterns; p++){
	string pattern = simple_form[p];
	int s = simple_ints[p];
	/*cout<<p<<" simple_form="<<pattern<<" "<<" s="<<s<<endl;*/
	for(int l=0; l< ncs.label_types.size(); l++){
	  labeltype lt = ncs.label_types[l];
	  if(find(pattern.begin(), pattern.end(), lt.name)!=pattern.end()){
	     have_labeltype_pattern_flag[p][l] = true;
	     have_labeltype_simplified_flag[s][l] = true;
	  }
	}
    }
}

void PatternsCodes::print_flags(){
   for(int p=0; p<n_patterns; p++){
      int s = simple_ints[p];
      cout<<"p= "<<setw(3)<<p<<" "<<patterns[p]<<" s="<<setw(3)<<s<<" "<<simple_form[s]<<" flags= \'";
      for(int l=0;l<ncs.label_types.size();l++){
         if (have_labeltype_pattern_flag[p][l]){
	     cout<<ncs.label_types[l].name;
         }else{
	     cout<<" ";
         }
      }
      cout<<"\'"<<endl;
   }
   for(int s=0;s<n_simplified;s++){
      cout<<"s= "<<setw(3)<<s<<" "<<unique_simplified_patterns[s]<<" flags=\'";
      for(int l=0;l<ncs.label_types.size();l++){
	if (have_labeltype_simplified_flag[s][l]){
	   cout<<ncs.label_types[l].name;
	}else{
	  cout<<" ";
	}
      }
      cout<<"\'"<<endl;
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
    map <string, int> simplified_map = {};
    int unique_simple_count = -1; /* will be incremented */
    int pattern_simple_int;
    for(int i =0; i<patterns.size(); i++){
      string simple_pattern = simplify_pattern(patterns[i]);
      auto seek_pattern = simplified_map.find(simple_pattern);
      if (seek_pattern == simplified_map.end() ){
        unique_simplified_patterns.push_back(simple_pattern);
	unique_simple_count++;
	pattern_simple_int = unique_simple_count;
        simplified_map[simple_pattern]=pattern_simple_int;
      }
      else{
	pattern_simple_int = simplified_map[simple_pattern];
      }
      simple_form.push_back(simple_pattern);
      simple_ints.push_back(pattern_simple_int);
      /*cout<<i<<" pattern="<<patterns[i]<<
	", simple_pattern= "<<simple_pattern<<
	", unique_simple_count = "<<unique_simple_count<<endl;*/
      
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
