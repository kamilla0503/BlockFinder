
#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED


#include<time.h>
#include<string>
#include<iostream>
#include<iomanip>

//  Simple counter for speed testing
//  Counts number of events and time spend 

class Counter {
  public:
    unsigned long long counter;
    double cpu_time;
    double wall_time;
    time_t start_cpu_time, stop_cpu_time;
    struct timespec start_wall_time, stop_wall_time;

    void clear();
    void start();
    void count(int add);
    void stop();
    void stop(int add);
		double get_cpu_speed();
    double get_wall_speed();
    Counter operator+(Counter const& cadd);
};


#endif
