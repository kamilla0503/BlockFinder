//
// Created by kamilla on 20.03.19.
//

#ifndef FORWORK_TASKS_H
#define FORWORK_TASKS_H

#include <boost/regex.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

class Task4run{
public:
    vector<int> start;
    vector<int> end;
    int    number;
    string name;

    Task4run(vector<int>t_start = {}, vector<int>t_end ={}, int t_num = -1, string t_name = "");
    Task4run(string line);
    void update_name(string base = "Task");
    operator string() const;
};

bool operator ==(Task4run t1, Task4run t2);
vector<int> string_to_vector_int(const string str);
ostream& operator<<( const Task4run& t, ostream& os );


#endif //FORWORK_TASKS_H
