
#include "counter.h"

/*Counter::Counter(){
  counter = 0;
  cpu_time = 0.0;
  wall_time = 0.0
}*/

void Counter::clear() {
  counter = 0;
  cpu_time = 0.0;
  wall_time = 0.0;
};

void Counter::start() {
  start_cpu_time = clock();
  clock_gettime(CLOCK_MONOTONIC, &start_wall_time);
};
    
void Counter::count(int add) {
  counter+=add; 
};
    
void Counter::stop(int add) { 
  count(add); 
	stop(); 
};

void Counter::stop() {
  stop_cpu_time = clock();
  clock_gettime(CLOCK_MONOTONIC, &stop_wall_time);

  double the_wall_time = (stop_wall_time.tv_sec - start_wall_time.tv_sec);
  the_wall_time += (stop_wall_time.tv_nsec - start_wall_time.tv_nsec) / 1000000000.0;
  wall_time += the_wall_time;

  double the_cpu_time = (double)(stop_cpu_time - start_cpu_time) / CLOCKS_PER_SEC;
  cpu_time += the_cpu_time;
};
 
double Counter::get_cpu_speed() { 
  return counter/cpu_time;
};

double Counter::get_wall_speed(){ 
  return counter/wall_time; 
};
