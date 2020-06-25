#!/bin/sh

SRCPATH=gen/src.org
DSTPATH=gen/src.dst
PROGPATH=script/utconv.py

if [ ! -d $DSTPATH ]; then
    mkdir $DSTPATH
fi

for infile in `ls $SRCPATH/*.cpp`; do
    filename=`echo $infile | sed -e 's/^.*\///'`
    outfile=$DSTPATH/$filename
    echo $infile
    python3 $PROGPATH $infile > $outfile
done

for infile in `ls $SRCPATH/*.cpp`; do
    echo $infile
    cp -f $infile $outfile
done

# end of file
