#!/bin/bash

echo "ProcessorCount, PointCount, ElapsedTime, Pi"
for i in `seq 1 8`;
do
    mpirun -np $i ./pi $1
done
