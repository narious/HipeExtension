OBJS=build/main.o build/html.o build/str.o
CC=gcc
CFLAGS=-c
LFLAGS=-lgumbo

htmltohipe: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm htmltohipe build/*.o tmp.c cli

