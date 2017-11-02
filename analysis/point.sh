#!/bin/bash

echo "ProcessorCount, PointCount, ElapsedTime, Pi"
for (( i=1; i<=1000000000; i*=10  ));
do
    mpirun -np 4 ./pi $i
done

