#!/bin/bash
NAME_FILE="$(pwd)/libs.txt"
function search
{
    for dir in $(ls -d */)
    do
        echo $dir
        cd $dir 
        search $dir 
    done
    echo "$(find  $(pwd)/*.so)" >> $NAME_FILE
    cd ../
}

olsIFS=$IFS
IFS=$'\n'
search ./
IFS=$oldIFS
return 0
