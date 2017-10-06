#!/bin/sh

flags=""
if [ ! -z $1 ]; then
	flags="MASTER=right"
fi

echo "Building with flags:" $flags

make -C ../../../../ ergodox_infinity-pm $flags
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing, Press enter key to continue"
read x
sudo ../../../../util/activate_wsl.sh && make -C ../../../../ ergodox_infinity-pm-dfu-util $flags

#make -C ../../../../ ergodox-infinity-pm MASTER=right
#if [ $? != 0 ]; then
#    exit 1
#fi
#echo "Flashing right hand, Press enter key to continue"
#read x
#sudo make -C ../../../../ ergodox-infinity-pm-dfu-util MASTER=right
