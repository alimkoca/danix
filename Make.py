#!/usr/local/bin/python3

import subprocess as sub
import os
import shlex
import json
import platform as plat

sys = os.sys

GITHUB = "llamaking136/danix"

CONFIG_GLOBAL = json.loads(open("CONFIG.json", "r").read())

try:
    CONFIG = CONFIG_GLOBAL[plat.system()]
except KeyError:
    print("error: configuration for system " + plat.system() + " not found, stopping", file = sys.stderr)
    print("if you think this is an issue, create a new issue at my GitHub: https://github.com/" + GITHUB, file = sys.stderr)
    exit(2)

def system(*args):
    print(combine(args))
    return os.system(combine(args))

def sys_run(*args, ignore = False):
    if system(args) and not ignore:
        print("error: sys_run returned false", file = os.sys.stderr)
        exit(1)

def not_found(filename):
    print("error: file '" + filename + "' not found, stopping", file = os.sys.stderr)
    exit(1)

def fix_out(lst):
    amnt = 0
    for i in range(len(lst)):
        if lst[i + amnt] == "":
            del lst[i + amnt]
            amnt += 1
    return lst

def combine(*args):
    # return " ".join(args)
    result = ""
    for i in args[-1]:
        # result += i + " "
        for ii in i:
            result += ii + " "
    return result

def change_path(orig, targ):
    path = orig.split("/")[-1]
    return targ + "/" + path

def get_out(args):
    args = shlex.split(args)
    return fix_out(sub.Popen(args, stdout = sub.PIPE).communicate()[0].decode("utf-8").split("\n"))

def replace_ext(one, two):
    split = one.split(".")
    del split[-1]
    if len(split) == 0:
        raise Exception
    split.append(two)
    return ".".join(split)

CC = CONFIG["CC"]
CC_ARGS = "-m32 -c -nostdlib -nostdinc -nostartfiles -Iinclude -Wno-builtin-declaration-mismatch"
# CXX = CONFIG["CXX"]
# CXX_ARGS = CC_ARGS + " -std=c++17"
NASM = CONFIG["NASM"]
NASM_ARGS = "-felf32"
LD = CONFIG["LD"]
LD_ARGS = "-T linker.ld -m elf_i386"

TARGET = "danix.elf"
ISO = "danix.iso"

KERNEL = "."

# SOURCE = get_out("find . -name '*.asm'")

ASSEMBLY = get_out("find " + KERNEL + " \\( -name '*.asm' -o -name '*.s' \\)")
# ASSEMBLY.insert(0, "boot/boot.asm")
# print(ASSEMBLY)
CFILES = get_out("find " + KERNEL + " -name '*.c'")
CPPFILES = get_out("find " + KERNEL + " -name '*.cpp'")
OUTPUTS = ""
for i in ASSEMBLY:
    OUTPUTS += change_path(replace_ext(i, "o"), "output") + " "
for i in CFILES:
    OUTPUTS += change_path(replace_ext(i, "o"), "output") + " "
# for i in CPPFILES:
#     OUTPUTS += change_path(replace_ext(i, "o"), "output") + " "

def make_main():
    if not os.path.exists("iso/init"):
        os.mkdir("iso/init")

    if not os.path.exists("output"):
        os.mkdir("output")

    # if not os.path.exists("boot/boot.o"):
        # print("compiling bootloader...")
        # sys_run(NASM, NASM_ARGS, "-o", "boot/boot.o", "boot/boot.asm")

    # if not os.path.exists(TARGET):
        # print("compiling all C files...")
        # for i in SOURCE:
        #     sys_run(CC, CC_ARGS, "-o", change_path(replace_ext(i, "o"), "output"), i)
        # print("linking all object files...")
        # sys_run(LD, LD_ARGS, "-o", TARGET, OUTPUTS, "boot/boot.o")

    if not os.path.exists(TARGET):
        print("compiling all assembly files...")
        for i in ASSEMBLY:
            sys_run(NASM, NASM_ARGS, "-o", change_path(replace_ext(i, "o"), "output"), i)
        print("compiling all c files...")
        for i in CFILES:
            sys_run(CC, CC_ARGS, "-o", change_path(replace_ext(i, "o"), "output"), i)
        # print("compiling all c++ files...")
        # for i in CPPFILES:
        #     sys_run(CXX, CXX_ARGS, "-o", change_path(replace_ext(i, "o"), "output"), i)
        print("linking all object files...")
        sys_run(LD, LD_ARGS, "-o", TARGET, OUTPUTS)
        sys_run("cp", TARGET, "iso/init/boot.bin")
        print("creating grub iso...")
        sys_run("grub-mkrescue -o", ISO, "./iso")

def make_clean():
    if os.path.exists("output"):
        sys_run("rm -r output")

    if os.path.exists(TARGET):
        sys_run("rm", TARGET)

    if os.path.exists(ISO):
        sys_run("rm", ISO)

    if os.path.exists("iso/init/boot.bin"):
        sys_run("rm iso/init/boot.bin")
    
    # else:
    #     print("error: nothing to do!", file = os.sys.stderr)
    #     exit(1)

def make_run():
    if os.path.exists(ISO):
        sys_run("qemu-system-i386 -soundhw pcspk -cdrom", ISO, ignore = True)
    elif os.path.exists(TARGET):
        sys_run("qemu-system-i386 -soundhw pcspk -kernel", TARGET, ignore = True)
    else:
        not_found(TARGET)

def make_kernel():
    if os.path.exists(TARGET):
        sys_run("qemu-system-i386 -soundhw pcspk -kernel", TARGET, ignore = True)

if len(os.sys.argv) <= 1:
    make_main()
else:
    if os.sys.argv[-1] == "clean":
        make_clean()
    elif os.sys.argv[-1] == "run":
        make_run()
    elif os.sys.argv[-1] == "kernel":
        make_kernel()
    else:
        print("error: unknown option: " + os.sys.argv[-1], file = os.sys.stderr)
        exit(1)
