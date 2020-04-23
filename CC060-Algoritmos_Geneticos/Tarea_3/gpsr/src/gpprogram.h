#ifndef GPPROGRAM_H
#define GPPROGRAM_H

#include <stack>

#include "gpnode.h"
#include "global.h"

class GPProgram {

	public:
		// constructors
		GPProgram();
		GPProgram(const GPProgram& other);
		GPProgram(int size, int maxDepth);
		~GPProgram();

		void operator=(const GPProgram &rhs);

		// accessors
		std::vector<GPNode*> getGenome() const;
		int getSize() const;
		double getFitness() const;
		double getLSCoeffA() const;
		double getLSCoeffB() const;

		std::string getType(int i) const;

		// mutators
		void setGenome(const std::vector<GPNode*> &genome);
		void setSize(int s);
		void setFitness(double fit);
		void setLSCoeffA(double a);
		void setLSCoeffB(double b);

		// other member functions
		double getTestFitness() ;
		void addNode(GPNode *gpnode);
		void removeNode(int index);
		void setNode(unsigned index, GPNode *gpnode);
		void insertNode(int index, GPNode *gpnode);
		void insertSubtree(int index, const std::vector<GPNode*> &subtree);
		void removeSubtree(int start, int end);
		std::vector<GPNode*> getSubtree(int start, int end) const;
		GPNode* getNode(int index) const;
		void resetSize();
		std::vector<int> getDepths() const;
		void initialise(int size, int maxDepth);

		ResultType evaluate(bool training);
		double calcFitness(bool training);
		void linearScaling(const ResultType &evolved, const ResultType &target);
		ResultType getEvolvedGuesses();
		int getNumberOfHits(double hitsCriterion, bool training);

	private:
		std::vector<GPNode*> genome;
		int size;
		double fitness;
		
		// linear scaling stuff
		double lsCoeffA;
		double lsCoeffB;
	
		friend std::ostream& operator<<(std::ostream& os, const GPProgram& gpprog);
};
#endif
