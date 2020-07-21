TARGET = build/forage
CC = gcc
CFLAGS = -g -Wall -pedantic
OBJS = build/main.o build/window.o
GTKDEPS = `pkg-config --cflags --libs gtk+-3.0`

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(GTKDEPS)

build/main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c $(GTKDEPS) -o build/main.o

build/window.o: src/window.c
	$(CC) -c $(CFLAGS) src/window.c $(GTKDEPS) -o build/window.o

clean:
	rm -f build/*.o build/forage
