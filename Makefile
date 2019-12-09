LDLIBS ?= -lcurl -ljansson -lm
OPT ?= -O2 -s

# Test always has debugging enabled.
shaman-test: OPT = -Og -g3

# Use the Openweathermap API key if defined as an environment variable.
ifdef OWMAPIKEY
CFLAGS += -DOWMAPIKEY=\"$(OWMAPIKEY)\"
endif

# Required CFLAGS
CFLAGS += -Wall -Wextra -std=c99 -pedantic

all: shaman shaman-test
shaman: src/shaman.c src/weather.o
	$(CC) $(CFLAGS) $(OPT) $(LDFLAGS) -o $@ $^ $(LDLIBS)
shaman-test: test/suite.c src/weather.o
	$(CC) $(CFLAGS) $(OPT) $(LDFLAGS) -o $@ $^ $(LDLIBS)

src/weather.o: src/weather.c src/weather.h

clean:
	$(RM) shaman test src/weather.o
