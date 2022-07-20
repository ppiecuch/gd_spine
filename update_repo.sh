#!/bin/bash

set -e

if [ -d /tmp/spine-runtimes ]; then
	(cd /tmp/spine-runtimes; git pull)
else
	git clone --depth=1 --recursive --no-single-branch https://github.com/EsotericSoftware/spine-runtimes.git /tmp/spine-runtimes
fi

dt=$(date +"%d_%m_%Y")

diff="spine-${dt}.diff"

[ -f $diff ] && rm $diff

if [ -d spine-cpp ]; then
	diff -Nuar -x '*.o' -x '*.obj' /tmp/spine-runtimes/spine-cpp/spine-cpp spine-cpp > $diff
	rm -rf spine-cpp
fi

if [ -e config.py ]; then
	count=0
	files=$(cd /tmp/spine-runtimes/spine-godot/spine_godot/ && find . -type f | xargs)
	for f in $files; do
		fn="/tmp/spine-runtimes/spine-godot/spine_godot/$f"
		diff -Nuar $fn $f >> $diff || true
		rm $f
		count=$((count+1))
	done
	find . -type d -not -path '.' -exec rmdir "{}" \; || true
	echo "*** checked $count files"
	echo "*** content of the directory:"
	ls -l | grep -v '.o'
fi

echo "*** copy runtime ..."
cp -r /tmp/spine-runtimes/spine-cpp/spine-cpp .
echo "*** copy module ..."
cp -r /tmp/spine-runtimes/spine-godot/spine_godot/* .

if [ -f $diff ]; then
	echo "*** patching with changes ..."
	patch < $diff
	rm $diff
fi

rm -rf /tmp/spine-runtimes
