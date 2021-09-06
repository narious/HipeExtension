# Make file from Hipe runs all the html files

htmltohipe = ../htmltohipe
data = ../data/
CC = gcc
CFLAGS=-c -Wall
LFLAGS=-lgtest -lgtest_main -lpthread -lgumbo
INC=

# ALL: media flex-grid whitelist runwhitelist runmedia runflex-grid
ALL: media whitelist

square: square.c
	$(CC) square.c -o square -lhipe
square.c :
	$(htmltohipe) $(data)square.html > square.c

square2: square2.c
	$(CC) square2.c -o square2 -lhipe
square2.c :
	$(htmltohipe) $(data)square2.html > square2.c

square3: square3.c
	$(CC) square3.c -o square3 $(CFLAGS)
square3.c :
	$(htmltohipe) $(data)square3.html > square3.c

hipe-calc: hipe-calc.c
	$(CC) hipe-calc.c -o hipe-calc -lhipe 
hipe-calc.c :
	$(htmltohipe) $(data)hipe_calc.html > hipe-calc.c

media: media.c
	$(CC) media.c -o media -lhipe 

media.c: 
	$(htmltohipe) $(data)media.html > media.c

flex-grid: flex-grid.c
	$(CC) flex-grid.c -o flex-grid -lhipe

flex-grid.c:
	$(htmltohipe) $(data)flex-grid.html > flex-grid.c

whitelist: whitelist.c
	$(CC) whitelist.c -o whitelist -lhipe 
whitelist.c:
	$(htmltohipe) $(data)whitelist.html > whitelist.c

nav: nav.c
	$(CC) nav.c -o nav -lhipe
nav.c:
	$(htmltohipe) $(data)nav.html > nav.c

runnav:
	./nav

runwhitelist:
	./whitelist

runmedia:
	./media

runflex-grid:
	./flex-grid

clean:
	rm nav.c media.c whitelist.c square.c square2.c square3.c hipe-calc.c flex-grid.c \
	media flex-grid whitelist square square2 square3 hipe-calc

whitelist2:
	$(htmltohipe) whitelist-modified.html > whitelist.c
	gcc whitelist.c -o whitelist -lhipe
	./whitelist
