#!/bin/bash

for i in $(seq $1); do
	score[$i]=0
	los[$i]=""
	./gracz_v2.sh $i 2>/dev/null &
done
remis=0

#	for i in $(seq $1); do
#		for j in $(seq $i $1); do
#			if [ $i -eq $j ]; then
#				continue
#			fi
#			echo "$i $j"
#		done
#	done

#	for sc in "${score[@]}"; do
# 		echo "$sc"
#	done

for runda in $(seq $2); do
	echo "start" > komenda.txt

	for i in $(seq $1); do
		while [ ! -f "los$i.txt" ]; do sleep 0.001; done
		los[$i]=$(<"los$i.txt")
	done

	rm -rf komenda.txt 2>/dev/null

	for i in $(seq $1); do
		for j in $(seq $i $1); do
			if [ $i -eq $j ]; then
				continue
			fi
			
			if [ ${los[$i]} = ${los[$j]} ]; then
				remis=$((remis+1))
				echo "remis" >> gra.log

			elif [ ${los[$i]} = "papier" ]; then
				if [ ${los[$j]} = "kamien" ]; then
					score[$i]=$((score[$i]+1))
					echo "gracz$i" >> gra.log
				else
					score[$j]=$((score[$j]+1))
					echo "gracz$j" >> gra.log
				fi

			elif [ ${los[$i]} = "kamien" ]; then
				if [ ${los[$j]} = "nozycze" ]; then
					score[$i]=$((score[$i]+1))
					echo "gracz$i" >> gra.log
				else
					score[$j]=$((score[$j]+1))
					echo "gracz$j" >> gra.log
				fi

			elif [ ${los[$i]} = "nozyce" ]; then
				if [ ${los[$j]} = "papier" ]; then
					score[$i]=$((score[$i]+1))
					echo "gracz$i" >> gra.log
				else
					score[$j]=$((score[$j]+1))
					echo "gracz$j" >> gra.log
				fi
			fi
		done
	done

	for i in $(seq $1); do
    	rm -rf "los$i.txt" 2>/dev/null
	done
done

echo "stop" > komenda.txt
sleep 0.001
rm -rf komenda.txt 2>/dev/null

for i in $(seq $1); do
	echo gracz$i:$'\t'${score[$i]}
done

echo remisy:$'\t'$remis

exit 0
