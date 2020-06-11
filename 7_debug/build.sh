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


gcc -Wall -O0 -static files/a.c -o $dst/a
gcc -Wall -O0 -static files/b.c -o $dst/b
