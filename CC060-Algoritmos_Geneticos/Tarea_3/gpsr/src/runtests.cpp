#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "global.h"
#include "gppopulation.h"
#include "gpoperators.h"
#include "usefulfunctions.h"
#include "rng.h"

using namespace std;

int main( int argc, char* argv[] ) {

	setupGlobals(argc, argv);
	loadFiles(training_file, testing_file);
	setupNodeLists();


	cout << "MAXDEPTH = " << MAXDEPTH << endl;
	cout << "genomeSize = " << genomeSize << endl;

	if (!seed_specified) {
		seed = time(0) ^ (getpid() << 16);
	}
	rng.reseed(seed);

	for (unsigned i=0; i<constants.size(); i++) {
		cout << "const[" << i << "]: " << constants[i] << endl;
	}

	printSettings();

	GPProgram *prog1;
	prog1 = new GPProgram(genomeSize, MAXDEPTH);
	cout << *prog1 << endl;

	prog1->calcFitness(true);
	cout << "Training score:\t" << prog1->getFitness() << endl;
	cout << "Testing score:\t" << prog1->getTestFitness() << endl;
	
	delete prog1;
	cleanup();

	return EXIT_SUCCESS;
}
