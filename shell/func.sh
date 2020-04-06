#!/bin/bash
num1=$1
num2=$2
func() {
    echo "func() here"
    num1=$1
    num2=$2
    echo "$num1 $num2"
    return $((num1+num2))
}

echo $1 $2
func 5 6
echo "$?"
