#!/bin/bash
var=$1
name=`echo ${var%%.*}`
header="$name.h"
cpp="$name.cpp"
obj="$name.o"

echo "gen code"
echo $header
echo $cpp

./gen $1 > $cpp 
grep '^void' $cpp | while read LINE; do echo "$LINE;"; done > $header

cp $cpp ../
cp $header ../

echo "gen Makefile"
makefile="../Makefile"
>$makefile
first_line=`head -n 1 Makefile`
echo "$first_line $obj" >> $makefile
second_line=`head -n 2 Makefile | tail -n 1`
echo -e "$second_line $obj" >> $makefile 
sum=`wc -l Makefile | awk '{print $1}'`
clean=$(($sum - 3))
sed -n "3, ${clean}p" Makefile >> $makefile 
echo -e "$obj: $cpp $header public.h\n\tg++ -c $cpp" >> $makefile 
tail -n 3 Makefile >> $makefile 

#cp $makefile Makefile
