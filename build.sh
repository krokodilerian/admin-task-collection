#!/bin/bash

if [ -z "$1" ]; then
	echo usage: $0 outdir
	exit 2
fi

if ! [ -d "$1" ]; then
	mkdir -p "$1" || exit 4
fi

pushd "$1" > /dev/null
dst=`pwd`
popd > /dev/null

dstd=$dst/tasks

mkdir -p $dstd

rm -f $dst/*

for i in [0-9]*_*; do
	echo "Processing $i..."
	if ! [ -x "$i/build.sh" ]; then
		echo Skipping $i, no build.sh found
		continue
	fi
	(
		cd "$i"
		mkdir -p $dstd/$i
		./build.sh $dstd/$i
		cp task $dstd/$i/README.md
		cat >> $dst/full.md <<EOF

\newpage

## $i

### Task

`cat task`

### Solution

`cat solution`

### Rationale

`cat rationale`


EOF
	)
	echo "Finished $i..."
done

pandoc -f markdown -t latex   -V geometry:margin=1in $dst/full.md --toc -o $dst/full.pdf
(
	cd $dst
	tar cfj taskfile tasks
)

