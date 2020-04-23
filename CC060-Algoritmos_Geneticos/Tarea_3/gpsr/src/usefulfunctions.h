#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H

int intRandom(const int &low, const int &high);
double protectedDivision(const double &a, const double &b);
ResultType protectedDivision(const ResultType &a, const ResultType &b);
double protectedLog(const double &a);
ResultType protectedLog(const ResultType &a);
void loadFiles(const std::string &training_file, const std::string& testing_file);

std::string doubleToString(const double &x);
std::string intToString(const int &x);
int min (const int &a, const int &b);
void clearStack();
void createResultType(double value, ResultType & res);
//void printStack();

GPNode* getRandomVariable();
GPNode* getRandomConstant();
GPNode* getRandomUnary();
GPNode* getRandomBinary();

void setupGlobals(int argc, char* argv[]);
void printHelp();
void printSettings();
void setupConstants();
void setupVariables();
void setupBinaries();
void setupUnaries();
void setupNodeLists();
void cleanup();
int countHits(const ResultType &targets, const ResultType &guesses, double criterion);
#endif
