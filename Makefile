SRCDIR = src
OBJDIR = build

CC = gcc
CFLAGS = -g -Wall -pedantic
GTKDEPS = `pkg-config --cflags --libs gtk+-3.0`

TARGET = $(OBJDIR)/forage
OBJS = $(OBJDIR)/main.o $(OBJDIR)/window.o


all: $(OBJS) | $(OBJDIR)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(GTKDEPS)

$(OBJDIR)/main.o: $(SRCDIR)/main.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/main.c $(GTKDEPS) -o $(OBJDIR)/main.o

$(OBJDIR)/window.o: $(SRCDIR)/window.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/window.c $(GTKDEPS) -o $(OBJDIR)/window.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/forage
