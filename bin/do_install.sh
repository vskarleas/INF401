#/bin/bash

FILES=`ls . | grep -v do_install.sh`
echo $FILES

cp -f $FILES ../../bin

for f in $FILES
do
  chgrp dlst-ens ../../bin/$f
done
