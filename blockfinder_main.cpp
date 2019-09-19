#include<pthread.h>
//temporary
#include<time.h>
#include<iomanip>
#include<iostream>
#include<sstream>

#include<boost/asio.hpp> // host_name
#include<boost/program_options.hpp>
namespace po = boost::program_options;
//temporary


//#include<boost/chrono.hpp> // process_system_cpu_clock
#include<chrono>

#include "ctpl.h"
#include "blockfinder.h"

using namespace std;
using namespace boost::asio::ip;
using namespace std::chrono;

int main(int argc, char *argv[]) {
   
   unsigned int ncpu_onboard = std::thread::hardware_concurrency(), 
                ncpu = ncpu_onboard;
   string name_ncs;
   NCS ncs;
   int samples, min_depth, parallel_depth, task_size;
   int auto_min_t_free = -1;
   bool list_ncs;
      
   po::options_description desc("Usage:\nblockfinder NCS samples min-patterns [options]\nAvailable options");
   po::positional_options_description pos_desc;
  
   try {

      desc.add_options()
         ("help", "produce help message")
         ("NCS", po::value<string>(&name_ncs), "Name of NCS, e.g. NC2. Use option --list-ncs for all supporten NCS")
         ("samples", po::value<int>(&samples), "Number of samples, e.g. 3")
         ("min-patterns", po::value<int>(&min_depth), "Minimal number of patterns in scheme, e.g. 3")
         ("ncpu,n", po::value<unsigned int>(&ncpu)->default_value(ncpu_onboard), "Number of CPU to use")
         ("parallel-depth,d", po::value<int>(&parallel_depth)->default_value(1), "Execute in parallel from that depth")
         ("task-size,t", po::value<int>(&task_size)->default_value(200), "The size of task to be executed in parallel")
         ("list-ncs", "List all supporten NCS")
      ;
      pos_desc.add("NCS", 1)
              .add("samples", 1)
              .add("min-patterns", 1);
      po::variables_map vm;
      po::store(po::command_line_parser(argc, argv).
              options(desc).positional(pos_desc).run(), vm);
      po::notify(vm);
     
      if(ncpu>ncpu_onboard){
        cout<<"Too many CPU selected: "<<ncpu<<", set ncpu to "<<ncpu_onboard<<endl;
        ncpu=ncpu_onboard;
      }


      if (vm.count("help")) {
         cout << desc << endl;
         return 1;
      }
      
      if (vm.count("list-ncs")) {
         cout << "The list of supported NCS:" << endl;
         for(string s: ncs.ALL_NCS_NAME)
           cout<<s<<" ";
         cout<<endl;
         return 1;
      }

      if (vm.count("NCS")) {
         name_ncs = vm["NCS"].as<string>();
         try{
            NCS ncs_new = get_NCS(name_ncs);
            ncs = ncs_new;
         }catch(UnknownNCS& e){
            cout<< e.what() << std::endl;
            return(-1);
         }
      } else {
         cout <<"Missing recquired argument: NCS"<<endl;
         cout << desc << endl;
         return -1;
      };


      if (! vm.count("samples")) {
         cout <<"Missing recquired argument: samples"<<endl;
         cout << desc << endl;
         return -1;
      }
      
      if (! vm.count("min-patterns")) {
         cout <<"Missing recquired argument: min-patterns"<<endl;
         cout << desc << endl;
         return -1;
      }

   }catch(const po::error & ex){
      cerr << ex.what() <<endl;
      cerr << desc << endl;
      cerr << "exiting"<<endl;
      return(-1);
   };

   system_clock::time_point now_time = system_clock::now();
   auto readable_time = system_clock::to_time_t(now_time);
   cout <<"===== BlockFinder started ====="<<endl;
   cout <<"Host:     "<<host_name()<<endl;
   cout <<"Command:  ";

   for(int arg=0; arg<argc;arg++)cout<<argv[arg]<<" ";
   cout<<endl;
   cout<<"Date/Time: "<<std::ctime(&readable_time)<<endl;

   cout << "NCS with name "<<ncs.name << " generated" << endl;
   if( (ncs.name=="ALT12" || ncs.name=="NCDAT12" ) && samples == 3){
       auto_min_t_free = 8;
       cout<<"Automatically set min_t_free = 8"<<endl;
   }
   else if( ( ncs.name=="ALT12" || ncs.name=="NCDAT12" ) && samples == 4){
      auto_min_t_free = 16;
      cout<<"Automatically set min_t_free = 16"<<endl;
   }else{
      cout<<"Checks of  min_t_free is swithced off"<<endl;
   }


   PatternsCodes empty_table;
   BlockFinder b(samples, ncs, min_depth, auto_min_t_free, empty_table);
   b.parallel_depth = parallel_depth;
   b.task_size = task_size;

   cout<<"CREATE TASKS STARTED "<<endl;
   b.create_tasks();
   cout<<"CREATE TASKS FINISHED. "<<to_string(b.tasks.size())<<" TASKS CREATED"<<endl;


   ctpl::thread_pool p(ncpu);

   ofstream taskfile;


   // Initialize timers
   struct timespec wall_clock_start, wall_clock_finish;
   clock_t cpu_usage_start, cpu_usage_finish;   
   cpu_usage_start = clock();
   clock_gettime(CLOCK_MONOTONIC, &wall_clock_start);


   cout << endl;
   int numbertask=0;
   // std::future<void> qw = p.push(find_schemes,
   cout<<"RUNNING ALL "<<to_string(b.tasks.size())<<" IN PARALLEL ON "<<to_string(p.size())<<" THREADS"<<endl;

   cout_locker Cout_Lock;
   for (Task4run t : b.tasks){
      p.push(find_schemes, samples, ncs, min_depth, auto_min_t_free, b.code_table, b.patterns_listl, b.patterns[0], t, & Cout_Lock);
      numbertask=numbertask+1;
   }


   // Wait for all jobs to finish
   p.stop(true);
   cout<<"EXECUTION OF ALL "<<to_string(numbertask)<<" TASKS FINISHED"<<endl;
   cpu_usage_finish = clock();
   clock_gettime(CLOCK_MONOTONIC, &wall_clock_finish);


   double cpu_usage_seconds = (double)(cpu_usage_finish - cpu_usage_start) / CLOCKS_PER_SEC;
   double wall_clock_seconds = (wall_clock_finish.tv_sec - wall_clock_start.tv_sec);
   wall_clock_seconds += (wall_clock_finish.tv_nsec - wall_clock_start.tv_nsec) / 1000000000.0;
   
   printf("The CPU usage time:   %f seconds\n", cpu_usage_seconds);
   printf("The wall clock time:  %f seconds\n", wall_clock_seconds);
   printf("CPU/wall clock ratio: %5.2f\n", cpu_usage_seconds/wall_clock_seconds);

   return 0;
}
