# Building DANIX

Requirements to build danix:
* GRUB Command-line Utils
* xorriso
* The Netwide Assembler
* binutils/coreutils (for linux)
* i686-elf utils (for mac)
* python3
* GNU Make
* QEMU (optional)

Supported Systems:
* macOS
* Linux-based Distros
* DANIX (in progress)
* Windows (kind-of)

Common build errors:
* The `iso/init` directory does not exist.
* One of the requirements is not installed.


## Note for Windows Builders!
You'll want to use the Windows Subsystem for Linux because the build file doesn't support Windows.
Support might come in the future.


For your building system, edit the `CONFIG.json` file to your compiler
specifications.

In order to build, just type:

	make

Two files result, `danix.elf` and `danix.iso`.

`danix.elf` is the kernel file, and `danix.iso` is a
bootable ISO image of the kernel file.

In order to run in QEMU, just type:

	make run

In order to run just the kernel in QEMU, just type:

	make kernel
