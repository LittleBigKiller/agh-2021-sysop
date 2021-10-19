#!/bin/bash
convert -density 600 $1 -append temp.png
composite -gravity northwest -geometry +$3-$4 $2 temp.png final.png
convert final.png result.pdf

