#!/bin/bash

name="a"
age=1
while [[ "$name" != "" || "$age" != 0 ]]
do
  echo "enter your name:"
  read name  
  if [[ -z $name ]]
  then
    break
  fi

  echo "enter your age:"
  read age
  if [[ $age == 0 ]]
  then
    break
  fi

  if [[ $age -le 16 ]]
  then
	groupe="child"
  elif [[ $age -le 25 ]]
  then
	groupe="youth"
  else
	groupe="adult"
  fi
      
  echo "$name, your group is $groupe"
done
echo "bye"
exit
