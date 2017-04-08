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



cp files/gen.c $dst/
