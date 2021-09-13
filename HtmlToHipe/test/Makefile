# Make file from Hipe runs all the html files

htmltohipe = ../htmltohipe
data = ../data/
CC = gcc
CFLAGS=-c -Wall
LFLAGS=-lgtest -lgtest_main -lpthread -lgumbo
INC=

ALL: media whitelist square square2 square3 nav flex-grid hipe-calc button hipe-canvas hipe-clock hipe-diag

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

button: button.c
	$(CC) button.c -o button -lhipe 

button.c:
	$(htmltohipe) $(data)button.html > button.c

whitelist: whitelist.c
	$(CC) whitelist.c -o whitelist -lhipe 

whitelist.c:
	$(htmltohipe) $(data)whitelist.html > whitelist.c

nav: nav.c
	$(CC) nav.c -o nav -lhipe
nav.c:
	$(htmltohipe) $(data)nav.html > nav.c

hipe-canvas: hipe-canvas.c
	$(CC) hipe-canvas.c -o hipe-canvas -lhipe 

hipe-canvas.c:
	$(htmltohipe) $(data)hipe-canvas.html > hipe-canvas.c

hipe-clock: hipe-clock.c
	$(CC) hipe-clock.c -o hipe-clock -lhipe 

hipe-clock.c:
	$(htmltohipe) $(data)hipe-clock.html > hipe-clock.c

hipe-diag: hipe-diag.c
	$(CC) hipe-diag.c -o hipe-diag -lhipe 

hipe-diag.c:
	$(htmltohipe) $(data)hipe-diag.html > hipe-diag.c

runALL:
	./nav && ./square && ./square2 && ./flex-grid && ./media && ./hipe_calc

runnav:
	./nav

runwhitelist:
	./whitelist

runmedia:
	./media

runflex-grid:
	./flex-grid

clean:
	rm nav.c media.c whitelist.c square.c square2.c square3.c hipe-calc.c flex-grid.c button.c \
	hipe-canvas.c hipe-clock.c hipe-diag.c \
	media flex-grid whitelist square square2 square3 hipe-calc nav button hipe-canvas hipe-clock hipe-diag

whitelist2:
	$(htmltohipe) whitelist-modified.html > whitelist.c
	gcc whitelist.c -o whitelist -lhipe
	./whitelist
