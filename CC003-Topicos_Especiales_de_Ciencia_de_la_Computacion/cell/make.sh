#!/usr/bin/bash

g++ cell_sim.cpp -lglut -lGL -lGLU -fopenmp -o cell
./cell

