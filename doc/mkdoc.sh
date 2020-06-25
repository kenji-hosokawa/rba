#!/bin/sh

WORKDIR=./work
TARGETDIR=../include/rba
DOXYGEN_JP=Doxygen_jp
DOXYGEN_EN=Doxygen_en
LOGO_FILE=denso_logo.png

if [ -d $WORKDIR ]; then
    /bin/rm -fr $WORKDIR
fi
mkdir $WORKDIR

worksrc=$WORKDIR/src
if [ -d $worksrc ]; then
    /bin/rm -fr $worksrc
fi
mkdir $worksrc

for hppfile in `ls $TARGETDIR | grep "\.hpp$"`; do
    cat $TARGETDIR/$hppfile | python3 ../script/conv_release.py | python3 ../script/remove_comment.py > $worksrc/$hppfile
done
/bin/rm -f $worksrc/RBAAnimation*.hpp
/bin/rm -f $worksrc/RBAPosition*.hpp
/bin/rm -f $worksrc/RBAPost*.hpp
/bin/rm -f $worksrc/RBAAbstractFactory*.hpp
/bin/rm -f $worksrc/RBAConstraint*
/bin/rm -f $worksrc/RBAAreaSet.hpp
/bin/rm -f $worksrc/RBASoundContentSet.hpp
/bin/rm -f $worksrc/RBAViewContentSet.hpp
/bin/rm -f $worksrc/RBAZoneSet.hpp

sed -e 's/^INPUT =.*$/INPUT = .\/src/' $DOXYGEN_JP > $WORKDIR/$DOXYGEN_JP
sed -e 's/^INPUT =.*$/INPUT = .\/src/' $DOXYGEN_EN > $WORKDIR/$DOXYGEN_EN

cd $WORKDIR
doxygen $DOXYGEN_JP
doxygen $DOXYGEN_EN

