#!/bin/bash
counter ()  # takes one argument
{
  local let "c1+=$1"
  let "c2+=${1}*2"
  echo "$c1,$c2"
} 

i=1
while [[ $i != 11 ]]; do
  counter $i
  let "i=i+1"
done
echo "Final $c1 , $c2"

