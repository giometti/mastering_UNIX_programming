OS := $(shell uname)

TARGETS += stat
TARGETS += getugid
TARGETS += access
TARGETS += link unlink
TARGETS += atime

include ../rules.make

ifneq ($(filter Linux FreeBSD,${OS}),)
CFLAGS_getugid := -D_HAS_GETRESUID # do NOT remove the space at the end!
endif
