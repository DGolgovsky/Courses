#!bin/bash

gcd()
{
	let "m=$1%$2"
	if [[ $m == 0 ]]; then
		let "ans=$2"
	else
		gcd $2 $m
	fi
}

ans=0
while [[ true ]]; do
	read a b	
	if [[ -z $a || -z $b ]]; then
		break
	fi
	gcd $a $b
	echo "GCD is $ans"
done
echo "bye"
