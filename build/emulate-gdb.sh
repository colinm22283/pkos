#!/bin/bash

qemu-system-x86_64 -no-reboot -s -S -drive file=pkos.img,format=raw -vga std -m 6G & x86_64-elf-gdb
