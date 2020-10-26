#!/bin/bash
a=10
b=5
let a=$a+$b
echo "$a, $b"
a=10
b=5
let "a=$a+$b"
echo "$a, $b"
a=10
b=5
let "a=+b"
echo "$a, $b"
a=10
b=5
a+=$b
echo "$a, $b"
a=10
b=5
let "a = a + b"
echo "$a, $b"
