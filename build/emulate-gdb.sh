#!/bin/bash

qemu-system-x86_64 -s -S -drive file=pkos.img,format=raw -vga std
