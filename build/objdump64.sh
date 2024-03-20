#!/bin/bash

x86_64-elf-objdump -b binary -D $1 -m i386:x86-64 -z
