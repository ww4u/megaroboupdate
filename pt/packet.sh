#!/bin/sh
tar czvf tmp.tar.gz ./demo/* ./update.txt ./update.xml ./*.mrh ./update.sh
./packet -c
rm tmp.tar.gz

