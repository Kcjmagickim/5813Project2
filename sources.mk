#@file: sources.mk
#@brief: Includes common CFLAGS, paths, and source files
#@author: John Kim
#@date: Feb 10th, 2018

vpath %.c -I src
vpath %.h -I include

INCLUDES = 	-I./include/CMSIS	\
			-I./include/common	\
			-I./include			\
			-I./3rd-party/build-Debug/include

CMOCKA_LIBRARY = 3rd-party/build-Debug/lib/libcmocka.a

