# Building danix

Requirements to build danix:
* GRUB Command-line Utils
* xorriso
* The Netwide Assembler
* binutils/coreutils (for linux)
* i686-elf utils (for mac)
* python3
* GNU Make
* QEMU

Supported Systems:
* macOS
* Linux-based Distros
* danix (in progress)

Common build errors:
* The `iso/init` directory does not exist.
* One of the requirements is not installed.


In order to build, just type:

	make

Two files result, `danix.elf` and `danix.iso`.

`danix.elf` is the kernel file, and `danix.iso` is a
bootable ISO image of the kernel file.

In order to run in QEMU, just type:

	make run

In order to run just the kernel in QEMU, just type:

	make kernel
