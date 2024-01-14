#!/bin/bash

OBJECT_FILES=$(find obj -type f -name $1)

if ($OBJECT_FILES -eq "") then
  echo "Object not found!"
fi

echo "Object dump of \"$OBJECT_FILES\""

x86_64-elf-objdump -D $OBJECT_FILES