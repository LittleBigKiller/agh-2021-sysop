#!/bin/bash
res=1

for i in $(seq $2); do
	res=$((res*$1))
done

echo $res
