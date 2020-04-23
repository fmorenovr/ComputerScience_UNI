#include "global.h"
#include "gpnode.h"
#include "rng.h"

std::vector<ResultType> valueStack;

std::vector<ResultType> variables;
ResultType targets;
std::vector<double> constants;

std::vector<ResultType> test_variables;
ResultType test_targets;

std::vector<GPNode> t_unaries;
std::vector<GPNode> t_binaries;
std::vector<GPNode> t_variables;
std::vector<GPNode> t_constants;

// default settings that can be set via command line args
int tournamentSize = 3;
double crossover_prob = 0.7;
double mutation_prob = 0.02;
int genomeSize = 256;
int popsize = 500;
int numgens = 100;
int numConstants = 20;
int numVariables = 1;
double constRange = 10.0;
bool linear_scaling = false;
bool loose_metric = false;
bool seed_specified = false;
double hitsCriterion = 0.01;

std::string unaries = "lsc2";
std::string best_file = "best";
std::string logfile = "res";
std::string training_file = "train.dat";
std::string testing_file = "test.dat";

RNG rng(1);
ulong seed;
