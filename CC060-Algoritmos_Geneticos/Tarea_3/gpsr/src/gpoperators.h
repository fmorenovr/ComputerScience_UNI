#ifndef GPOPERATORS_H
#define GPOPERATORS_H

#include <vector>
#include "gppopulation.h"


void tournamentSelection(GPPopulation &pop);
void mutation(GPPopulation &pop);
void crossover(GPPopulation &pop); 

int select(GPPopulation &pop);
GPProgram* xover(const GPProgram &mom, const GPProgram &dad);
void branchMutate(GPProgram &indy);
void nodeMutate(GPProgram &indy);

std::vector<GPNode*> growSubtree(int size, int startDepth);
int findStart(std::vector<int> depths, int index, const GPProgram &gpprog);
int getMaxDepth(std::vector<int> depths);

#endif
