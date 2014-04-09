#!/bin/bash

set -e
set -x
make kernel
cp boot/grub.cfg mnt/boot/grub
cp kernel mnt/boot/kernel
sync
