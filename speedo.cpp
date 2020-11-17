
#include "speedo.h"

Speedo::Speedo():
  counter(0),last_counter(0),
  wall_time(0.0), last_wall_time(0.0),
  cpu_time(0.0), last_cpu_time(0.0)
{};

Speedo::Speedo(unsigned long long cnt, double wall_t, double cpu_t):
  counter(cnt),last_counter(cnt),
  wall_time(wall_t), last_wall_time(wall_t),
  cpu_time(cpu_t), last_cpu_time(cpu_t)
{};

void Speedo::clear() {
  counter = 0;
  last_counter = 0;
  cpu_time = 0.0;
  last_cpu_time = 0.0;
  wall_time = 0.0;
  last_wall_time = 0.0;
};

void Speedo::start() {
  clear();
  start_cpu_time = clock();
  clock_gettime(CLOCK_MONOTONIC, &start_wall_time);
};

std::string Speedo::readable_date_time() {
  std::ostringstream oss;
  system_clock::time_point chrono_now_time = system_clock::now();
  std::time_t readable_time = system_clock::to_time_t(chrono_now_time);
  oss<<std::ctime(&readable_time);
  return oss.str();
}


void Speedo::count(int add) {
  counter+=add; 
};
    
void Speedo::stop(int add) { 
  count(add); 
	stop(); 
};


void Speedo::check_point() {
  last_cpu_time = cpu_time;
  last_wall_time = wall_time;
  last_counter = counter;
  
  measure_time(); 
}

void Speedo::measure_time() {
  this_cpu_time = clock();
  clock_gettime(CLOCK_MONOTONIC, &this_wall_time);

  double the_wall_time = (this_wall_time.tv_sec - start_wall_time.tv_sec);
  the_wall_time += (this_wall_time.tv_nsec - start_wall_time.tv_nsec) / 1000000000.0;
  wall_time = the_wall_time;

  double the_cpu_time = (double)(this_cpu_time - start_cpu_time) / CLOCKS_PER_SEC;
  cpu_time = the_cpu_time;
}

void Speedo::stop() {
  measure_time();
};
 
double Speedo::cpu_speed() { 
  return (counter - last_counter)/(cpu_time - last_cpu_time);
};

double Speedo::wall_speed(){ 
  return (counter - last_counter)/(wall_time - last_wall_time); 
};
 
double Speedo::mean_cpu_speed() { 
  return counter/cpu_time;
};

double Speedo::mean_wall_speed(){ 
  return counter/wall_time; 
};
    
Speedo Speedo::operator+(Speedo const& sadd){
  return Speedo(counter + sadd.counter, wall_time + sadd.wall_time, cpu_time + sadd.cpu_time);
};

Speedo& Speedo::operator+=(Speedo const& sadd){
  counter+= sadd.counter;
  wall_time+= sadd.wall_time;
  cpu_time+= sadd.cpu_time;
  return *this;
};

void Speedo::operator++() {
  ++counter;
}

void Speedo::operator++(int) {
  counter++;
}

Speedo::operator std::string() const {;
  return std::to_string(counter);
};

std::ostream& operator<<(std::ostream& stream, const Speedo& spd){
  return stream<<spd.counter;
};

