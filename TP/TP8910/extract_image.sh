#!/bin/bash


#  Extract 2 C files from a .bm image file :
#  image_bits_include.h 
#        définition des constates symboliques WIDTH HEIGTU BYTES et BYTES_PER_LINE
#  image_bits_content.c 
#        tableau de contenu décrivant les pixels
#

nom=`echo $1.bm | sed -e "s/\.bm\.bm/.bm/"`

if [ ! -s $nom ]; then
  echo "Le fichier image $1 est vide ou n'existe pas."
  exit 1
fi

if [ ! -r $nom ]; then
  echo "Le fichier image $1 n'est pas accessible en lecture."
  exit 1
fi

w=`grep "#define" $nom | grep "width"`
w=`echo $w | sed -e "s/^ *#define *//" | sed -e "s/width *//"`
w=`echo $w | sed -e "s/\(^[1-9][0-9]*\).*/\1/"`
ok=`echo $w |  grep "^[1-9][0-9]*" | wc -l`


if [ ! $ok -eq 1 ]; then
   echo "Erreur : #define width absent ou non conforme"
   exit 1
fi

h=`grep "#define" $nom | grep "height"`
h=`echo $h | sed -e "s/^ *#define *//" | sed -e "s/height *//"`
h=`echo $h | sed -e "s/\(^[1-9][0-9]*\).*/\1/"`
ok=`echo $h |  grep "^[1-9][0-9]*" | wc -l`

if [ ! $ok -eq 1 ]; then
   echo "Erreur : #define height absent ou non conforme"
   exit 1
fi

bytesperline=$(($w / 8))
bytes=$(( $bytesperline * $h ))

c_include="image_bits_include.h"

if ! echo "#define WIDTH $w" > $c_include 
then
   echo "Echec d'écriture de width dans $c_include"
   exit 1
fi

echo "#define HEIGHT $h" >> $c_include
echo "#define BYTES $bytes" >> $c_include
echo "#define BYTES_PER_LINE $bytesperline" >> $c_include

content="image_bits_content.c"
dollar='$'
cp $nom $content

# Edit in place image copy 
ex -c "1,/static.*bits/-1d" -c "s/^ *static *//" -c "wq" $content
ex -c "/#endif/d" -c "wq" $content

exit 0
