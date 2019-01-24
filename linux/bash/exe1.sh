#!/bin/bash

SPLIT="=================================================="

echo "1. define a variable FILE whose value is /etc/passwd"
echo "$SPLIT"
File="/etc/passwd"
echo "file is $File"


printf "2. say hello to users in /etc/passwd\n%s\n", $SPLIT
#with awk
awk -v "FS=:" '{ print "hello", $1, "your user UID is", $3}' /etc/passwd

#normal operations
Num=`cat $File | wc -l`
let N=0
#note that for use space and return as split character;
#for Line in `cat $File`; do
#    echo $N, $Line
#    Name=`echo $Line | awk -F: '{print $1}'`
#    ID=`echo "$Line" | awk -F: '{print $3}'`
#    echo "Hello $Name, your ID is $ID"
#    N=$[$N + 1]
#done
while read Line; do
    Name=`echo $Line | awk -F: '{print $1}'`
    ID=`echo "$Line" | awk -F: '{print $3}'`
    echo "Hello $Name, your ID is $ID"
    N=$[$N + 1]
done < $File

echo "there has $Num Users"
echo $N








