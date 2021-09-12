htmltohipe_location = ../htmltohipe
CC = gcc
CFLAGS = -lhipe
TESTS = $(wildcard *.html)
OBJECTS = $(patsubst %.html,%.out,$(wildcard *.html))

all: $(OBJECTS)

# %.out: %.c
# 	$(CC) $< $(CFLAGS) -o $@

# %.c: %.html
# 	$(htmltohipe_location) $< > $@

# This version will also keep .c files
%.out: %.html
	$(htmltohipe_location) $< > $(basename $@).c
	$(CC) $(basename $@).c $(CFLAGS) -o $@

%.c: %.html
	$(htmltohipe_location) $< > $@


# example: make testbutton -j
test%: run% browser%
	echo $@

run%: %.out
	./$<

browser%: %.html
	chromium ./$<

clean:
	rm -f *.c *.out
