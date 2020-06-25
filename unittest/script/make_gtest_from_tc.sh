#!/bin/sh

# for cygwin

TESTMODELS=`find . -maxdepth 1 -type d -name "HA762*"`
OUTDIR=gtestcase_HA762
JSONPATH=template-gen
JSONFILE=RBAModel.json

mkdir -p $OUTDIR
for dir in $TESTMODELS;
do
    inputfiles=`find $dir -maxdepth 1 -name "*.tc"`
    for testname in $inputfiles;
    do
        python3 create_ut_prog.py $testname -o $OUTDIR -j "${dir}/${JSONPATH}/${JSONFILE}"
    done
done