#!/bin/sh

#if [ $# -ne 3 ];then

#echo "usage: argument 1:IP_Address 2:Server_PORT 3:Temp_PATH"

#exit 1

#fi
#IP=$1

#PORT=$2

#DIRT=$3

#TEMP2=""

#while read line;do
   
#  echo  "$line"
 
#   TEMP="$line"

#   TEMP2=$TEMP2$TEMP

#done < tvdevicedesc2.xml


echo "Change values in tvdevicedesc2.xml..."



#sed "s/#pre.*#pre end/#pre$TEMP22#pre end/" tvdevicedesc.xml > tvdevicedesc2.xml
sed '/#pragma scop/,/#pragma endscop/d' mm.c > mm1.c
sed '/#pragma zyl/r mm.primetile.c' mm1.c > mm2.c

echo "Done."
