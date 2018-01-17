#How would you print just the 10th line of a file?
#For example, assume that file.txt has the following content:
#Line 1
#Line 2
#Line 3
#Line 4
#Line 5
#Line 6
#Line 7
#Line 8
#Line 9
#Line 10
#Your script should output the tenth line, which is:
#Line 10
#Hint:
#1. If the file contains less than 10 lines, what should you output?
#2. There's at least three different solutions. Try to explore all possibilities.

#!/bin/sh

############################### sed ############################### 
sed -n '10p;11q' file.txt


############################### AWK ############################### 
awk 'FNR == 10 {print }'  file.txt
# OR
awk 'NR == 10' file.txt

############################### sed  ############################### 
sed -n 10p file.txt

############################### tail | head  ############################### 
tail -n+10 file.txt|head -1

############################### bash ############################### 
cnt=0
while read line && [ $cnt -le 10 ]; do
  let 'cnt = cnt + 1'
  if [ $cnt -eq 10 ]; then
    echo $line
    exit 0
  fi
done < file.txt

############################### cut ############################### 
cat file.txt | cut -d $'\n' -f 10


