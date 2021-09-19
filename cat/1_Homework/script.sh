#!/bin/bash 
olsIFS=$IFS
IFS=$'\n'
LIBS="$(find ./ -depth  -name *.so)"
echo $LIBS
IFS=$oldIFS