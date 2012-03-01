#!/bin/bash
#PBS -j oe
#PBS -V

cd $PBS_O_WORKDIR

np=`wc -l $PBS_NODEFILE | cut -f 1 -d ' '`

# compiles the code
mpicc -O2 main.c alg1.c alg2.c -std=c99

# runs the program and save data to file
mpirun -np $np -machinefile $PBS_NODEFILE a.out > results.txt 

#generate graphs from the data
#gnuplot graf_costs.gnu 
