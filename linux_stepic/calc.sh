#!/bin/bash

while [[ true ]]; do
	read x act y

	if [[ $x == "exit" ]]; then
		echo "bye"
		exit
	elif [[ "$x" =~ "^[0-9]+$" && "$y" =~ "^[0-9]+$" ]]; then
	    echo "error"
		exit
	fi
 
	case $act in
	"+") let "result = $x + $y";;
	"-") let "result = $x - $y";;
	"/") if [ $y -eq 0 ]; then
			echo "error"
			exit
	     else
	        let "result = $x / $y"
	     fi;;
	"*") let "result = $x * $y";;
	"%") let "result = $x % $y";;
	"**") let "result = $x ** $y";;
	*)
		echo "error"
		exit
	esac
	echo $result
done
