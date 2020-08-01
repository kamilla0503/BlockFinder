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
  regex task_e(task_re);
  smatch what;
  if(regex_match(line, what, task_e)){
//int task_id = what["task"]
//     for (size_t i = 0; i < what.size(); ++i) {
//        ssub_match sub_match = what[i];
//        string piece = sub_match.str();
//        cout << "  submatch " << i << ": \'" << piece << "\'"<<endl;
//     }
     number = stoi(what["task"]);
     update_name();
     //cout<<"Task name =   "<<name<<endl;
     //cout<<"Task number = "<<number<<endl;
     start = string_to_vector_int(what["start"]);
     end   = string_to_vector_int(what["end"]);
     //cout<<"start size = "<<start.size()<<endl;
     //cout<<"  end size = "<<  end.size()<<endl;
     //cout<<"start = ";  
     //for(int v : start)
     //  cout<<v<<" "; 
     //cout<<endl;
     //cout<<"  end = ";  
     //for(int v :   end)
     //  cout<<v<<" "; 
     //cout<<endl;

  }else{
     cout<<"   ERROR: Can't parse restart line:"<<endl<<line<<endl; 
  }
}

Task4run::operator string() const {
  ostringstream out;
  out<<name<<" start= ";
  for (int i: start)
    out <<setw(4)<< i << " ";
  out<<" end= ";
  for (int i: end)
    out <<setw(4)<< i << " ";
  return out.str();  
}

void Task4run::update_name(string base_str){
   ostringstream tmp;
   tmp<<base_str<<setw(5)<<setfill('0')<<number;
   name = tmp.str();
}


bool operator==(Task4run t1, Task4run t2){
  if (t1.number != t2.number) return false;
  if (t1.name != t2.name) return false;
  if (t1.start != t2.start) return false;
  if (t1.end != t2.end) return false;
  return true;
}


vector<int> string_to_vector_int(const string str){
     istringstream input(str);
     vector<int> result(0);
     int v;
     while(input >> v) {
       result.push_back(v);
     };
     return result;
}


ostream& operator<<( const Task4run& t, ostream& os ){
  return os<<((string)(t));
}
