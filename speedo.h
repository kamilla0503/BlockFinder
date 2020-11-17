
#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED


#include<time.h>
#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<chrono>

using namespace std::chrono;

//  Simple speedometer for speed testing
//  Counts number of events and time spend after check_point()
//  Returns wall_speed or cpu_speed on reqest

class Speedo {
  public:
    unsigned long long counter, last_counter;
    double cpu_time, last_cpu_time;
    double wall_time, last_wall_time;
    time_t start_cpu_time, this_cpu_time;
    struct timespec start_wall_time, this_wall_time;

    Speedo();
    Speedo(unsigned long long cnt, double wall_t, double cpu_t);
    std::string readable_date_time();
    
    void clear();
    void start();
    void count(int add);
    void measure_time();
		void check_point();
    void stop();
    void stop(int add);
    Speedo& operator+=(Speedo const& sadd);

		double cpu_speed();
    double wall_speed();
		double mean_cpu_speed();
    double mean_wall_speed();
    Speedo operator+(Speedo const& sadd);
		void operator++();    /* prefix increment  */
		void operator++(int); /* postrix increment */
		explicit operator std::string() const;
		friend std::ostream& operator<<(std::ostream& stream, const Speedo& spd);
};


#endif
