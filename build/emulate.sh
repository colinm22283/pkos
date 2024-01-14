#!/bin/bash

qemu-system-x86_64 -no-reboot -drive file=pkos.img,format=raw -vga std -d cpu_reset
