#!/bin/bash

##################################################
#### Author: Moreno Vera, Felipe Adrian  #########
##################################################

gcc pi.c -o pi.out
gcc piOMP.c -fopenmp -lm -o piOMP.out
mpicc piMPI.c -lm -o piMPI.out
mpicc pi_MPI_OMP.c -fopenmp -lm -o piMPI_OMP.out

function menu_paralelo {
  echo "Escogio el metodo paralelizado"
  echo "Escoja el metodo: "
  echo -e "\n1.MPI\n2.OpenMP\n3.MPI + OpenMP\n4.Salir"
  read -n 1 -p "Escoja el metodo (1/2/3/4) " ans;
  
  case $ans in
    1)
      echo -e "\nEscogio MPI:\n"
      mpiexec -np $2 ./piMPI.out $1
      ;;
    2)
      echo -e "\nEscogio OpenMP:\n"
      ./piOMP.out $2 $1
      ;;
    3)
      echo -e "\nEscogio MPI+OpenMP:\n"
      mpiexec -np $procs ./piMPI_OMP.out $1
      ;;
    *)
      echo -e "\nEscogio Salir, Adios Meow ~~"
      exit
      ;;
  esac
}

echo "Menu de ejecuciones:"
echo -e "\n1.Metodo Secuencial\n2.Metodo Paralelizado"
read -n 1 -p "Escoja el metodo (1/2) " answ;

case $answ in
  1)
    echo -e "\nEscogio Secuencial:"
    echo -e "\nIngrese el numero de intervalos: "
    read i
    ./pi.out $i
    ;;
  2)
    echo -e "\nEscogio Paralelizado:"
    echo -e "\nIngrese el numero de intervalos: "
    read i
    echo -e "\nEscoja el numero de procesos"
    read procs
    menu_paralelo $i $procs
    ;;
  *)
    echo -e "\nMetodo incorrecto, Adios Meow~~";;
esac
