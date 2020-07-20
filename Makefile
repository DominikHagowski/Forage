forage: src/forage.c
	gcc `pkg-config --cflags gtk+-3.0` -o build/forage src/forage.c `pkg-config --libs gtk+-3.0`
