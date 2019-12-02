LDLIBS ?= -lcurl -ljansson
CFLAGS ?= -O2 -s -Wall -Wextra -std=c99 -pedantic

all: shaman
shaman: src/shaman.c src/weather.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) 

test: test/suite.c src/weather.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
