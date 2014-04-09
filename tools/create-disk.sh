#!/bin/bash
set -e
function usage {
  echo "usage: $0 disk-name"
}

if [ -z $1 ] ; then
  usage
  exit 1
fi

if [ -z $SUDO_USER ] ; then
  SUDO_USER=$USER
fi

if [[ $EUID -ne 0 ]] ; then
  echo "$0: must be run as root"
  exit 1
fi

DISK_NAME=$1

dd if=/dev/zero of=$DISK_NAME ibs=1024 count=$((60*1024))
chown $SUDO_USER $DISK_NAME

# Create a single partition for the disk.
# n - create new partition
# p - primary partition
# 1 - partition number
# 2048 - partition start at 1MB (2048th segment)
# <CR> - default end
# w - write partition table and quit
fdisk $DISK_NAME << EOF
n
p
1
2048

w
EOF
set +e
losetup -d /dev/loop0
losetup -d /dev/loop1
set -e
losetup /dev/loop0 $DISK_NAME
losetup /dev/loop1 $DISK_NAME -o $((2048*512))
mkdir -p mnt
mkfs.ext2 /dev/loop1
mount /dev/loop1 mnt
echo 'Installing grub'
# TODO(koz): Is elf needed here?
grub-install --root-directory=mnt --no-floppy --modules="normal ext2 part_msdos multiboot biosdisk elf" /dev/loop0
chown -R $SUDO_USER mnt
sync
