#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "global.h"
#include "rng.h"

using namespace std;

double protectedDivision(const double &a, const double &b) {
	if (b == 0.0) {
		return 0.0;
	}
	else {
		return a / b;
	}
}

ResultType protectedDivision(const ResultType &a, const ResultType &b) {
	ResultType ret(a.size());

	for (int i=0; i<ret.size(); i++) {
		if (b[i] == 0.0) {
			ret[i] = 0.0;
		}
		else {
			ret[i] = a[i] / b[i];
		}
	}
	return ret;
}

int countHits(const ResultType &targets, const ResultType &guesses, double criterion) {
	int ret=0;

	double err = 0.0;
	for (int i=0; i<targets.size(); i++) {
	//cout<<"i: "<<i<<"targets: "<<targets[i]<<", guesses: "<<guesses[i]<<endl;
		err = abs(targets[i] - guesses[i]);

		if (err <= criterion)
			ret++;

	}
	return ret;
}

double protectedLog(const double &a) {
	if (a <= 0 ) {
		return 0.0;
	}
	else {
		return log(a);
	}
}

ResultType protectedLog(const ResultType &a) {
	ResultType ret(a.size());
	for (int i=0; i<ret.size(); i++) {
		if (a[i] <= 0.0) {
			ret[i] = 0.0;
		}
		else {
			ret[i] = log(a[i]);
		}
	}
	return ret;
}

int intRandom(const int &low, const int &high) {
	int nb = high - low + 1;
	return (int)(rng.uniform()*nb + low);
}

double dblRandom(const double &low, const double &high) {
	double nb = high - low + 1;
	return (rng.uniform()*nb + low);
}

void clearStack() {
	valueStack.clear();
	valueStack.resize(0);
}

void createResultType(double value, ResultType &res) {
	for (int i=0; i<res.size(); i++) {
		res[i] = value;
	}
}

/*
void printStack() {
	for (unsigned i=0; i<valueStack.size(); i++) {
		cout << valueStack[i] << " ";
	}
	cout << endl;
}
*/

std::string doubleToString(const double &x)
{
	std::ostringstream o;
	if (o << x)
		return o.str();
	// some sort of error handling goes here...
	return "conversion error";
} 

std::string intToString(const int &x)
{
	std::ostringstream o;
	if (o << x)
		return o.str();
	// some sort of error handling goes here...
	return "conversion error";
}

int min (const int &a, const int &b) {
	if (a <= b) 
		return a;
	else
		return b;
}

void loadFiles(const std::string &training_file, const std::string& testing_file) {

	if (training_file == "" || testing_file == "")
	{
		cerr<<"You must supply a training and testing file\n";
		exit(1);
	}
	else
	{ 	
		// load data

		ifstream data(training_file.c_str());
		if (!data) {
			cerr << "Could not open training datafile " << training_file << endl;
			exit(1);
		}
		string line;
		getline(data, line); // read first (header) line

		if (line[0] != '#') { 
			cerr << "Training datafile needs a header line" << endl;
		}
		istringstream is(line);
		is.get(); // skip #
		int ncases;
		int nvars;
		is >> ncases;
		is >> nvars;
		--nvars; // last one is target
		
		// reset global numVariables
		numVariables = nvars;

		//cout << "Loading training data, ncases = " << ncases << ", nvars = " << nvars << endl;

		variables.resize(nvars);
		targets.resize(ncases);
		for (int i = 0; i < nvars; ++i) {
			variables[i].resize(ncases);
		}

		for (int i = 0; i < ncases; ++i) {
			for (int j = 0; j < nvars; ++j) {
				data >> variables[j][i];
			}

			data >> targets[i];

			if (!data) {
				cerr << "Something went wrong reading in the training data" << endl;
				cerr << "at line " << i+1 << endl;
				exit(1);
			}
		}

		ifstream test_data(testing_file.c_str());
		if (!test_data) {
			cerr << "Could not open testing datafile " << testing_file << endl;
			exit(1);
		}
		getline(test_data, line); //nb: reuse of line
		if (line[0] != '#') { 
			cerr << "Testing datafile needs a header line" << endl;
		}
		istringstream is2(line);
		is2.get(); // reuse of is again (might need a new one)
		is2 >> ncases;
		is2 >> nvars;
		--nvars;

		//cout << "Loading testing data, ncases = " << ncases << ", nvars = " << nvars << endl;
		test_variables.resize(nvars);
		test_targets.resize(ncases);
		for (int i = 0; i < nvars; ++i) {
			test_variables[i].resize(ncases);
		}
		for (int i=0; i<ncases; i++) {
			for (int j=0; j<nvars; j++) {
				test_data >> test_variables[j][i];
			}
			test_data >> test_targets[i];

			if (!test_data) {
				cerr << "Something went wrong reading in the testing data" << endl;
				cerr << "at line " << i+1 << endl;
			}
		}
		data.close();
		test_data.close();
	}
}


GPNode* getRandomVariable() {
	int rndnum = intRandom(0, t_variables.size()-1);
	GPNode *ret = &(t_variables[rndnum]);
	return ret;
}

GPNode* getRandomConstant() {
	int rndnum = intRandom(0, t_constants.size()-1);
	GPNode *ret = &(t_constants[rndnum]);
	return ret;
}

GPNode* getRandomBinary() {
	int rndnum = intRandom(0, t_binaries.size()-1);
	GPNode *ret = &(t_binaries[rndnum]);
	return ret;
}

GPNode* getRandomUnary() {
	int rndnum = intRandom(0, t_unaries.size()-1);
	GPNode *ret = &(t_unaries[rndnum]);
	return ret;
}

void printHelp(char* arg)
{
    cout << "Usage: " << arg << " <options>" << endl << endl;

    cout << "-g num   \t number of generations to run (default = 100) " << endl;
    cout << "-p num   \t population size (default = 500) " << endl;
    cout << "-t num   \t tournament size (default = 3)" << endl;
    cout << "-h       \t help (print this message) " << endl;
    cout << endl;
    //cout << "-u string\t unaries to use (default = 'vlsc2')" << endl;
    cout << "-u string\t unaries to use (default = 'lsc2')" << endl;
    //cout << "	      \t v : sqrt(x)\n";
    cout << "	      \t l : ln(x)\n";
    cout << "	      \t s : sin(x)\n";
    cout << "	      \t c : cos(x)\n";
    cout << "	      \t 2 : x*x\n";
    cout << "\nBinaries are: x + y, x - y, x * y and x / y\n";
    cout << endl;
    cout << "-l	      \t switches on linear scaling (off by default)\n";
    cout << "-D num   \t random seed (default = time(0) ^ (getpid() << 16))\n";
    cout << "-o num   \t outputfile for best indy (default = best)\n";
    cout << "-d num   \t training data (default = train.dat)\n";
    cout << "-f num   \t testing data (default = test.dat)\n";
    cout << "-s num   \t maximum size genome (default = 256)\n";
    cout << "-r num   \t constant range (default = 10.0)\n";  
    cout << "-j num   \t number of constants (default = 20, minimum = 1)\n";
    cout << "-O file  \t results file (default: res)\n";
    cout << "-c num   \t hits criterion (default: 0.01)\n";
    cout << endl;
}

void setupGlobals(int argc, char* argv[]) {
    string optionstring = "g:p:t:hu:lD:o:d:f:s:r:j:LO:c:";
    
    if (argc == 1) {
	    printHelp(argv[0]);
	    exit(1);
    }
    
    while(1)
    {
	int c = getopt(argc,argv,optionstring.c_str());
	//int c;

	if (c == -1)
	    break;

	switch(char(c))
	{
	    case 'g': numgens = atoi(optarg); break;
	    case 'p': popsize = atoi(optarg);break;
	    case 't': tournamentSize = atoi(optarg); break;
	    case 'u': unaries = optarg; break;
	    case 'D': seed = atoi(optarg); seed_specified = true; break;
	    case 'l': linear_scaling = true; break;
	    case 'o': best_file = optarg; break;
	    case 'd': training_file = optarg; break;
	    case 'f': testing_file = optarg; break;
	    case 's': genomeSize = atoi(optarg); break;
	    case 'r': constRange = atof(optarg); break;
	    case 'j': numConstants = atoi(optarg); break;
	    case 'L': loose_metric = true; break;
	    case 'O': logfile = optarg; break;
	    case 'c': hitsCriterion = (double) atof(optarg); break;
	    case 'h': printHelp(argv[0]); exit(1);
	   
	    default:
		printHelp(argv[0]);
		exit(1);
	}
    }
}

void setupConstants() {
	//GPNode *c;
	for (int i=0; i<numConstants; i++) {
		constants.push_back(dblRandom(-constRange, constRange));
		//c = new GPNode(i, "constant", -1);
		//t_constants.push_back(*c);
		t_constants.push_back(GPNode(i, "constant", -1));
	}
}

void setupVariables() {
	//GPNode *vb;
	for (int i=0; i<numVariables; i++) {
		//vb = new GPNode(i, "VAR", -1);
		//t_variables.push_back(*vb);
		t_variables.push_back(GPNode(i, "VAR", -1));
	}
}

void setupBinaries() {
	//GPNode *binary1 = new GPNode(0, "ADD", 1);
	//t_binaries.push_back(*binary1);
	
	t_binaries.push_back(GPNode(0, "ADD", 1));
	t_binaries.push_back(GPNode(1, "MIN", 1));
	t_binaries.push_back(GPNode(2, "MUL", 1));
	t_binaries.push_back(GPNode(3, "DIV", 1));

	//GPNode *binary2 = new GPNode(1, "MIN", 1);
	//t_binaries.push_back(*binary2);
	//GPNode *binary3 = new GPNode(2, "MUL", 1);
	//t_binaries.push_back(*binary3);
	//GPNode *binary4 = new GPNode(3, "DIV", 1);
	//t_binaries.push_back(*binary4);
}

void setupUnaries() {
	//GPNode *u;
	for (unsigned i = 0; i < unaries.size(); ++i) {
		switch (unaries[i]) {
			//case 'v': t_unaries.push_back(GPNode(i, "SQRT", 0)); break;
			case 'l': t_unaries.push_back(GPNode(i, "log", 0)); break;
			case 's': t_unaries.push_back(GPNode(i, "sin", 0)); break;
			case 'c': t_unaries.push_back(GPNode(i, "cos", 0)); break;
			case '2': t_unaries.push_back(GPNode(i, "sqrt", 0)); break;
			default: std::cerr << "Problem processing unaries\n"; printHelp("prog"); exit(1); 
		}
	}
}

void setupNodeLists() {
	setupConstants();
	setupVariables();
	setupBinaries();
	setupUnaries();
}

void cleanup() {
	t_unaries.clear();
	t_binaries.clear();
	t_variables.clear();
	t_constants.clear();
}

void printSettings() {
	cout << "Run settings:\n";
	cout << "------------------------------------------" << endl;
	cout << "population size:       " << popsize << endl;
	cout << "genome size:           " << genomeSize << endl;
	cout << "number of generations: " << numgens << endl;
	cout << "crossover rate:        " << crossover_prob << endl;
	cout << "mutation rate:         " << mutation_prob << endl;
	cout << "tournament size:       " << tournamentSize << endl;
	cout << "number of constants:   " << numConstants << endl;
	cout << "number of variables:   " << numVariables << endl;
	cout << "constant range:        " << constRange << endl;
	cout << "random seed:           " << seed << endl;
	cout << "hits criterion:        " << hitsCriterion << endl;
	cout << "------------------------------------------" << endl;
}
