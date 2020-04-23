#include <cmath>
#include <iostream>

#include "gpprogram.h"
#include "gpoperators.h"
#include "rng.h"
#include "usefulfunctions.h"

using namespace std;

GPProgram::GPProgram() {
	size = 0;
	fitness = 0.0;
	lsCoeffA = 0.0;
	lsCoeffB = 1.0;
	genome = vector<GPNode*>(0);
}

GPProgram::GPProgram(const GPProgram &other) {
	//cout << "entered GPProgram copy ctor\n";
	this->size = other.getSize();
	this->fitness = other.getFitness();
	this->lsCoeffA = other.getLSCoeffA();
	this->lsCoeffB = other.getLSCoeffB();

	for (int i=0; i<other.getSize(); i++) {
		//genome.push_back(new GPNode(*(other.getNode(i))));
		genome.push_back(other.getNode(i));
	}
	//cout << "leaving GPProgram copy ctor\n";
}

GPProgram::GPProgram(int size, int maxDepth) {
	this->size = size;
	this->lsCoeffA = 0.0;
	this->lsCoeffB = 1.0;
	// reserve memory for the genome
	this->genome.reserve(size);
	initialise(size, maxDepth);
}

GPProgram::~GPProgram() {
	//cout << "entered ~GPProgram()\n";

	//vector<GPNode*>::iterator it=genome.begin();
	//while(it!=genome.end()){
	//	delete *it;
	//	it++;
	//}
	//for (unsigned ii=0; ii<genome.size(); ii++) {
	//	delete genome[ii];
	//}
	
	this->genome.clear();
	//cout << "leaving ~GPProgram()\n";
}

void GPProgram::operator=(const GPProgram &rhs) {
	this->size = rhs.getSize();
	this->fitness = rhs.getFitness();
	this->lsCoeffA = rhs.getLSCoeffA();
	this->lsCoeffB = rhs.getLSCoeffB();
	this->genome = rhs.getGenome();
}


int GPProgram::getSize() const {
	//this->size = genome.size();
	return this->size;
}

double GPProgram::getFitness() const {
	return this->fitness;
}

double GPProgram::getTestFitness() {
	// evaluate with training flag set to false
	return calcFitness(false);
}

double GPProgram::getLSCoeffA() const {
	return this->lsCoeffA;
}

double GPProgram::getLSCoeffB() const {
	return this->lsCoeffB;
}

vector<GPNode*> GPProgram::getGenome() const {
	return this->genome;
}

std::string GPProgram::getType(int i) const {
	return genome[i]->getType();
}

void GPProgram::setSize(int s) {
	this->size = s;
}

void GPProgram::setFitness(double fit) {
	this->fitness = fit;
}

void GPProgram::setLSCoeffA(double a) {
	this->lsCoeffA = a;
}

void GPProgram::setLSCoeffB(double b) {
	this->lsCoeffB = b;
}


void GPProgram::setGenome(const vector<GPNode*> &genome) {
	this->genome = genome;
}

void GPProgram::addNode(GPNode *gpnode) {
	this->genome.push_back(gpnode);
}

void GPProgram::removeNode(int index) {
	//cout << "entered removeNode(), index = " << index << "\n";
	vector<GPNode*>::iterator pos = this->genome.begin();
	pos += index;
	//delete genome[index];
	this->genome.erase(pos);
	//cout << "leaving removeNode()\n";
}

void GPProgram::setNode(unsigned index, GPNode* gpnode) {
	if (index < this->genome.size() ) {
		this->genome[index] = gpnode;
	}
	else {
		cerr<<"Index out of bounds in GPProgram::setNode\n";
		// FIXME exit?
	}
}

void GPProgram::insertNode(int index, GPNode *gpnode) {
	genome.reserve(genome.size() + 1);
	//cout << "entered insertNode(), index = " << index << "\n";
	vector<GPNode*>::iterator pos;
	// FIXME make sure we have the correct position here
	pos = this->genome.begin() + index;
	//this->genome.insert(pos, new GPNode(*gpnode));
	this->genome.insert(pos, gpnode);
	//cout << "leaving insertNode()\n";
}


void GPProgram::insertSubtree(int index, const vector<GPNode*> &subtree) {
	genome.reserve(genome.size() + subtree.size());
	//cout << "entered insertSubtree(), index = " << index << " size = " << subtree.size() << "\n";
	vector<GPNode*>::iterator pos = this->genome.begin() + index;
	for (unsigned i=0; i<subtree.size(); i++) {
		//cout << "inserting " << subtree[i]->getType() << " at position " << i << endl;
		//this->genome.insert(pos, new GPNode(*(subtree[i])));
		this->genome.insert(pos, (subtree[i]));
		pos++;
	}
	//cout << "leaving insertSubtree()\n";
}

void GPProgram::removeSubtree(int start, int end) {

	//cout << "entered removeSubtree(), start == " << start << " end == " << end << "\n";
	//cout << "removing nodes from " << start << " to " << end << "\n";
	vector<GPNode*>::iterator first = this->genome.begin() + start;
	vector<GPNode*>::iterator last = this->genome.begin() + end + 1;

	//for (int i=start; i<end; i++) {
	//	delete genome[i];
	//}

	this->genome.erase(first, last);
	//cout << "leaving removeSubtree()\n";
}

vector<GPNode*> GPProgram::getSubtree(int start, int end) const {
	//cout << "entered getSubtree(), start == " << start << " end == " << end << endl;
	vector<GPNode*> ret;
	for (int i=start; i<end; i++) {
		//ret.push_back(new GPNode(*(this->genome[i])));
		ret.push_back(this->genome[i]);
	}
	//cout << "leaving getSubtree()\n";
	return ret;
}

GPNode* GPProgram::getNode(int index) const {
	// FIXME watch it, no check!
	return this->genome[index];
}

void GPProgram::resetSize() {
	this->size = this->genome.size();
}


vector<int> GPProgram::getDepths() const {

	vector<int> depths;
	depths.reserve(genome.size());
	int depth = -1;
	for (unsigned i = 0; i < genome.size(); i++) {
		depth += genome[i]->getArity();
		depths.push_back(depth);
	}
	return depths;
}

void GPProgram::initialise(int size, int maxDepth) {

	genome.reserve(size);
	GPNode *current;
	int rndnum = 0;

	// start with a terminal
	if (rng.flip(0.5)) {
		// random variable
		rndnum = intRandom(0, t_variables.size()-1);
		//current = t_variables[rndnum];
		//genome.push_back(new GPNode(current));
		genome.push_back(&(t_variables[rndnum]));
		
	}
	else {
		// random constant
		rndnum = intRandom(0, t_constants.size()-1);
		//current = t_constants[rndnum];
		//genome.push_back(new GPNode(current));
		genome.push_back(&(t_constants[rndnum]));
	}

	int depth = -1;
	int maxdepth = -1;
	int lastValidLocation = 0;

	int currentArity = 0;


	for (int i = 1; i < size; i++) {

		if (depth < -1) {
			int sw = rng.random(3);
			switch( sw ) {
				case 2: 
					// random terminal
					if (rng.flip(0.5)) {
						// random constant
						rndnum = intRandom(0, t_constants.size()-1);
						current = &(t_constants[rndnum]);
						currentArity = current->getArity();
						genome.push_back(&(t_constants[rndnum]));
					}
					else {
						// random variable
						rndnum = intRandom(0, t_variables.size()-1);
						current = &(t_variables[rndnum]);
						currentArity = current->getArity();
						genome.push_back(&(t_variables[rndnum]));

					} 
					break;
				case 1: 
					// random unary
					rndnum = intRandom(0, t_unaries.size()-1);
					current = &(t_unaries[rndnum]);
					currentArity = current->getArity();
					genome.push_back(&(t_unaries[rndnum]));
					break;
					
				case 0: 
					// random binary
					rndnum = intRandom(0, t_binaries.size()-1);
					current = &(t_binaries[rndnum]);
					currentArity = current->getArity();
					genome.push_back(&(t_binaries[rndnum]));
			}
		}
		else if (depth == -1) {
			switch (rng.random(2)) {
				case 1:
					// random terminal 
					if (rng.flip(0.5)) {
						rndnum = intRandom(0, t_constants.size()-1);
						current = &(t_constants[rndnum]);
						currentArity = current->getArity();
						genome.push_back(&(t_constants[rndnum]));
					}
					else {
						rndnum = intRandom(0, t_variables.size()-1);
						current = &(t_variables[rndnum]);
						currentArity = current->getArity();
						genome.push_back(&(t_variables[rndnum]));
					}
					break;
				case 0: 
					// random unary
					rndnum = intRandom(0, t_unaries.size()-1);
					current = &(t_unaries[rndnum]);
					currentArity = current->getArity();
					genome.push_back(&(t_unaries[rndnum]));
					break;
			
			}
		}

		depth += currentArity;
		
		maxdepth = min(depth, maxdepth);

		if (maxdepth <= -maxDepth) {
			break;
		}

		if (depth == -1) {
			lastValidLocation = i;
		}
	}
	this->size = lastValidLocation + 1;
	this->genome.resize(this->size);

}



ResultType GPProgram::evaluate(bool training) {

	clearStack();	

	GPNode *current;
	string type;

	int arraysize = (training) ? targets.size() : test_targets.size();

	ResultType ret(arraysize);
	ResultType doubleData(arraysize);
	ResultType op1(arraysize);
	ResultType op2(arraysize);

	double constData = 0;

	for (unsigned i = 0; i < this->genome.size(); i++) {

		current = this->genome[i];
		type = current->getType();

		if (type == "constant") {
			constData = constants[current->getData()];
			createResultType(constData, doubleData); 
			valueStack.push_back(doubleData);
		}
		else if (type == "ADD") {
			op1 = valueStack.back();
			valueStack.pop_back();

			op2 = valueStack.back();
			valueStack.pop_back();

			op2+=op1;

			valueStack.push_back(op2);
		}
		else if (type == "MIN") {
			op1 = valueStack.back();
			valueStack.pop_back();

			op2 = valueStack.back();
			valueStack.pop_back();

			op2 -= op1;

			valueStack.push_back(op2);
		}
		else if (type == "MUL") {
			op1 = valueStack.back();
			valueStack.pop_back();

			op2 = valueStack.back();
			valueStack.pop_back();

			op2 *= op1;

			valueStack.push_back(op2);
		}
		else if (type == "DIV") {
			op1 = valueStack.back();
			valueStack.pop_back();

			op2 = valueStack.back();
			valueStack.pop_back();

			valueStack.push_back(protectedDivision(op2, op1));
		}
		else if (type == "sqrt") {
			op1 = valueStack.back();
			valueStack.pop_back();
			op1*=op1;

			valueStack.push_back(op1);
		}
		else if (type == "cos") {
			op1 = valueStack.back();
			valueStack.pop_back();

			valueStack.push_back(cos(op1));
		}
		else if (type == "sin") {
			op1 = valueStack.back();
			valueStack.pop_back();

			valueStack.push_back(sin(op1));
		}
		else if (type == "log") {
			op1 = valueStack.back();
			valueStack.pop_back();

			valueStack.push_back(protectedLog(op1));
		}
		else if (type == "VAR") {
			op1=variables[current->getData()];
			valueStack.push_back(op1);
		}
		//else if (type == "SQRT") {
		//	op1 = valueStack.back();
		//	valueStack.pop_back();
		//	valueStack.push_back(sqrt(op1));
		//}
	}
	// result is last value on the stack
	ret = valueStack.back();
	valueStack.pop_back();
	// FIXME maybe check that the stack is now empty
	//delete current;
	return ret;
}


double GPProgram::calcFitness(bool training) {

	int arraysize = (training) ? targets.size() : test_targets.size();

	ResultType res(arraysize);

	if (linear_scaling) {

		if (training) {
			// only do this during training to calculate the coefficients
			linearScaling(evaluate(true), targets);
		}

		ResultType lsA(arraysize);
		createResultType(lsCoeffA, lsA);
		ResultType lsB(arraysize);
		createResultType(lsCoeffB, lsB);
		lsB *= evaluate(training);
		lsA += lsB;
		res = (training) ? lsA - targets : lsA - test_targets;
		res *= res;

	}
	else {
		res = (training) ? evaluate(true) - targets : evaluate(false) - test_targets;
		res *= res;
	}

	// only update fitness during training
	if (training) {
		this->fitness =  res.sum() / (double) res.size();
	}

	return res.sum() / (double) res.size();
}


void GPProgram::linearScaling(const ResultType &evolved, const ResultType &target) {

	int count = evolved.size();
	double meanTarget = 0.0;
	double meanEvolved = 0.0;
	for (int i=0; i<count; i++) {
		meanTarget += target[i];
		meanEvolved += evolved[i];
	}
	meanTarget /= count;
	meanEvolved /= count;

	double b = 1.0;
	double a = 0.0;
	double numerator = 0.0;
	double denominator = 0.0;

	for (int i=0; i<count; i++) {
		double factor = (evolved[i] - meanEvolved);
		numerator+= (target[i] - meanTarget) * factor;
		denominator += (factor * factor);
	}

	if (denominator != 0.0) {
		b = numerator / denominator;
	}
	else if (meanEvolved == 0.0) {
		b = 1.0;
	}
	else {
		b = meanTarget / meanEvolved;
	}

	a = meanTarget - (b * meanEvolved);

	this->lsCoeffA = a;
	this->lsCoeffB = b;
}


ResultType GPProgram::getEvolvedGuesses() {
	return evaluate(true);
}

int GPProgram::getNumberOfHits(double hitsCriterion, bool  training) {

	int ret = 0;

	// depending on the value
	if (training) {
		ret = countHits(targets, (lsCoeffA + lsCoeffB * evaluate(true)), hitsCriterion);
	}
	else {
		ret = countHits(test_targets, (lsCoeffA + lsCoeffB * evaluate(false)), hitsCriterion);
	}
	
	return ret;
}


ostream& operator<<(ostream &os, const GPProgram& gpprog) {

	string output;
	stack<string> printStack;

	GPNode *current;
	string type;
	string data1;
	string data2;

	for (int i=0; i<gpprog.getSize(); i++) {
		current = gpprog.getNode(i);
	
		if (current->getArity() == -1) {
			type = current->getType();
			if (type == "VAR") {
				printStack.push("x" + intToString(current->getData()));
			}
			else if (type == "constant") {
				printStack.push(doubleToString(constants[current->getData()]));
			}
		}
		else if (current->getArity() == 0) {
			data1 = printStack.top();
			printStack.pop();
			printStack.push(current->getType() + "(" + data1 + ")");
		}
		else if (current->getArity() == 1) {
			type = current -> getType();
			data2 = printStack.top();
			printStack.pop();
			data1 = printStack.top();
			printStack.pop();
			if (type == "ADD") {
				printStack.push("(" +data1 +" + " +data2 + ")");
			}
			else if (type == "MIN") {
				printStack.push("(" +data1 +" - " +data2 + ")");
			}
			else if (type == "MUL") {
				printStack.push("(" +data1 +" * " +data2 + ")");
			}
			else if (type == "DIV") {
				printStack.push("(" +data1 +" / " +data2 + ")");
			}
		}
		output = printStack.top();
		//printStack.pop();
		
	}
        os << gpprog.getLSCoeffA() << " + " << gpprog.getLSCoeffB() << " * " << output;
	// don't delete current! for some reason, it fucks everything up!
	// FIXME figure out why the hell this is..
	return os;
}

