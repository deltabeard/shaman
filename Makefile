LDLIBS ?= -lcurl -ljansson
CFLAGS ?= -O2 -s

# Required CFLAGS
CFLAGS += -Wall -Wextra -std=c99 -pedantic

all: shaman test
shaman: src/shaman.c src/weather.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
test: test/suite.c src/weather.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) 

src/weather.o: src/weather.c src/weather.h

clean:
	$(RM) shaman test src/weather.o
