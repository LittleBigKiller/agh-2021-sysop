#!/bin/bash

MYFILE="los$1.txt"

opcje[0]="papier"
opcje[1]="kamien"
opcje[2]="nozyce"

while :; do
    while [ ! -f komenda.txt ]; do sleep 0.001; done

    com=$(<komenda.txt)
    if [ "$com" = "stop" ]; then
	exit 0
    elif [ "$com" = "start" ]; then
	if [ ! -f $MYFILE ]; then
	    echo ${opcje[$(($RANDOM % 3))]} > $MYFILE
	fi
    fi
    sleep 0.001
done
