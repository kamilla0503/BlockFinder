#include"blockfinder.h"

BlockFinder::BlockFinder( int bsamples, NCS bncs, int bmin_depth, bool bblock_finder_mode, int bmin_t_free, int bbegin, int bend ){	
	samples = bsamples;
	ncs = bncs;
	min_depth = bmin_depth;
	check_t_free = false; 
	block_finder_mode = bblock_finder_mode;
	scheme.setscheme("1", ncs, samples, {});
	depth = 0;  
	min_t_free = bmin_t_free;
	index_of_type_T = index_of_type(labeltype('T', 1, 1, 0));
	if (min_t_free >= 0) {
		check_t_free = true;
	} 
	if (min_depth <= 1) {
		min_depth = 2;
	} 
	patterns.push_back(generate_patterns(samples ));  
	counter.push_back(0); 
	results_found = 0; 
	max_depth = 0;
	iterator = 0;
	begin = bbegin;
	end = bend; 
	result_string = "[NCS = " + ncs.name + "]\n"+
	                "[Deuterated = " + (ncs.deuterated?"True":"False") + "]\n";
	
	out1 = "";
	start_time = clock();
}


vector <string> BlockFinder::generate_patterns(int  bsamples, bool top ) {
	vector <string> new_set;
	vector <string>  current_set;
	if (bsamples == 0) {
		new_set = { "" };
		return new_set;
	}
	
	current_set = generate_patterns(bsamples - 1, false);
	new_set = { };
	string new_pattern;
	for (string item : current_set) {
		for (labeltype option : ncs.label_types) {
			new_pattern = item + option.name;
			if (top==true ) {
				if (ncs.check_power(new_pattern, min_depth) ){
					new_set.push_back(new_pattern); 
				}
		}
			else {
				new_set.push_back(new_pattern);
			} 
		}
	}  
	return new_set;
}


int index_of_type(labeltype label_type) {
	labeltype typeX('X', 0, 0, 0);
	labeltype typeN('N', 1, 0, 0);
	labeltype typeC('C', 0, 0, 1);
	labeltype typeD('D', 1, 1, 1);
	labeltype typeA('A', 0, 1, 0);
	labeltype typeT('T', 1, 1, 0);
	labeltype typeS('S', 1, 0, 1);
	labeltype typeF('F', 0, 1, 1);
	static map<char, int>  basic_types = { {typeX.name, 0}, { typeN.name,1 } , {typeC.name, 2} , {typeD.name, 3} , {typeA.name, 4} , {typeT.name, 5} ,{ typeS.name, 6}, {typeF.name, 7} };
	return basic_types[label_type.name]; 
} 

void BlockFinder::start_blockfinder() {
	if (check_t_free) {
		cout << "started samples =" << samples << " min depth = " << min_depth << " min_t_free=" << min_t_free << endl; 
		out1 = "started samples =" + to_string(samples) + " min depth = " + to_string(min_depth) + " min_t_free=" + to_string(min_t_free);
	}
	else {
		out1 = "started samples =" + to_string(samples) + " min depth = " + to_string(min_depth);
		cout << "started samples =" << samples << " min depth = " << min_depth << endl;
	}
	cout << " total number of patterns is  " << patterns[0].size() << endl; 
}


void BlockFinder::recoverfromcounters( vector <int> currentcounters){

 vector<string> temp_patterns = patterns[0];
    for (int c=0; c<currentcounters.size()-1; c++){

        back_up_schemes.push_back(scheme);

        scheme.add_pattern(temp_patterns[currentcounters[c]]);

        temp_patterns = get_next_patterns(temp_patterns, temp_patterns.size()-currentcounters[c]-1, currentcounters[c]+1);

        patterns.push_back(temp_patterns);


    }

    depth = currentcounters.size()-1;
    counter=currentcounters;

}

// next pattern is a problem
void BlockFinder::maincycle1(vector <int> start, vector <int> end) {
	vector<string> patternscurrent, next_patterns;
	int start_point;
	int patterns_left; 
	bool flag_t_free;

	std::ofstream iterlog;
    iterlog.open("iterlog.txt");
    bool limits=true;
    bool check_limits=false;
    if (start.size()==0 && end.size()==0){
    	limits = false;
    	check_limits=false;
    }
    int order = 0;


	while (true) {

		order = 0 ;
//cout << "cycle started " << endl;

		if(limits && counter.size()==end.size()){
			for (int c=0; c< end.size(); c++ ){
				if (counter[c]<end[c]){
					//order =order+1;
					//check_limits=true;
					break;
				}
				order =order+1;
			}
/**
			if(counter[end.size()-1]>=end.back()){
				order=order+1;

			}**/

			if (order==end.size()){
				check_limits=true;

				cout << "end while "<< endl;
				for (int q: counter){
					cout << q << " ";
				}

				cout << endl;


			}

		}

		if(check_limits){
			break;
		}


        iterlog<<iterator<<" "<<depth<<" : ";
        for(int d=0;d<depth+1; d++)
            iterlog<<counter[d]<<" ";
        iterlog<<endl;


		next_iteration_output();
		//cout << "iterator " << iterator << endl;

		patternscurrent = patterns[depth];

	//	cout <<"patterns are got " << endl;

		//cout << "current is got " << endl;
		if (depth == 0 && ( (counter[0] + min_depth )> patternscurrent.size())  ) {
			break;
		}
		start_point = 1 + counter[depth];
		patterns_left = patternscurrent.size() - start_point;


		back_up_schemes.push_back(scheme);
		scheme.add_pattern(patternscurrent[counter[depth]]); //////
		if (patterns_left < (min_depth - depth - 1)   ) {
			go_back();
			continue;
		}
		if (patterns_left == 0) {
			if (scheme.patterns.size() >= min_depth) {


                save_result();
			}
			go_back();
			continue;
		}
		next_patterns = get_next_patterns(patternscurrent, patterns_left, start_point);
		flag_t_free = true;
		if (check_t_free) {
			flag_t_free = check_have_enought_t_free(scheme, next_patterns);
		}



		if ( next_patterns.size() != 0 && flag_t_free){
			
			go_deeper(next_patterns);
		}
		else {
			if (scheme.patterns.size() >= min_depth) {



				save_result();

			}
			go_parallel();	
		}
		check_max_depth();
	}



}



void BlockFinder::maincycle() {
	vector<string> patternscurrent, next_patterns;
	int start_point;
	int patterns_left;
	bool flag_t_free;


	std::ofstream out;          // поток для записи
	out.open("schemes.txt");

    std::ofstream iterlog;          // поток для записи
    iterlog.open("iterlogdepth.txt");



   // fstream f("file.dat",ios::binary|ios::in|ios::out);


	vector<int> counter_start ,counter_end;
	//int pool_depth_test=2, test_size_test=4;
	int task_counter=0;

	vector <Task4run> t;
	//Task4run task1({0}, {});
	Task4run task1;
	task1.counter_start={0};
	task1.counter_end={};
	tasks.push_back(task1);

    int kt=0;
    string temps;

	while (true) {
       // iterlog<<iterator<<" "<<depth<<" : ";
        for(int d=0;d<depth+1; d++)
            iterlog<<counter[d]<<" ";
        iterlog<<endl;



		next_iteration_output();

		patternscurrent = patterns[depth];
		if (depth == 0 && ( (counter[0] + min_depth )> patternscurrent.size())) {
			break;
		}
		start_point = 1 + counter[depth];
		patterns_left = patternscurrent.size() - start_point;
		back_up_schemes.push_back(scheme);
		scheme.add_pattern(patternscurrent[counter[depth]]);
		if (patterns_left < (min_depth - depth - 1)   ) {
			go_back();
			continue;
		}
		if (patterns_left == 0) {
			if (scheme.patterns.size() >= min_depth) {
				save_result();
                cout << " save " << endl;
                for (int c: counter){
                    cout << c<< " ";


                }

                cout << endl;


            }
			go_back();
			continue;
		}
		next_patterns = get_next_patterns(patternscurrent, patterns_left, start_point);
		flag_t_free = true;
		if (check_t_free) {
			flag_t_free = check_have_enought_t_free(scheme, next_patterns);
		}
		if ( next_patterns.size() != 0 && flag_t_free){
			if(depth == parallel_depth){


                //out << "back up " << endl;
			    /**

                out << back_up_schemes.size() << endl;
			    save_back_up(out);

			    //out << depth<< endl;

			    out << scheme.patterns.size() << endl;

			    for (int i=0; i<scheme.patterns.size(); i++){
			        out << scheme.patterns[i] << endl;


			    }



			    out << depth << endl;

			    for (int e=1; e<patterns.size(); e++){
			        out << patterns[e].size() << endl;
                    for (int q=0; q<patterns[e].size(); q++){
                        out << patterns[e][q]<< endl;


                    }



			    }


			    cout<< " break because of depth " << endl;

                for (int i=0; i<counter.size(); i++){
                    cout << counter[i] << " ";
                }

                cout << endl;**/





				task_counter=task_counter+1;
				//cout << "this depth " << endl;
				//kt=kt+counter[pool_depth_test];

				if (task_counter%task_size==0){

				    tasks.back().counter_end = counter;

				    //Task4run task1(counter, {});
				    task1.counter_start=counter;
				    task1.counter_end={};

				    tasks.push_back(task1);

				    //cout << " where is a problem " << t.back().counter_start.size() << endl;

				    //counter_start.push_back(counter[depth]);
                    //counter_end.push_back();


                    task_counter=0;
				}


				go_parallel();
			}
			if(depth<parallel_depth){

			    go_deeper(next_patterns);

			}
		}
		else {
			if (scheme.patterns.size() >= min_depth) {
			    cout << " save " << endl;
			    for (int c: counter){
			        cout << c<< " ";


			    }

			    cout << endl;


				save_result();
			}
			go_parallel();
		}
		check_max_depth();

		/**
        for (int i=0; i<counter.size(); i++){
            cout << counter[i] << " ";
        }

        cout << endl;**/




	}

	tasks.back().counter_end=counter;





 //   cout << " kt" << kt << endl;
	//cout << " go deeper " << task_counter  << endl;


//cout << " size of tasks" << t.size() << endl;
out.close();









//  return t;

}







/**

void BlockFinder::maincycle2(Task4run task) {
	vector<string> patternscurrent, next_patterns;
	int start_point;
	int patterns_left;
	bool flag_t_free;

	while (true) {
		next_iteration_output();

		patternscurrent = patterns[depth];
		if (depth == 0 && ( (counter[0] + min_depth )> patternscurrent.size())) {
			break;
		}
		start_point = 1 + counter[depth];
		patterns_left = patternscurrent.size() - start_point;
		back_up_schemes.push_back(scheme);
		scheme.add_pattern(patternscurrent[counter[depth]]);
		if (patterns_left < (min_depth - depth - 1)   ) {
			go_back();
			continue;
		}
		if (patterns_left == 0) {
			if (scheme.patterns.size() >= min_depth) {
				save_result();
			}
			go_back();
			continue;
		}
		next_patterns = get_next_patterns(patternscurrent, patterns_left, start_point);
		flag_t_free = true;
		if (check_t_free) {
			flag_t_free = check_have_enought_t_free(scheme, next_patterns);
		}
		if ( next_patterns.size() != 0 && flag_t_free){

			go_deeper(next_patterns);
		}
		else {
			if (scheme.patterns.size() >= min_depth) {
				save_result();
			}
			go_parallel();
		}
		check_max_depth();
	}
}
**/













void BlockFinder::next_iteration_output()
{
    iterator++;
    if (iterator % 10000 == 0) {
      ostringstream log;
      log<< "[BlockFinder" << to_string(samples) << "]";
      log<< setw(9) << iterator;
      time_t now = clock();
      double time_in_run = (double)(now - start_time) / CLOCKS_PER_SEC;
      log << setw(8) << setprecision(2) << fixed << time_in_run << " sec";
      log << " max_P=" << setw(2) << setiosflags(ios::left) << max_depth + 1;
      log << " ELB_found= " << setw(6) << results_found;
      for(int d=0; d< depth && d<10; d++){
	log << " " << setw(3) << setiosflags(ios::right) << counter[d] << "/";
	log        << setw(3) << setiosflags(ios::left) << patterns[d].size() - min_depth + 1 + d;
      }
      cout << log.str() << endl;
    }
}

void BlockFinder::go_parallel() {
    //cout << "go parallel"<< endl;
	scheme =back_up_schemes[depth];

	//cout << " back is ok " << endl;
	back_up_schemes.pop_back();
	counter[depth] = counter[depth] + 1;
}

void BlockFinder::check_max_depth() {
	if (depth > max_depth) {
		max_depth = depth;
		if (block_finder_mode) {
			out1 = "[BlockFinder" + to_string(samples) + " ] New max depth:" + to_string(max_depth); 
		}
	}

} 

vector <string> BlockFinder::get_next_patterns(vector <string> patterns, int patterns_left, int  start_point) {
	vector <string> next_patterns ;
	for (int i = 0; i < patterns_left; i++)  {
		if( scheme.try_pattern(patterns[i + start_point])) {
			next_patterns.push_back(patterns[i + start_point]);
		}
	}
	return next_patterns;
}

void BlockFinder::go_deeper(vector <string> next_patterns) {
	//cout << "depeer " << depth << endl;
	patterns.push_back(next_patterns);
	counter.push_back(0);
	depth = depth + 1;
    /**for (int i=0; i<counter.size(); i++){
        cout << " counter " << counter[i] ;
    }
	cout << endl;**/

}

//vector<Task4run> BlockFinder::create_tasks(int pool_depth, int task_size=1) {
void BlockFinder::create_tasks() {
	//start_blockfinder();

    //vector <Task4run> t;

	 maincycle();
cout << " all or not " << endl;
	//maincycle1();


    ofstream file1("tasksend.txt");
	//blockfinder_finished();

	for (Task4run c: tasks){

		for (int i: c.counter_start){
			file1 <<setw(2)<< i << " ";

		}
        file1<<" : ";
		for (int i: c.counter_end){
			file1 <<setw(2)<< i << " ";

		}

		file1 << endl;

	}



//	return t;

	// ?
	/**

	cout << " size of t  " << t.size() << endl;

	BlockFinder r(samples, ncs, min_depth, block_finder_mode, min_t_free);
	r.counter = t[0].counter_end;
	cout << r.ncs.name << " name of ncs " << endl;
	//r.back_up_schemes=back_up_schemes;

	r.find_schemes();


	cout << " ????? " << r.results_found << endl;


**/



}



void BlockFinder::find_schemes1() {
    start_blockfinder();
    maincycle1();

    //maincycle1();



    blockfinder_finished();


}





void BlockFinder:: blockfinder_finished() {
	out1 = "[BlockFinder] finished search in" + to_string(samples) + "samples after " + to_string(iterator) + " iterations " + to_string(results_found) + " ELB schemes found";
}

void BlockFinder::go_back() {
	depth = depth -1;
	patterns.pop_back();
	counter.pop_back();
	counter[counter.size() - 1] = counter[counter.size() - 1] + 1;


	back_up_schemes.pop_back();
	scheme = back_up_schemes[back_up_schemes.size() - 1];
	back_up_schemes.pop_back();

}

void BlockFinder::save_result() {
	if (check_t_free && !(check_have_enought_t_free(scheme, {}))) {
		return;
	}
	int depth_of_scheme;
	depth_of_scheme= scheme.patterns.size();
	Scheme new_scheme;
	new_scheme = scheme;
	new_scheme.sort();
	if(	result.find(depth_of_scheme) != result.end() ){
		if (result[depth_of_scheme].find(new_scheme) == result[depth_of_scheme].end()) {

			result[depth_of_scheme].insert(new_scheme);
			write_result(new_scheme);
		}
	}
	else {
		result[depth_of_scheme] = { new_scheme };
		write_result(new_scheme);
	}
}



void BlockFinder::save_back_up(std::ostream& out) {


	if (back_up_schemes.size()!=0){
		for (Scheme c : back_up_schemes){
			out << c.patterns.size()<< endl;
			for(int i=0; i<c.patterns.size(); i++){
			    out << c.patterns[i] << endl;
			}


		}


	}




}





bool BlockFinder::check_have_enought_t_free(Scheme scheme, vector<string>  patterns_left) {
	tuple <int, int> t;
	t = count_type_in_list_of_simplified(scheme.simplified, index_of_type_T); 
	int scheme_t = get<0>(t); 
	int scheme_t_free = get<1>(t); 
	tuple <int, int> t2; 
	t2 = count_type_in_list_of_patterns(patterns_left, labeltype('T', 1, 1, 0));
	int left_t = get<0>(t2);
	int left_t_free = get<1>(t2);
	return (scheme_t_free + left_t_free >= min_t_free); 
}

map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns) {
	map <string, int> simplified;
	string simple_pattern;
	for (string pattern : list_of_patterns) {
		simple_pattern = simplify_pattern(pattern);
		if(  simplified.size() != 0 &&   simplified.count(simple_pattern)!=0  ){
			simplified[simple_pattern] = simplified[simple_pattern] + 1;
	}
		else {
			simplified[simple_pattern] = 1;
		} 
	}
	return simplified;
}

tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type) {
	int count_type = 0;
	int count_all = 0;
	int has_t;
	for(  auto sp : simplified) {
		has_t = 0;
			if (int(sp.first[index_of_type])) {
				has_t = 1;
			}
			count_type = count_type + has_t * sp.second;
			count_all = count_all  + sp.second;
	}
	return  make_tuple(count_type, count_all - count_type);
}

tuple<int, int > count_type_in_list_of_patterns(vector<string> patterns, labeltype label_type) {
	map <string, int>  simplified = simplify_list_of_patterns(patterns);
	int index_of_t = index_of_type(label_type);
	return count_type_in_list_of_simplified(simplified, index_of_t);
}

void  BlockFinder::write_result(Scheme  new_scheme) {
	results_found = results_found + 1;
        result_string += "# iterator = " + to_string(iterator) + "\n";
	result_string += new_scheme.full_str();
}
