#!/bin/sh

url=https://github.com/google/googletest.git
gittag=release-1.8.1
gtestdir=googletest/googletest

git clone -b $gittag $url
cd $gtestdir
cmake .
make

echo done
