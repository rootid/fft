#Given a text file file.txt that contains list of phone numbers (one per line), write a one liner bash script to print all valid phone numbers.
#You may assume that a valid phone number must appear in one of the following two formats: (xxx) xxx-xxxx or xxx-xxx-xxxx. (x means a digit)
#You may also assume each line in the text file must not contain leading or trailing white spaces.
#For example, assume that file.txt has the following content:
#987-123-4567
#123 456 7890
#(123) 456-7890
#Your script should output the following valid phone numbers:
#987-123-4567
#(123) 456-7890

#!/bin/sh

##################### Grep ##################### 
grep -P '^([0-9]{3}-|([0-9]{3}) )[0-9]{3}-[0-9]{4}$' file.txt

##################### Awk ##################### 
awk '/^(\([0-9]{3}\) |[0-9]{3}-)[0-9]{3}-[0-9]{4}$/' file.txt

##################### Awk ##################### 
grep -e '\(^[0-9]\{3\}-[0-9]\{3\}-[0-9]\{4\}$\)' -e '\(^([0-9]\{3\})[ ]\{1\}[0-9]\{3\}-\([0-9]\{4\}\)$\)'  file.txt

#1. In Bash, we use \ to escape next one trailing character;
#2. ^ is used to denote the beginning of a line
#3. $ is used to denote the end of a line
#4. {M} is used to denote to match exactly M times of the previous occurence/regex
#5. (...) is used to group pattern/regex together
#Back to this problem: it requires us to match two patterns, for better readability, I used -e and separate the two patterns into two regexes, the first one matches this case: xxx-xxx-xxxx and the second one matches this case: (xxx) xxx-xxxx

grep -e "^\([0-9]\{3\}-\|([0-9]\{3\}) \)[0-9]\{3\}-[0-9]\{4\}$" telephone.txt

#1. remember use \ to escape |;
#2. ( and ) also need to be escaped when they are used following ^ as showing its bound;


##################### Grep ##################### 
grep -P '^(\d{3}-|\(\d{3}\) )\d{3}-\d{4}$' file.txt

##################### Sed ##################### 
sed -n -r '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/p' file.txt

##################### AWK ##################### 
awk '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/' file.txt


##################### AWK ##################### 
awk '/^([[:digit:]]{3}-|\([[:digit:]]{3}\) )[[:digit:]]{3}-[[:digit:]]{4}$/' file.txt


##################### egrep ##################### 
egrep -o "^(([0-9]{3}\-)|(\([0-9]{3}\) )){1}[0-9]{3}\-[0-9]{4}$" file.txt

#egrep -o: output the exact match
#^: match the beginning of line
#([0-9]{3}\-): match exactly 3 digits followed by '-', e.g. xxx-.
#(\([0-9]{3}\) ): match 3 digits between ( and ) followed by a single
#space, e.g. (xxx) .
#(([0-9]{3}\-)|(\([0-9]{3}\) )){1}: combine the two previous matches from point 3 and 4:
#matches or 3 digits followed by '-', e.g. xxx-, or 3 digits between ( and )
#followed by a single space, e.g. (xxx) , exactly {1} time, because the phone number can be in the format (xxx) xxx-xxxx or xxx-xxx-xxxx.
#[0-9]{3}\-: match exactly 3 digits followed by '-'
#[0-9]{4}: match exactly 4 digits
#$: match end of line
