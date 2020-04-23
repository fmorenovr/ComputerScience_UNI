#!/bin/bash

GP=./bin/gpsr				
RESULTS=./results
NUMRUNS=$1
TRAINFILE=./datasets/quartic_train.dat
TESTFILE=./datasets/quartic_test.dat

for i in `seq -w $NUMRUNS`
do
  echo ""
  echo "*************************************************"
  echo "Ejecucion Numero: $i"
  $GP -d $TRAINFILE -f $TESTFILE -o $RESULTS/ejecucion_$1/best$i -O $RESULTS/ejecucion_$1/res$i
  echo ""
  echo "*************************************************"
  echo ""
done
