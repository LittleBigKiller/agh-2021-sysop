#!/bin/bash
if [ -z "$1" ]; then
    set -- "0"
fi

./gracz1.sh 2>/dev/null &
./gracz2.sh 2>/dev/null &

scor1=0
scor2=0
remis=0

for i in $(seq $1); do
    echo "start" > komenda.txt
    while [ ! -f los1.txt ]; do sleep 0.1; done
    while [ ! -f los2.txt ]; do sleep 0.1; done
    sleep 0.1
    rm -rf komenda.txt 2>/dev/null
    los1=$(<los1.txt)
    los2=$(<los2.txt)

    if [ $los1 = $los2 ]; then
	remis=$((remis+1))
	echo "remis\n" >> gra.log
    elif [ $los1 = "papier" ]; then
	if [ $los2 = "kamien" ]; then
	    scor1=$((scor1+1))
	    echo "gracz1" >> gra.log
        else
	    scor2=$((scor2+1))
	    echo "gracz2" >> gra.log
	fi
    elif [ $los1 = "kamien" ]; then
	if [ $los2 = "nozycze" ]; then
	    scro1=$((scor1+1))
	    echo "gracz1" >> gra.log
	else
	    scor2=$((scor2+1))
	    echo "gracz2" >> gra.log
	fi
    elif [ $los1 = "nozyce" ]; then
	if [ $los2 = "papier" ]; then
	    scor1=$((scor1+1))
	    echo "gracz1" >> gra.log
	else
	    scor2=$((scor2+1))
	    echo "gracz2" >> gra.log
	fi
    fi

    rm -rf los1.txt 2>/dev/null
    rm -rf los2.txt 2>/dev/null
done

echo "stop" > komenda.txt
sleep 1
rm -rf komenda.txt 2>/dev/null

echo "gracz1: $scor1"
echo "gracz2: $scor2"
echo "remisy: $remis"

exit 0
