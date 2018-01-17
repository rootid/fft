#!/bin/sh

ip_file=${1}
if [ -z ${ip_file} ]
then
  echo "PLease enter the file path"
fi
a.out < ${ip_file}
