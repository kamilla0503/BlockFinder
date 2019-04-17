//
// Created by kamilla on 20.03.19.
//

#include "tasks.h"


Task4run::Task4run ( vector<int> t_start, vector<int> t_end, int t_num, string t_name){
    start =  t_start;
    end =    t_end;
    number = t_num;
    name =   t_name;
    if( number >=0 && name == ""){
       update_name();
    }
}

void Task4run::update_name(string base_str){
   ostringstream tmp;
   tmp<<base_str<<setw(4)<<setfill('0')<<number;
   name = tmp.str();
}
