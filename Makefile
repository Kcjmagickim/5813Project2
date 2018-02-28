#@file: MakeFile
#@brief: GNU Make imeplementation
#@author: John Kim
#@date: Feb 18th, 2018

include sources.mk

SRCS = memory.c tests.c

PPRO := $(SRCS:.c=.i)

OBJS := $(SRCS:.c=.o)

ASMS := $(SRCS:.c=.asm)

LDFLAGS = -lm

CFLAGS = -Wall	\
		-Werror	\
		-g 		\
		-O0		\
		-std=c99 

ifeq ($(PLATFORM),KL25z)
	CC = arm-none-eabi-gcc
	CFLAGS += -mcpu=cortex-m0plus	\
	-mfloat-abi=soft	\
	-march=armv6-m	\
	-mthumb	\
	-mfpu=fpv4-sp-d16		\
	--specs=nosys.specs

else ifeq ($(PLATFORM),BBB)
	CC = arm-linux-gnueabi-gcc
else
	CC = gcc
endif


arch_arm32.o: arch_arm32.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o arch_arm32.o src/arch_arm32.c

memory.o: memory.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o memory.o src/memory.c

data.o: data.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o data.o src/data.c

conversion.o: conversion.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o conversion.o src/conversion.c

port.o: port.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o port.o src/port.c

mocka.o: mocka.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o mocka.o src/mocka.c

.PHONY: clean
clean:
	rm -f *.o *~ *.asm *.i *.d project1.elf

.PHONY: unittests
unittests: memory.o conversion.o data.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o unittests src/mocka.c memory.o data.o conversion.o $(CMOCKA_LIBRARY) -lm
