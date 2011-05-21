# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../bin/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../bin/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult testMulti sort createfile ReadInt PrintInt TestInt TestChar TestString ASCII help

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

testMulti.o: testMulti.c
	$(CC) $(CFLAGS) -c testMulti.c
testMulti: testMulti.o start.o
	$(LD) $(LDFLAGS) start.o testMulti.o -o testMulti.coff
	../bin/coff2noff testMulti.coff testMulti

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile
	
ReadInt.o: ReadInt.c
	$(CC) $(CFLAGS) -c ReadInt.c
ReadInt: ReadInt.o start.o
	$(LD) $(LDFLAGS) start.o ReadInt.o -o ReadInt.coff
	../bin/coff2noff ReadInt.coff ReadInt

PrintInt.o: PrintInt.c
	$(CC) $(CFLAGS) -c PrintInt.c
PrintInt: PrintInt.o start.o
	$(LD) $(LDFLAGS) start.o PrintInt.o -o PrintInt.coff
	../bin/coff2noff PrintInt.coff PrintInt

	
TestInt.o: TestInt.c
	$(CC) $(CFLAGS) -c TestInt.c
TestInt: TestInt.o start.o
	$(LD) $(LDFLAGS) start.o TestInt.o -o TestInt.coff
	../bin/coff2noff TestInt.coff TestInt

TestChar.o: TestChar.c
	$(CC) $(CFLAGS) -c TestChar.c
TestChar: TestChar.o start.o
	$(LD) $(LDFLAGS) start.o TestChar.o -o TestChar.coff
	../bin/coff2noff TestChar.coff TestChar
	
TestString.o: TestString.c
	$(CC) $(CFLAGS) -c TestString.c
TestString: TestString.o start.o
	$(LD) $(LDFLAGS) start.o TestString.o -o TestString.coff
	../bin/coff2noff TestString.coff TestString
	
help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

ASCII.o: ASCII.c
	$(CC) $(CFLAGS) -c ASCII.c
ASCII: ASCII.o start.o
	$(LD) $(LDFLAGS) start.o ASCII.o -o ASCII.coff
	../bin/coff2noff ASCII.coff ASCII


