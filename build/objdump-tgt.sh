#!/bin/bash

OBJECT_FILES=$(find obj -type f -name $1)

echo "Object dump of \"$OBJECT_FILES\""

i686-elf-objdump -D $OBJECT_FILES