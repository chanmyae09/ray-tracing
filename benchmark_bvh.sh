#!/bin/bash

OUTPUT_CSV="bvh_results.csv"
echo "Render_Time_Seconds" > $OUTPUT_CSV

for i in {1..10}
do
    echo "BVH - Run $i/10"
    g++ -std=c++20 -O3 -DNDEBUG main.cpp -o raytracer
    TIME=$(./raytracer > image.ppm 2>&1 | grep "Render time:" | awk '{print $3}')
    echo $TIME >> $OUTPUT_CSV
done

echo "Results saved to $OUTPUT_CSV"