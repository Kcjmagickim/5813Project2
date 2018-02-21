#@file: sources.mk
#@brief: Includes common CFLAGS, paths, and source files
#@author: John Kim
#@date: Feb 10th, 2018

vpath %.c -I src
vpath %.h -I include


INCLUDES = 	-I./include/	\
			-I./3rd-party/build-Debug/include

CMOCKA_LIBRARY = 3rd-party/build-Debug/lib/libcmocka.a

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
