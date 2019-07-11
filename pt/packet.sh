#!/bin/sh
tar czvf tmp.tar.gz ./demo/* ./update.txt ./update.xml ./*.mrh
./packet -c
rm tmp.tar.gz

