//#pragma once
#include"scheme.h"
#include "task.h"


class BlockFinder {
public:
	

	vector<labeltype> types;
	int samples;
	NCS ncs;
	int min_depth;
	Scheme scheme;
	int begin, end; 
	//Scheme scheme("1", ncs, samples, {});

	//vector <string> patterns; //temporary 
	//new?
	vector <vector <string>> patterns;
	int depth;
	int max_depth;
	bool check_t_free;
	string result_string;
	int  min_t_free = -1;
	vector <int> counter = {}; //temporary
	vector <Scheme> back_up_schemes = {};
	bool  block_finder_mode;
	int results_found;
	map <int, set< Scheme>> result;//soe
	int iterator;
	int index_of_type_T;
	int task_size=95;

	int parallel_depth = 2;
	vector <Task4run> tasks;

	string out1;
	time_t start_time;
	//BlockFinder( NCS bncs, int bmin_depth, bool bblock_finder_mode, int  bmin_t_free = -1);
	vector <string> generate_patterns(int  samples, bool top = true);
	void start_blockfinder();
    void maincycle();
    //void BlockFinder::maincycle2(Task4run task);

    void find_schemes1();

    void maincycle1(vector <int> start={}, vector <int> end={});
    void recoverfromcounters( vector <int> currentcounters);

	void next_iteration_output();
	void go_back();
	void save_result();

	void save_back_up(std::ostream& out);
	bool check_have_enought_t_free(Scheme scheme, vector<string>  patterns_left);
	void  write_result(Scheme  new_scheme);
	vector <string> get_next_patterns(vector <string> patterns, int patterns_left, int  start_point);
	void go_deeper(vector <string> next_patterns);
	void go_parallel();
	void check_max_depth();
	void create_tasks();
	void blockfinder_finished();
	BlockFinder(int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free, int begin = -1, int  end = -1);

};

