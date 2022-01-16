#!/bin/bash
ls -alR | awk -F" " '{print $1}' | cut -c 2- | grep "^[r,-]" | sort | uniq -c
