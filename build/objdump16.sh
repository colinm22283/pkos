#!/bin/bash

i686-elf-objdump -b binary -D pkos.img -m i386 -Maddr16,data16 -z
