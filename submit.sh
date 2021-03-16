#!/bin/bash
#
#SBATCH --job-name=pi-calculator
#SBATCH --output=pi.txt
#
#SBATCH --ntasks=1
#SBATCH --time=5:00
#SBATCH --mem-per-cpu=100

for i in {1..16}
do
    srun ./pi.out $i 1000
done

for i in {1..16}
do
    srun ./pi.out $i 100000
done

for i in {1..16}
do
    srun ./pi.out $i 10000000
done