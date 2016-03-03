#!/bin/sh

ip_file=${1}
ip_file=ip.txt
if [ -z ${ip_file} ]
then
  echo "PLease enter the file path"
fi
./a.out < ${ip_file}
