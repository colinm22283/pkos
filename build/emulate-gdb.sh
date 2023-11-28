#!/bin/bash

qemu-system-i386 -s -S -drive file=pkos.img,format=raw -vga std
