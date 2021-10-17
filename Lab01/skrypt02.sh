#!/bin/bash

if [ $1 -gt $2 ]; then
	echo "<max> nie może być mniejsze od <min>. Kończenie..."
	exit 1
fi

finnum=$(shuf -i $1-$2 -n 1)
ctr=0

read input
while [ $input -ne $finnum ]; do
	ctr=$((ctr+1))
	if [ $ctr -eq 10 ]; then
		echo "10 prób minęło. Koniec gry!"
		exit 0
	fi

	if [ $input -lt $finnum ]; then
		echo "Za mała"
	else
		echo "Za duża"
	fi
	read input
done

echo "Zwycięstwo"
exit 0
