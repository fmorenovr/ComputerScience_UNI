#ifndef RNG_H
#define RNG_H

#include <cmath>
#include <climits>

typedef unsigned long ulong;


class RNG {             // encapsulate random number generator
	public:
		RNG();
		RNG(ulong seed);   // constructor
		void RandomInit(ulong seed);      // initialization
		ulong IRandom(int min, int max);       // get integer random number in desired interval
		ulong random(int n);
		double Random();                     // get floating point random number
		double uniform();
		bool flip(double);
		void reseed(ulong seed);
		double dblRandom(double low, double high);
		int intRandom(int low, int high);

	protected:
		double x[5];                         // history buffer
		ulong seed;
};
#endif  
