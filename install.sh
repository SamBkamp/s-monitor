#!/bin/bash

cwd=$(pwd)
if [ "$1" = "" ]; then
    echo "Please supply the DocumentRoot of your apache install"
    exit 1
fi


sudo ln -sf  $cwd"/smonitor" $1
