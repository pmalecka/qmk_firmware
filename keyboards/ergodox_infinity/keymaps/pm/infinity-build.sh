#!/bin/sh

flags=""
if [ ! -z $1 ]; then
	flags="MASTER=right"
fi

echo "Flags:" $flags

make -C ../../../../ ergodox_infinity:pm $flags
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing left hand, Press enter key to continue"
read x
../../../../util/activate_wsl.sh && make -C ../../../../ ergodox_infinity:pm:dfu-util $flags


#make -C ../../../../ ergodox_infinity:pm MASTER=right
#if [ $? != 0 ]; then
#    exit 1
#fi
#echo "Flashing right hand, Press enter key to continue"
#read x
#../../../../util/activate_wsl.sh && make -C ../../../../ ergodox_infinity:pm:dfu-util MASTER=right
