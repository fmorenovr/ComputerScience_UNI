#!/usr/bin/bash

gcc TwoBodyProb.c nbody.c  -lm -o TwoBody
./TwoBody --help

# queda crear un fichero por cada particula para:
# coordenadas, rmin, rmax y excentricidad
