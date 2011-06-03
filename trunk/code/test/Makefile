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
# GCCDIR = ~/gnu/local/decstation-ultrix/bin/
# LDFLAGS = -T script -N
# ASFLAGS = -mips
# CPPFLAGS = $(INCDIR)
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


all: halt shell matmult sort consoleA consoleB test createfile \
	main lower middle higher highest\
	ping pong scheduler1\

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

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

consoleA.o: consoleA.c
	$(CC) $(CFLAGS) -c consoleA.c
consoleA: consoleA.o start.o
	$(LD) $(LDFLAGS) start.o consoleA.o -o consoleA.coff
	../bin/coff2noff consoleA.coff consoleA

consoleB.o: consoleB.c
	$(CC) $(CFLAGS) -c consoleB.c
consoleB: consoleB.o start.o
	$(LD) $(LDFLAGS) start.o consoleB.o -o consoleB.coff
	../bin/coff2noff consoleB.coff consoleB

test.o: test.c
	$(CC) $(CFLAGS) -c test.c
test: test.o start.o
	$(LD) $(LDFLAGS) start.o test.o -o test.coff
	../bin/coff2noff test.coff test\

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
main: main.o start.o
	$(LD) $(LDFLAGS) start.o main.o -o main.coff
	../bin/coff2noff main.coff main
lower.o: lower.c
	$(CC) $(CFLAGS) -c lower.c
lower: lower.o start.o
	$(LD) $(LDFLAGS) start.o lower.o -o lower.coff
	../bin/coff2noff lower.coff lower
middle.o: middle.c
	$(CC) $(CFLAGS) -c middle.c
middle: middle.o start.o
	$(LD) $(LDFLAGS) start.o middle.o -o middle.coff
	../bin/coff2noff middle.coff middle
higher.o: higher.c
	$(CC) $(CFLAGS) -c higher.c
higher: higher.o start.o
	$(LD) $(LDFLAGS) start.o higher.o -o higher.coff
	../bin/coff2noff higher.coff higher
highest.o: highest.c
	$(CC) $(CFLAGS) -c highest.c
highest: highest.o start.o
	$(LD) $(LDFLAGS) start.o highest.o -o highest.coff
	../bin/coff2noff highest.coff highest

ping.o: ping.c
	$(CC) $(CFLAGS) -c ping.c
ping: ping.o start.o
	$(LD) $(LDFLAGS) start.o ping.o -o ping.coff
	../bin/coff2noff ping.coff ping

pong.o: pong.c
	$(CC) $(CFLAGS) -c pong.c
pong: pong.o start.o
	$(LD) $(LDFLAGS) start.o pong.o -o pong.coff
	../bin/coff2noff pong.coff pong

scheduler1.o: scheduler1.c
	$(CC) $(CFLAGS) -c scheduler1.c
scheduler1: scheduler1.o start.o
	$(LD) $(LDFLAGS) start.o scheduler1.o -o scheduler1.coff
	../bin/coff2noff scheduler1.coff scheduler1

