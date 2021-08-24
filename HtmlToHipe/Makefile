OBJS=build/main.o build/tag.o
CC=gcc
CFLAGS=-c
LFLAGS=-lgumbo

htmltohipe: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm htmltohipe build/*.o

ctags:
	myctags -R . /usr/include/gumbo.h
