LDLIBS = -lcurl -ljansson
all: shaman
shaman: src/shaman.c src/weather.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
