OBJS=build/main.o build/tag.o build/str.o
CC=gcc
CFLAGS=-c
LFLAGS=-lgumbo

htmltohipe: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

client:
	./htmltohipe data/hipe_calc.html > tmp.c
	$(CC) tmp.c -lhipe -o cli

clean:
	rm htmltohipe build/*.o tmp.c cli

ctags:
	myctags -R . /usr/include/gumbo.h
