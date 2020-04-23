#ifndef GPPOPULATION_H
#define GPPOPULATION_H

#include "gpprogram.h"
#include <vector>

class GPPopulation {

	public:
		GPPopulation(int size);
		GPPopulation(const GPPopulation &other);
		GPPopulation(int size, int indySize);
		~GPPopulation();
		void operator=(const GPPopulation &rhs);

		int getIndexOfBest() const;
		std::vector<GPProgram*> getPopulation() const;
		int getSize() const;

		void setIndexOfBest(int index);
		void setPopulation(const std::vector<GPProgram*> &pop);

		GPProgram* getIndividual(int index) const;
		double getIndividualFitness(int index);

		void setIndividual(int index, GPProgram* indy);
		GPProgram* getBestIndividual();
		void updateBestIndividual();
		int getIndexOfWorst();
		void calculatePopulationFitness();

	private:
		int indexOfBest;
		std::vector<GPProgram*> population;
		
		friend std::ostream& operator<<(std::ostream& os, const GPPopulation& pop);
};


#endif
