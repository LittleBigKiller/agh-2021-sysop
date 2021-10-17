#!/bin/bash

opcje[0]="papier"
opcje[1]="kamien"
opcje[2]="nozyce"

while :; do
    while [ ! -f komenda.txt ]; do sleep 0.1; done

    com=$(<komenda.txt)
    if [ "$com" = "stop" ]; then
	exit 0
    elif [ "$com" = "start" ]; then
	if [ ! -f los1.txt ]; then
	    echo ${opcje[$(($RANDOM % 3))]} > los1.txt
	fi
    fi
    sleep 0.1
done
