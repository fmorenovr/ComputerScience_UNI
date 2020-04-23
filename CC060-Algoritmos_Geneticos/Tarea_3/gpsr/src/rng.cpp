#include <cmath>
#include "rng.h"

// constructor:
RNG::RNG(ulong seed) {
	// initialize
	RandomInit(seed);
}

RNG::RNG() {

}


// returns a random number between 0 and 1:
double RNG::Random() {

  long double c;
  c = (long double)2111111111.0 * x[3] +
      1492.0 * (x[3] = x[2]) +
      1776.0 * (x[2] = x[1]) +
      5115.0 * (x[1] = x[0]) +
      x[4];
  x[4] = floor(c);
  x[0] = c - x[4];
  x[4] = x[4] * (1./(65536.*65536.));
  return x[0];
}


// returns integer random number in desired interval:
ulong RNG::IRandom(int min, int max) {
	int iinterval = max - min + 1;
	if (iinterval <= 0) return 0x80000000; // error
	int i = long(iinterval * Random()); // truncate
	if (i >= iinterval) i = iinterval-1;
	return min + i;
}


// this function initializes the random number generator:
void RNG::RandomInit (ulong seed) {
	this->seed = seed;
	int i;
	unsigned long s = seed;
	// make random numbers and put them into the buffer
	for (i=0; i<5; i++) {
		s = s * 29943829 - 1;
		x[i] = s * (1./(65536.*65536.));
	}

	// randomize some more
	for (i=0; i<19; i++) 
		Random();
}

// return a uniform random between 0 and 1
double RNG::uniform() {
	return Random();
}

// flip a biased coin
bool RNG::flip(double d) {
	return (uniform() <= d);
}

// reseed
void RNG::reseed(ulong seed) {
	RandomInit(seed);
}

ulong RNG::random(int n) {
	return IRandom(0, n-1);
}

double RNG::dblRandom(double low, double high) {
	double nb = high - low +1;
	return (uniform() * nb) + low;
}

int RNG::intRandom(int low, int high) {
	return IRandom(low, high);
}

