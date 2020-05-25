#!/bin/bash

size=$(($# / 2))
out=0

for (( i=1; i<=$size; i++ ))
do
    off=$(( $size + i ))
    out=$(( $out + $(( ${!i} * ${!off} )) ))
done

echo "Size: $size"
echo "Sum: $out"
