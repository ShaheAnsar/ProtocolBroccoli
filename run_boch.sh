#!/usr/bin/env bash

sudo /sbin/losetup /dev/loop0 floppy.img
bochs_local
sudo /sbin/losetup -d /dev/loop0
