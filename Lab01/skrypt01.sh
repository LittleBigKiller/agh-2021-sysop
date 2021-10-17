#!/bin/bash
find $1 -type f -size +$2 -printf "%T@ %p\n" | sort -n | cut -d' ' -f 2- | tail -n 1
