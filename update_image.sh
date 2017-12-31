#!/usr/bin/env bash

sudo losetup /dev/loop0 floppy.img 
sudo mount /dev/loop0 mnt
cp test.mk.out mnt/kernel
sudo umount /dev/loop0
sudo losetup -d /dev/loop0
