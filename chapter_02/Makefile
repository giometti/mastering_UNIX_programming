OS := $(shell uname)

TARGETS += open
TARGETS += read
TARGETS += lseek
TARGETS += iospeed
TARGETS += async sync
ifneq (${OS}, FreeBSD)
TARGETS += dsync
endif

OBJECTS += wrappers.o

include ../rules.make

read: wrappers.o
async dsync sync: wrappers.o
