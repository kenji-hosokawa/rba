#!/bin/bash
# Ubuntuのターミナルではこのファイルを$ bash script/generate_src.sh で実行する。(shで実行すると構文エラーになる)

orgdir=./testmodel
dstdir=./gen
templatedir=./template
objlist=$dstdir/obj/objlist

dst_src=$dstdir/src
filelist=$dst_src/files

# check dirrectory
if [ ! -d $orgdir ]; then
    echo "$orgdir/: No such directory"
    exit
fi
if [ ! -d $dst_src ]; then
    mkdir -p $dst_src
fi

# check org directory
function generate()
{
    if [ -f $filelist ]; then
      /bin/rm -f $filelist
    fi
    echo Convert testmodel to testcase
    for dir in `ls $orgdir`; do
      inputdir=$orgdir/$dir
      RES=`find $inputdir -name "*.cpp" 2>/dev/null`
      if [ $? -ne 0 ]; then
        echo "予期せぬエラー"
      elif [ -z "$RES" ]; then
        input_files=`find $inputdir -name "*.txt"`
        python3 script/generate_testcase.py $dir $dst_src $input_files
        echo Test${dir}.cpp >> $filelist
      else
        echo "EXCEPTION: copy the file created by hand code:"$dir
        fromfile=`find $inputdir -name "*.cpp"`
        `cp $fromfile gen/src/`
        echo `basename $fromfile` >> $filelist
        fromfile=`find $inputdir -name "*.hpp"`
        `cp $fromfile gen/src/`
        fromfiles=`find $inputdir -name "*.json"`
        for fromfile in $fromfiles; do
          if [[ `basename $fromfile` = *$dir.json ]]; then
            `cp $fromfile gen/src/`
          fi
        done
      fi
    done
}

function make_makefile()
{
    pushd $dstdir > /dev/null
    if [ -f Makefile ]; then
      /bin/rm Makefile
    fi
    files=`cat src/files`
    
    cat << 'EOF' > Makefile
#
# Makefile
#

GTEST_ROOT = ../googletest/googletest
RBA_ROOT = ../..
CXX = g++
LD = g++
CXXFLAGS = -Wall -g -std=c++14
LDFLAGS =
SRCS =  \
EOF

    for filename in ${files[@]}; do
      echo "src/$filename \\" >> Makefile
    done
    echo >> Makefile

    echo "OBJS = \\" >> Makefile
    for filename in ${files[@]}; do
      objname=`echo $filename | sed -e 's/\.cpp$/.o/'`
      echo "obj/$objname \\" >> Makefile
    done
    echo >> Makefile

    echo "INCLUDES = -I\$(RBA_ROOT)/include/rba -I\$(GTEST_ROOT)/include -I\$(RBA_ROOT)/src -I\$(RBA_ROOT)/include/model" >> Makefile
    echo "LIBS = " >> Makefile
    echo "TARGET = \$(OBJS)" >> Makefile
    echo >> Makefile
    echo "all: \$(TARGET)" >> Makefile
    echo >> Makefile

    for filename in ${files[@]}; do
      objname=`echo $filename | sed -e 's/\.cpp$/.o/'`
      echo "obj/$objname: src/$filename" >> Makefile
      echo "	\$(CXX) -c \$(CXXFLAGS) \$< \$(INCLUDES) -o \$@" >> Makefile
      echo >> Makefile
    done
    echo >> Makefile

    echo "clean:" >> Makefile
    echo "	-rm -fr \$(TARGET) *~" >> Makefile

    popd > /dev/null
}

function make_objlist()
{
    if [ ! -d gen/obj ]; then
      mkdir -p gen/obj
    fi
    if [ -f $objlist ]; then
      /bin/rm -f $objlist
    fi

    echo "GENOBJS = \\" > $objlist
    for filename in `cat $filelist`; do
      objpath=`echo "gen/obj/"$filename | sed -e 's/\.cpp$/.o/'`
      echo $objpath \\ >> $objlist
    done
    echo >> $objlist
    /bin/rm -f $filelist

}

generate
make_makefile
make_objlist

# end of file
