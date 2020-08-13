#include <iostream>
#include "mydata.h"
#include <time.h>
#include <chrono>
#include <omp.h>

const int MaxProc=4;
typedef std::chrono::time_point<std::chrono::system_clock> t_point;
void print_timestamp(const char* str1,const t_point& start);


omp_lock_t lock;

int main(int argc, char **argv){
    const int nProc=std::min(MaxProc,omp_get_max_threads());
    t_point start = std::chrono::system_clock::now();
    std::time_t st_time = std::chrono::system_clock::to_time_t(start);
    std::string ofstream_name("vec_out2.relb");
    std::cout.setf(std::ios::unitbuf);
    int istart=1;
    if(std::string(argv[1])=="-o"){
        ofstream_name = argv[2];
        istart=3;
    }
    int nfiles=argc-istart;
    
    std::cout << "Start computation at ";
    std::cout << std::ctime(&st_time)<<std::endl;
    std::cout <<"Number of files to process: ";
    std::cout <<argc-istart<<std::endl;
    
    omp_set_num_threads(nProc);
    omp_init_lock(&lock);
    VecList lst[nfiles];   
    #pragma omp parallel for 
    for(int i=istart;i<argc;++i){
        int tid=omp_get_thread_num();
        int nThreads = omp_get_num_threads();
        VecList* cur=lst+(i-istart);
        timespec ts,ts1,ts2;
        std::ifstream in;
        std::string arg(argv[i]);
        in.open(argv[i]);
        read_veclist(in,*cur);
        int cursize=cur->size();
        clock_gettime(CLOCK_MONOTONIC, &ts);
        cur->sort(std::greater<Elem>());
        cur->unique();
        clock_gettime(CLOCK_MONOTONIC, &ts1);
        /*
        omp_set_lock(&lock);
        std::cout<<std::endl;
        std::cout<<"Thread: "<<tid<<std::endl;
        std::cout<<"Input file: "<<argv[i]<<std::endl;
        std::cout<<"Size of vector list in file: "<<cursize<<std::endl;
        std::cout<<"Calculation time (sort+unique): ";
        std::cout<<ts1.tv_sec-ts.tv_sec<<std::endl;
        std::cout<<"Size of list after unique: "<<cur->size()<<std::endl;
        omp_unset_lock(&lock);
        */
    }
        print_timestamp("Finished file reading at",start);

    SimpleVecList svlist(nfiles,lst);
    std::cout<<"Size of list after merging: "<<svlist.size()<<std::endl;
    print_timestamp("Finished list merging at",start);
    svlist.sort(std::greater<ElemPoint>());
    print_timestamp("Finished list sorting at",start);
    svlist.unique();
    std::cout<<"Size of list after unique: "<<svlist.size()<<std::endl;
    print_timestamp("Finished list unique at",start);
    svlist.repack();
    std::cout<<"Size of list after repack: "<<svlist.size()<<std::endl;
    print_timestamp("Finished list repack at",start);
    
    omp_destroy_lock(&lock);
    
    RandomElem rel(100000,svlist.get_elemsize(),1);
    DataTest *datatestptr = new DataTest(svlist);
//    DataTest datatest& = *datatestptr;
    
    print_timestamp("Finished RandomElem and DataTest init",start);
    t_point start1 = std::chrono::system_clock::now();
    int ntrue=0;
    for(auto pos=rel.begin();pos!=rel.end();++pos){
        if(svlist.check(*pos))ntrue++;
    }
    std::cout<<"ntrue= "<<ntrue<<std::endl;
    print_timestamp("Finished svlist.check",start1);

    t_point start2 = std::chrono::system_clock::now();
    ntrue=0;
    for(auto pos=rel.begin();pos!=rel.end();++pos){
        if(datatestptr->check(*pos))ntrue++;
    }
    std::cout<<"ntrue= "<<ntrue<<std::endl;
    print_timestamp("Finished datatest.check",start2);

//    delete datatestptr;

    return 0;
}

void print_timestamp(const char* str1,const t_point& start){
    t_point end=std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout<<str1<<' '<< std::ctime(&end_time);
    std::cout<< "elapsed time: " << elapsed_seconds.count() <<"s\n";
    }

