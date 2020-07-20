forager: src/forager.c
	gcc `pkg-config --cflags gtk+-3.0` -o build/forager src/forager.c `pkg-config --libs gtk+-3.0`
