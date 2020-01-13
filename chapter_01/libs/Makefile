CFLAGS = -Wall -O2
LDFLAGS = -L.
LDLIBS = -liops

clean:
	rm -rf static_iops dynamic_iops main.o iops.o libiops.a libiops.so

static: static_iops
dynamic: dynamic_iops

static_iops: main.o libiops.a
	cc -static $(LDFLAGS) -o static_iops main.o $(LDLIBS)

libiops.a: iops.c
	cc $(CFLAGS) -c iops.c
	ar rcs libiops.a iops.o

dynamic_iops: main.o libiops.so
	cc $(LDFLAGS) -o dynamic_iops main.o $(LDLIBS)

libiops.so: iops.c
	cc $(CFLAGS) -fPIC -c iops.c
	ld -G -o libiops.so iops.o
