#!/bin/bash
set -e

if [ -z "$1" ]; then
	echo "usage: $0 destinationdir"
	exit 3
fi

dst="$1"

if ! [ -d "$dst" ]; then
	echo "Directory $dst doesn't exits."
	exit 2
fi

pushd "$dst" > /dev/null
dst=`pwd`
popd > /dev/null


cd `dirname $0` || true




# one is easy

for i in `seq 1 3`; do
	mkdir -p "$dst"/one/$i
	cp files/one/* "$dst"/one/$i/
done

# two looks nasty

for i in `seq 1 8`; do
	mkdir -p "$dst"/two/$i
	mkdir -p "$dst"/two/$i/asdf
	mkdir -p "$dst"/two/$i/meow
	mkdir -p "$dst"/two/$i/"meow meow"
done

find "$dst"/two -type d -print0 |xargs -0 -n1 cp -a -- files/two/*


# three is easier on the eyes, but has sha1 and md5 collisions

mkdir -p "$dst"/three

# i use git, can't keep them in uncompressed...
for i in files/three/*bz2; do
	bunzip2 -fk $i
done

for i in `seq 1 10`; do
	cp files/three/m1  "$dst"/three/$RANDOM$RANDOM$RANDOM
	cp files/three/m1b  "$dst"/three/$RANDOM$RANDOM$RANDOM
	cp files/three/m2  "$dst"/three/$RANDOM$RANDOM$RANDOM
	cp files/three/m2b  "$dst"/three/$RANDOM$RANDOM$RANDOM
	cp files/three/s1  "$dst"/three/$RANDOM$RANDOM$RANDOM
	cp files/three/s2  "$dst"/three/$RANDOM$RANDOM$RANDOM
done
