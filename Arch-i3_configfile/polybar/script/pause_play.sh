#! /usr/bin/bash

statu=`mpc | grep -o playing`

if [ -z $statu ]
then
    mpc play
else
    mpc pause
fi
