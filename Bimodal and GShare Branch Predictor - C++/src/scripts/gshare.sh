#!/bin/bash

m=7
n=0

while [ $m -le 20 ]; do
	while [ $n -le $m ]; do
		./sim gshare $m $n perl_trace.txt
		((n++))
	done
	n=0
	((m++))
done  
