#!/bin/bash
res=1

if [ $2 -gt 0 ]; then
	for i in $(seq $2); do
		res=$((res*$1))
	done
else
	for i in $(seq $(echo ${2#-}) ); do
		res=$(echo "$res/$1" | bc -l)
	done
fi

echo $res | bc -l
