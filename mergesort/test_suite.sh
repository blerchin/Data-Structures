#! /bin/bash

trial_file="trial.csv"

if ! [ -e "mergesort" ]
then
	make
fi
if ! [ -e "$trial_file" ]
then
	echo -e "d , m, time" > "$trial_file"
fi
# 2^d threads
for d in {0..6}
do
# problem size: 8*m
	for m in 1 10 20 30 40 50 60 70 80 90 100
	do
		echo -n "$d , $m , " >> "$trial_file"
		./mergesort  $d $( expr $m \* 2000 )  >> "$trial_file"
	done

done

