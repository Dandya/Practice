#!/usr/bin/env bash

PathToInclude=/home/aleksandr/Gtest/include #Твой путь до папки include
PathToLib=/home/aleksandr/Gtest/build/lib #Твой путь до папки lib

Parameter1="$1"
Parameter2="$2"

if [ -z $Parameter1 ]
  then read -p "Enter the name of file: " nameFileIn
  else nameFileIn=$1
fi

nameFileObj=gtest.o

if [ -z $Parameter2 ]
  then nameFileOut=output
	else nameFileOut=$2
fi

if g++ -std=c++11 -pthread -I$PathToInclude -c -o $nameFileObj $nameFileIn
	then g++ -o $nameFileOut  $nameFileObj -L$PathToLib -lgtest -pthread 
fi
