//
// Created by kamilla on 20.03.19.
//

#include "tasks.h"
using namespace std;
using namespace boost;

Task4run::Task4run ( vector<int> t_start, vector<int> t_end, int t_num, string t_name){
    start =  t_start;
    end =    t_end;
    number = t_num;
    name =   t_name;
    if( number >=0 && name == ""){
       update_name();
    }
}

Task4run::Task4run (string line){
  //string task_re = "Task(?<task>\\d+) +start= +(?<start>(\\d+ +)+) +end= +(?<end>(\\d+ +)+)";
  string task_re = "Task(?<task>\\d+) +start= +(?<start>(\\d+ +)+)end= +(?<end>(\\d+ *)+)";
  regex e(task_re);
  smatch what;
  if(regex_match(line, what, e)){
//int task_id = what["task"]
     for (size_t i = 0; i < what.size(); ++i) {
        ssub_match sub_match = what[i];
        string piece = sub_match.str();
        cout << "  submatch " << i << ": \'" << piece << "\'"<<endl;
     }
     number = stoi(what["task"]);
     update_name();
     cout<<"Task name =   "<<name<<endl;
     cout<<"Task number = "<<number<<endl;
     vector <int> start(0);
     vector <int> end(0);
     cout<<"start size = "<<start.size()<<endl;
     cout<<"  end size = "<<  end.size()<<endl;
     istringstream s_start(what["start"]);
     istringstream s_end(what["end"]);
     int v;
     do {
       s_start >> v;
       start.push_back(v);
     }while(s_start);
     do {
       s_end >> v;
       end.push_back(v);
     }while(s_end);
     cout<<"start size = "<<start.size()<<endl;
     cout<<"  end size = "<<  end.size()<<endl;

  }else{
     cout<<"   ERROR: Can't parse restart line:"<<endl<<line<<endl; 
  }
}

void Task4run::update_name(string base_str){
   ostringstream tmp;
   tmp<<base_str<<setw(5)<<setfill('0')<<number;
   name = tmp.str();
}
