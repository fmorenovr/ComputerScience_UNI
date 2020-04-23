#include <iostream>
#include "gppopulation.h"
#include "usefulfunctions.h"

using namespace std;

GPPopulation::GPPopulation(int size) {
	indexOfBest = 0;
	population.reserve(size);
	for (int i=0; i<size; i++) {
		population.push_back(new GPProgram());
	}
}

GPPopulation::GPPopulation(const GPPopulation &other) {
	population.reserve(other.getSize());
	indexOfBest = other.getIndexOfBest();
	for (int i=0; i<other.getSize(); i++) {
		population.push_back(new GPProgram(*(other.getIndividual(i))));
	}
}

GPPopulation::GPPopulation(int size, int indySize) {

	population.reserve(size);

	int numSubgroups = MAXDEPTH - 1;;
	int subgroupSize = size / numSubgroups;
	int remainder = size % numSubgroups;
	int depth = 2;

	for (int i = 0; i < numSubgroups; i++)  {
		for (int j = 0; j < subgroupSize; j++) {
			population.push_back(new GPProgram(indySize, depth));
		}
		depth++;
	}
	if (remainder != 0) {
		for (int k = 0; k < remainder; k++) {
			population.push_back(new GPProgram(indySize, intRandom(2, MAXDEPTH)));
		}
	}
}

GPPopulation::~GPPopulation() {
	vector<GPProgram*>::iterator it = population.begin();
	while(it!=population.end()) {
		delete *it;
		it++;
	}
	population.clear();
}

void GPPopulation::operator=(const GPPopulation &rhs) {

	// get rid of current pop
	for (unsigned i=0; i<population.size(); i++) {
		delete population[i];
	}
	// clear vector
	population.clear();

	indexOfBest = rhs.getIndexOfBest();
	for (int i=0; i<rhs.getSize(); i++) {
		population.push_back(new GPProgram(*(rhs.getIndividual(i))));
	}
}

int GPPopulation::getIndexOfBest() const {
	return indexOfBest;
}

vector<GPProgram*> GPPopulation::getPopulation() const {
	return population;
}

int GPPopulation::getSize() const {
	return population.size();
}

void GPPopulation::setIndexOfBest(int index) {
	indexOfBest = index;
}

void GPPopulation::setPopulation(const vector<GPProgram*> &pop) {
	population = pop;
}

GPProgram* GPPopulation::getIndividual(int index) const {
	// FIXME watch it, no check
	//GPProgram *ret = population[index];
	return population[index];
}

double GPPopulation::getIndividualFitness(int index) {
	// no check
	GPProgram* indy = population[index];
	return indy->getFitness();
}

void GPPopulation::setIndividual(int index, GPProgram* indy) {
	delete population[index];
	population[index] = new GPProgram(*indy);
}

GPProgram* GPPopulation::getBestIndividual() {

	GPProgram *ret; 
	double bestFitness = 1e19; //really damn big
	double currentFitness = 0;
	int bestIndex = 0;
	for (unsigned i=0; i<population.size(); i++) {
		ret = population[i];
		currentFitness = ret->getFitness(); 
		if (currentFitness <= bestFitness) {
			bestFitness = currentFitness;
			bestIndex = i;
		}
	}
	indexOfBest = bestIndex;
	//delete ret;
	return population[bestIndex];
}

void GPPopulation::updateBestIndividual() {

	GPProgram *ret; 
	double bestFitness = 1e19; //really damn big
	double currentFitness = 0;
	int bestIndex = 0;
	for (unsigned i=0; i<population.size(); i++) {
		ret = population[i];
		currentFitness = ret->getFitness(); 
		if (currentFitness <= bestFitness) {
			bestFitness = currentFitness;
			bestIndex = i;
		}
	}
	indexOfBest = bestIndex;
}

int GPPopulation::getIndexOfWorst() {

	int index = 0;
	//GPProgram* current = new GPProgram(*(population[0]));
	double worstFit = population[0]->getFitness();
	double currentFit = 0.0;
	for (unsigned i=1; i< population.size(); i++) {
		//current = population[i];
		//if (current->getFitness() > worstFit) {
		currentFit = population[i]->getFitness();
		if (currentFit > worstFit) {
			worstFit = currentFit;
			index = i;
		}
	}
	//delete current;
	return index;
}

void GPPopulation::calculatePopulationFitness() {

	GPProgram *gpr;

	for (unsigned i = 0; i < population.size(); i++) {
		gpr = population[i];
		gpr->calcFitness(true);
		//cout << "gpr is:\n" << *gpr << endl;
	}
	updateBestIndividual();
	//delete gpr;
}

ostream& operator<<(ostream& os, const GPPopulation &pop) {

	GPProgram *gpr;
	for (int i=0; i<pop.getSize(); i++) {
		gpr = pop.getIndividual(i);
		os << *gpr << "\n";
	}
	// dont delete it - we'll need it later.
	//delete gpr;	
	return os;
}
