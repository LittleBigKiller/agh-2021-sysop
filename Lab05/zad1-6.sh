#!/bin/bash
cd $1

link_count=0

for entry in ./*
do
    last=$(echo $entry | cut -c 3-)
    i=0
    arr=()
    while [ "$(readlink $last)" != "" ]
    do
        arr[i]=$last
        i=$((i+1))

        last=$(readlink $last)

        do_break=false
        for elem in ${arr[@]}
        do
            if [ "$last" == "$elem" ]
            then
                do_break=true
                break
            fi
        done

        if [ "$do_break" = true ]
        then
                echo "$entry loops after $i iterations!"
                echo "${arr[@]}"
		link_count=$((link_count+1))
                break
        fi
    done
done

echo "Ilość pętli: $link_count"
