#include <iostream>
#include "gpoperators.h"
#include "rng.h"
#include "usefulfunctions.h"

using namespace std;

void tournamentSelection(GPPopulation &pop) {

	GPPopulation *temp = new GPPopulation(pop);

	int selected_index = 0;
	GPProgram* luckyBugger;
	for (int i = 0; i < temp->getSize(); i++) {
		selected_index = select(pop);
		luckyBugger = pop.getIndividual(selected_index);
		temp->setIndividual(i, luckyBugger);
	}

	pop = *temp;
	delete temp;
}

void mutation(GPPopulation &pop) {

	GPPopulation *temp = new GPPopulation(pop);
	GPProgram *mutant;

	for (int i = 0; i < pop.getSize(); i++) {
		if (rng.flip(mutation_prob)) {
			// do a mutation, but first choose whether to do a node
			// or a branch mutation
			mutant = pop.getIndividual(i);
			if (rng.flip(0.5)) {
				// do a node mutation
				nodeMutate(*mutant);
			}
			else {
				// do a branch mutation
				branchMutate(*mutant);
			}
			temp->setIndividual(i, mutant);
		}
	}
	pop = *temp;
	delete temp;
}

void crossover(GPPopulation &pop) {

	GPPopulation *temp = new GPPopulation(pop);
        GPProgram *child;
        GPProgram *mom;
        GPProgram *dad;

        int popsize = pop.getSize();
        for (int i = 0; i < popsize; i++) {
            if (rng.flip(crossover_prob)) {
                mom = pop.getIndividual(intRandom(0, popsize - 1));
                dad = pop.getIndividual(intRandom(0, popsize - 1));
                //child = new GPProgram(*(xover(mom, dad)));
                child = xover(*mom, *dad);
                temp->setIndividual(i, child);
            }
        }
	pop = *temp;
	delete temp;
}

int select(GPPopulation &pop) {
	//cout << "\tentered select()\n";
	int best_index = intRandom(0, pop.getSize() - 1);
        int competitor_index = 0;

        GPProgram *best = pop.getIndividual(best_index);
        GPProgram *competitor;

        double best_perf = best->getFitness();
        double competitor_perf = 0;

        for (int i = 1; i < tournamentSize; i++) {

            competitor_index =intRandom(0, pop.getSize() - 1);
            competitor = pop.getIndividual(competitor_index);
            competitor_perf = competitor->getFitness();

            if(competitor_perf < best_perf) {
                best = competitor;
		best_index = competitor_index;
            }
        }
	//cout << "\tleaving select(), best_index = " << best_index << "\n";
        return best_index;
}

GPProgram* xover(const GPProgram &mom, const GPProgram &dad) {
	//GPProgram *ret = new GPProgram(*mom);
	GPProgram *ret = new GPProgram(mom);
	// quick check: mom might only have one node
	int momIndex = 0;
	int momBranchStart = 0;
	//if (mom->getSize() == 1) {
	if (mom.getSize() == 1) {
		momIndex = 0;
	}
	else {
		// don't do crossover at the root level
		//momIndex = intRandom(0, mom->getSize() - 2);
		momIndex = intRandom(0, mom.getSize() - 2);
		//cout << "xover: momIndex = " << momIndex << endl;
	}

	//GPNode* momNode = mom->getNode(momIndex);
	GPNode* momNode = mom.getNode(momIndex);
	int momArity = momNode->getArity();
	//std::vector<int> momDepths = mom->getDepths();
	std::vector<int> momDepths = mom.getDepths();

	if (momArity == -1) {
		// we have a terminal, so we just remove it
		momBranchStart = momIndex;
		ret->removeNode(momIndex);
		ret->resetSize();
	}
	else {

		// we have a subtree, so we need to prune
		int momDepth = momDepths[momIndex];
		if (momDepth != -1) {
			//momBranchStart = findStart(momDepths, momIndex, *mom);
			momBranchStart = findStart(momDepths, momIndex, mom);
			//cout << "xover: momBranchStart = " << momBranchStart << endl;
		}
		ret->removeSubtree(momBranchStart, momIndex);
		ret->resetSize();
	}


	// that's mom taken care of, now for dad..
	int dadIndex = 0;
	int dadBranchStart = 0;
	//if (dad->getSize() == 1) {
	if (dad.getSize() == 1) {
		dadIndex = 0;
	}
	else {
		//dadIndex = intRandom(0, dad->getSize() - 2);
		dadIndex = intRandom(0, dad.getSize() - 2);
		//cout << "xover: dadIndex = " << dadIndex << endl;
	}
	//GPNode* dadNode = dad->getNode(dadIndex);
	GPNode* dadNode = dad.getNode(dadIndex);
	int dadArity = dadNode->getArity();
	//std::vector<int> dadDepths = dad->getDepths();
	std::vector<int> dadDepths = dad.getDepths();

	if (dadArity == -1) {
		// we've found a terminal on dad, so we simply place dadNode onto mom at momIndex
		ret->insertNode(momBranchStart, dadNode);
		ret->resetSize();
	}
	else {
		// we have a subtree to get from dad and copy to mom..
		int dadDepth = dadDepths[dadIndex];
		if (dadDepth != -1) {
			//dadBranchStart = findStart(dadDepths, dadIndex, *dad);
			dadBranchStart = findStart(dadDepths, dadIndex, dad);
			//cout << "xover: dadBranchStart = " << dadBranchStart << endl;
		}
		//std::vector<GPNode*> dadSubtree = dad->getSubtree(dadBranchStart, dadIndex);
		std::vector<GPNode*> dadSubtree = dad.getSubtree(dadBranchStart, dadIndex);
		//cout << "xover: dadSubtree.size() = " << dadSubtree.size() << endl;
		ret->insertSubtree(momBranchStart, dadSubtree);
		ret->resetSize();
	}

	// do a quick sanity check -- make sure that crossover hasn't exceeded the depths
	if (getMaxDepth(ret->getDepths()) < -MAXDEPTH) {
		delete ret;
		ret = new GPProgram(mom);
		//return mom;
		return ret;
	}
	else {
		return ret;
	}
}

void branchMutate(GPProgram &indy) {

	//cout << "entered branchMutate"<< endl;
	//cout << "entered branchMutate, indy is:\n" << indy << endl;
	GPProgram* ret = new GPProgram(indy);
	std::vector<int> depths = indy.getDepths();
	std::vector<GPNode*> subTree;

        // hack: never pick the first node unless there's only one
        int branchIndex = 0;
        if (indy.getSize() == 1) {
            branchIndex = 0;
        }
        else {
            // don't pick the root (end node)
            branchIndex = intRandom(0, indy.getSize() - 2);
        }

        GPNode *branch = indy.getNode(branchIndex);
        int arity = branch->getArity();
        int branchDepth = 0;
        int branchStart = 0;

        if (arity == -1) {
            // we have a terminal  
	    //cout << "picked a terminal at branchIndex = " << branchIndex << endl;
            branchDepth = depths[branchIndex]; 

            // grow a new subtree and replace this terminal with the subtree
            subTree = growSubtree(BRANCHSIZE, branchDepth);

            // now do the insert
            if (subTree.size() != 0) {
                // remove the element at branchIndex
                ret->removeNode(branchIndex);
                ret->resetSize();
                // insert the new subtree
                ret->insertSubtree(branchIndex, subTree);
                ret->resetSize();
            }
        }
        //else if (arity == 1) {
        else {
            // we have a function
	    //cout << "picked a function at branchIndex = " << branchIndex << endl;
	    branchDepth = depths[branchIndex];
            // prune the subtree from this node (using find start), then grow
            // a new subtree in its place

            // if the branchDepth != -1, we have to locate the start of the
            // subtree and remove it
            //
            // Otherwise, we can remove from element 0
            if (branchDepth != -1) {
                branchStart = findStart(depths, branchIndex, indy);
            }
            else {
                branchStart = 0;
            }
            subTree = growSubtree(BRANCHSIZE, branchDepth);
            if (subTree.size() != 0) {
                // prune away the old stuff
                ret->removeSubtree(branchStart, branchIndex);
                ret->resetSize();

                // insert the new
                ret->insertSubtree(branchStart, subTree);
                ret->resetSize();
            }
        }
	indy = *ret;
	delete ret;
	//cout << "leaving branchMutate()\n";
}

void nodeMutate(GPProgram &indy) {
	GPProgram *ret = new GPProgram(indy);
	int mutantIndex = intRandom(0, indy.getSize() - 1);
	//GPNode* mutant = new GPNode(*(indy.getNode(mutantIndex)));
	GPNode* mutant = indy.getNode(mutantIndex);

	int arity = mutant->getArity();

	if (arity == -1) {
		if (rng.flip(0.5)) {
			mutant = getRandomConstant();
		}
		else {
			mutant = getRandomVariable();
		}
	}
	else if (arity == 0) {
		mutant = getRandomUnary();
	}
	else if (arity == 1) {
		mutant = getRandomBinary();
	}
	ret->setNode(mutantIndex, mutant);
	indy = *ret;
	delete ret;
}


std::vector<GPNode*> growSubtree(int size, int startDepth) {

	//cout << "entered growSubtree()\n";

	std::vector<GPNode*> ret; 
        GPNode current;
	int rndnum = 0;

        // start with a terminal
        if (rng.flip(0.5)) {
		rndnum = intRandom(0, t_variables.size()-1);
		current = t_variables[rndnum];
		//ret.push_back(new GPNode(current));
		ret.push_back(&(t_variables[rndnum]));
        }
        else {
		// random constant
		rndnum = intRandom(0, t_constants.size()-1);
		current = t_constants[rndnum];
		//ret.push_back(new GPNode(current));
		ret.push_back(&(t_constants[rndnum]));
        }

	int depth = -1 - startDepth;
        int maxdepth = -1 - startDepth;
        int lastValidLocation = 0;
        int currentArity = 0;

	for (int i = 1; i < size; i++) {

		if (depth < -1) {
			switch( rng.random(3) ) {
				case 2: 
					// random terminal
					if (rng.flip(0.5)) {
						// random constant
						current = t_constants[intRandom(0, t_constants.size()-1)];
						currentArity = current.getArity();
						//ret.push_back(new GPNode(current));
						ret.push_back(&(t_constants[rndnum]));
					}
					else {
						// random variable
						current = t_variables[intRandom(0, t_variables.size()-1)];
						currentArity = current.getArity();
						//ret.push_back(new GPNode(current));
						ret.push_back(&(t_variables[rndnum]));
					} 
					break;
				case 1: 
					// random unary
					current = t_unaries[intRandom(0, t_unaries.size()-1)];
					currentArity = current.getArity();
					//ret.push_back(new GPNode(current));
					ret.push_back(&(t_unaries[rndnum]));
					break;
					
				case 0: 
					// random binary
					current = t_binaries[intRandom(0, t_binaries.size()-1)];
					currentArity = current.getArity();
					//ret.push_back(new GPNode(current));
					ret.push_back(&(t_binaries[rndnum]));
			}
		}
		else if (depth == -1) {
			switch (rng.random(2)) {
				case 1:
					// random terminal 
					if (rng.flip(0.5)) {
						current = t_constants[intRandom(0, t_constants.size()-1)];
						currentArity = current.getArity();
						//ret.push_back(new GPNode(current));
						ret.push_back(&(t_constants[rndnum]));
					}
					else {
						current = t_variables[intRandom(0, t_variables.size()-1)];
						currentArity = current.getArity();
						//ret.push_back(new GPNode(current));
						ret.push_back(&(t_variables[rndnum]));
					}
					break;
				case 0: 
					// random unary
					current = t_unaries[intRandom(0, t_unaries.size()-1)];
					currentArity = current.getArity();
					//ret.push_back(new GPNode(current));
					ret.push_back(&(t_unaries[rndnum]));
					break;
			}
		}

		depth += currentArity;
		
		maxdepth = min(depth, maxdepth);

		if (maxdepth <= -MAXDEPTH) {
			break;
		}

		if (depth == -1) {
			lastValidLocation = i;
		}
	}

	ret.resize(lastValidLocation + 1);
	//cout << "finished growSubtree(), size = " << ret.size() << "\n";
	//for (int i=0; i<ret.size(); i++) {
	//	cout << ret[i] -> getType() << " ";
	//}
	//cout << "\n";
        return ret;
}

int findStart(std::vector<int> depths, int index, const GPProgram &gpprog) {

	int start = 0;

        if (index == 0) {
            return start;
        }
        else {
            start = index - 1;
        }

        int depth = depths[index];

        // make sure we find a leaf node at the start, otherwise a function could be
        // returned resulting in an invalid individual
        bool found = 0;
        while (!found) {
            if ( depth == (depths[start]) && (gpprog.getNode(start)->getArity() == -1) ) {
                found = 1;
            }
            else {
                start--;
            }
        }
        return start;

}


int getMaxDepth(std::vector<int> depths) {
	int max = 1000; // FIXME might want to make this bigger
	int val = 0;
	for (unsigned i = 0; i < depths.size(); i++) {
		val = depths[i];
		if (val <= max) {
			max = val;
		}
	}
	return max;
}

