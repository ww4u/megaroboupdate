#!/bin/sh
cd /media/usb0
tar -xzvf mrh.tar.gz
cp demo /home/megarobo/MCT/MRX-T4/ -rf
cp update.txt /home/megarobo/MCT/MRX-T4/update.txt
cp update.xml /home/megarobo/MCT/MRX-T4/update.xml
cp update.sh /home/megarobo/MCT/MRX-T4/update.sh
mv *.mrh mrh.dat
