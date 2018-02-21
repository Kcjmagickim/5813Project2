#@file: MakeFile
#@brief: GNU Make imeplementation
#@author: John Kim
#@date: Feb 18th, 2018

include sources.mk

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

memory.o: memory.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o memory.o src/memory.c

conversion.o: conversion.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o conversion.o src/conversion.c

mocka.o: mocka.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o mocka.o src/mocka.c

.PHONY: clean
clean:
	rm -f *.o *~ *.asm *.i *.d project1.elf

.PHONY: unittests
unittests: memory.o conversion.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o unittests src/mocka.c memory.o conversion.o $(CMOCKA_LIBRARY) -lm
