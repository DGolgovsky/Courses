#!/bin/bash
case $1 in
0)
echo "No students"
;;
1)
echo "$1 student"
;;
2)
echo "$1 students"
;;
3)
echo "$1 students"
;;
4)
echo "$1 students"
;;
*)
echo "A lot of students"
esac

if [[ $var1 == $var2 || $var1 != var2 ]]
then
	echo "1.True"
fi
if [[ -z "" ]]
then
        echo "2.True"
fi
if [[ !(4 -le 3) ]]
then
        echo "3.True"
fi
if [[ -s $0 ]]
then
        echo "4.True"
fi
if [[ $# -gt 0 ]]
then
        echo "5.True"
fi
if [[ -e $0 ]]
then
        echo "6.True"
fi
var=3
if [[ $var -gt 5 ]]
then
  echo "one" 
elif [[ $var -lt 3 ]]
then
  echo "two"
elif [[ $var -eq 4 ]]
then
  echo "three"
else
  echo "four"
fi
var=5
if [[ $var -gt 5 ]]
then
  echo "one" 
elif [[ $var -lt 3 ]]
then
  echo "two"
elif [[ $var -eq 4 ]]
then
  echo "three"
else
  echo "four"
fi
for str in a , b , c_d
do
  echo "start"  
  if [[ $str > "c" ]]
  then
    continue
  fi
  echo "finish"
done
