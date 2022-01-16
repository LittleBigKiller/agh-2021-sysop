ls -li | awk '{print $1, $10}' | sort | awk '{print $2, $1}' | uniq -d -f 1

