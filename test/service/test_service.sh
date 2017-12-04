#!/bin/bash

for ((i=1; i<=1000000000000; i++))
 do
	 {
	 	echo $i
	 	nc 127.0.0.1 3000
 	 }&
 done

