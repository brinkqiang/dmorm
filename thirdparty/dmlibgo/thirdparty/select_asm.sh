#!/bin/bash

cd $1
work=`pwd`

cd $work/thirdparty/boost.context
test -f b2 || ./bootstrap.sh > /dev/null
obj=`./b2 -an --with-context link=static | grep "compile.asm" | awk '{print $2}' | grep $2`
obj_name=`basename $obj`
source=`echo $obj_name | cut -d\. -f1`.S
file=$work/thirdparty/boost.context/libs/context/src/asm/$source
cp $file $work/libgo/context
echo -n $work/libgo/context/$source
