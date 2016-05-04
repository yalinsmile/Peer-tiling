#!/bin/sh

cd custom_opt
~/pluto_zyy/polycc mm.c --debug


~/primetile-0.3.0-pre/primetile --tilelevel=2 mm.pluto.cloog


./ac.sh
