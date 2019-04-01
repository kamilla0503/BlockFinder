#include"ncs.h"
#include<string>
#include<vector>
#include<map>
#include<time.h> 
#include<iomanip>
#include<iostream>
#include"blockfinder.h"
//
using namespace std; 
/**
int main(int argc, char **argv)
{
	vector<spectrum> nc2_spectra;
	vector<labeltype> nc2_labeltype;
	string nc2_name("NC2");

	nc2_spectra.push_back(spectrum("HSQC"));
	nc2_spectra.push_back(spectrum("HNCO"));
	//nc2_spectra.push_back(spectrum("HNCA"));
	//nc2_spectra.push_back(spectrum("HNCOCA"));
	//nc2_spectra.push_back(spectrum("DQHNCA"));
	//nc2_spectra.push_back(spectrum("COfHNCA"));
	//nc2_spectra.push_back(spectrum("HNCACO"));
	//nc2_spectra.push_back(spectrum("HNCAfCO"));


	cout << "START " << endl; 
	NCS test_nc2;
	test_nc2 = get_NCS("NC2");


	nc2_labeltype.push_back(labeltype('X', 0, 0, 0));
	nc2_labeltype.push_back(labeltype('N', 1,0,0));
	nc2_labeltype.push_back(labeltype('C',0, 0, 1));

	//NCS test_nc2(nc2_name, nc2_spectra, nc2_labeltype);
	NCS newtest = test_nc2;
	cout << " Size of label_types: " << newtest.label_types.size() << endl;
	cout << " Size of spec_list: " << newtest.spec_list.size() << endl;
	cout << " codes_dict: " << endl;
	cout << "  ";
	//cout << " see " << endl; 
	//cout << test_nc2.codes_dict[nc2_labeltype[0]][nc2_labeltype[0]] << " ";
	cout << " see " << endl;
	cout << newtest.codes_dict[nc2_labeltype[0]][nc2_labeltype[0]] << " ";

	//map < NCS, int > s;
	//s[test_nc2] = 3;
	//cout << " * " << s[test_nc2] << endl; 


	for (labeltype type_1 : test_nc2.label_types)
		cout << setw(1) << type_1.name << " ";
	cout << endl;
	for (labeltype type_1 : test_nc2.label_types) {
		cout << setw(1) << type_1.name << " ";
		for (labeltype type_2 : test_nc2.label_types) {
			cout << test_nc2.codes_dict[type_1][type_2] << " ";
		};
		cout << endl;
	}
	cout << " vectors: " << endl;
	cout << setw(7) << "Code ";
	for (spectrum s : test_nc2.spec_list) {
		//cout << setw(7) << s.name << " ";
		cout << s.name << " ";
	}
	cout << endl;

	for (int code = 0; code < test_nc2.vectors.size(); code++) {
		//cout << setw(7) << code << " ";
		cout << code << " ";
		vector <int> v = newtest.vectors[code];
		for (int peak : v) {
			cout << setw(10) << peak << " ";
		}
		cout << endl;
	}

	cout << " label_dict " << endl; 

	for (auto  code : test_nc2.label_dict) {
		cout << code.first << " " << code.second.name << endl;


	}



	getchar();

	string s1 = "NNNCCCXXX";
	string s2 = "NCXNCXNCX";
	string code = test_nc2.calc_code(s1, s2);
	cout << "s1=  " << s1<<endl;
	cout << "s2=  " << s2 << endl;
	cout << "code=" << code << endl;


	string r1 = simplify_pattern(s1);

	string r2 = simplify_pattern(s2);
	cout << "Sp " << r1 << endl; 
	cout << "Sp " <<  r2 << endl;

	Scheme scheme("1", test_nc2, 2, {});
	Scheme scheme2 = scheme;
	set <Scheme> s;
	s.insert(scheme); 
	//s.insert(scheme2);


	getchar();
	int samp =4; 
	int minp =4;
	BlockFinder b(samp, test_nc2, minp, true, -1);
	cout << " test creating bf and s " << b.scheme.samples << endl;
	cout << "!!!" << endl; 
	//cout << b.patterns[0][0] << endl;

	for (int i = 0; i < b.patterns.size(); i++) {
		for (int j = 0; j < b.patterns[i].size(); j++) {
			cout << b.patterns[i][j] << " "; 

		}
		cout << endl;

	}


	getchar();

	fstream blocks_file;
	string block_filename = "NC2_" + to_string(samp) + "_" + to_string(minp) + "_cpp.elb";
	blocks_file.open(block_filename, fstream::out);
	clock_t start = clock();

	b.find_schemes(); 

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << b.results_found << " found " << endl; 
	cout << b.result.size() << " size of results" << endl;
	cout << b.out1 << endl;
	blocks_file << b.result_string;
        blocks_file.close();
	cout << "Blocks found (" << b.results_found << ") are written to file " << block_filename << endl;
	printf("The time: %f seconds\n", seconds); 

	getchar();
	return 0;
}

**/