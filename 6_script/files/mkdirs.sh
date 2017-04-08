#!/bin/bash

echo DO NOT RUN, IT BROKE srv05
exit 5


DST=/tmp/adsf
mkdir -p $DST


(while /bin/true ; do
	read usr
	if [ -z "$usr" ]; then
		break
	fi
	mkdir -v -p $DST/$usr
	cp -a skel $dst/$usr
	chown -R bin.bin $dst/$usr

done) <userlist
