OS := $(shell uname)

all: $(TARGETS)

clean:
	rm -rf $(TARGETS) *.o *.so

% : %.c
	cc $(CFLAGS_$*)-Wall -O2 $(CFLAGS) -o $* $^ $(LDFLAGS_$*)

lib%.so : %.c
	cc $(CFLAGS_$*)-Wall -O2 $(CFLAGS) -fPIC -c $^
	ld -G -o lib$*.so ${^:.c=.o}
