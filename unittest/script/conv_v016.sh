#!/bin/sh

JSONPATH=org/json
JSONFILE=RBAModel.json
INPUTDIR=./org/input
DSTDIR=gen/src
OBJLIST=__objlist
MAKEFILE=__Makefile

function generate()
{
    name=$1
    inputdir=$2
    inputfiles=`find $inputdir -name "*.txt"`
    python3 script/generate_testcase2.py $name $DSTDIR $inputfiles
}

if [ -f $OBJLIST ]; then
    rm $OBJLIST
fi

#
# Main routine
#

testname_array=()
for jsonpath in `find $JSONPATH -name $JSONFILE`; do
    basename=`echo $jsonpath | sed -e 's/^.*\/json\///;s/\/.*$//'`
    testname="Test"${basename}

    echo $testname
    testname_array+=( $testname )

    # Copy JSON file
    cp $jsonpath $DSTDIR/${testname}.json
    chmod -x $DSTDIR/${testname}.json

    # Generate TestXXX.cpp/hpp
    generate $basename $INPUTDIR/${basename}

    # Add objlist
    echo gen/obj/${testname}.o \\ >> $OBJLIST
done

#
# Generate SRCS,OBJS,rule part of Makefile
#

echo SRCS = \\ > $MAKEFILE
for testname in ${testname_array[@]}; do
    echo src/${testname}.cpp  \\ >> $MAKEFILE
done
echo >> $MAKEFILE

echo OBJS = \\ >> $MAKEFILE
for testname in ${testname_array[@]}; do
    echo obj/${testname}.o \\ >> $MAKEFILE
done
echo >> $MAKEFILE

for testname in ${testname_array[@]}; do
    echo obj/${testname}.o: src/${testname}.cpp >> $MAKEFILE
    echo "	\$(CXX) -c \$(CXXFLAGS) \$< \$(INCLUDES) -o \$@" >> $MAKEFILE
    echo >> $MAKEFILE
done
