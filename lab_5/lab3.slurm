#!/bin/bash
#SBATCH --job-name=run8
#SBATCH --ntasks-per-node=8
#SBATCH --time=00:30:00
#SBATCH --output=out4.out
#SBATCH --error=err4.err

module purge
module load intel/mpi4
mpirun ./matMulMPI
EOF