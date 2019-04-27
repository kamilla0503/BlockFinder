//
// Created by kamilla on 20.03.19.
//

#ifndef FORWORK_TASKS_H
#define FORWORK_TASKS_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

class Task4run{
public:
    vector<int> start;
    vector<int> end;
    int    number;
    string name;

    Task4run(vector<int>t_start = {}, vector<int>t_end ={}, int t_num = -1, string t_name = "");
    void update_name(string base = "Tasks/Task");

};




#endif //FORWORK_TASKS_H
