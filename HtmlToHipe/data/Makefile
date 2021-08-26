htmltohipe_location = ../htmltohipe
CC = gcc

ALL: media flex-grid whitelist runwhitelist runmedia runflex-grid

media: media.c
	$(CC) media.c -o media -lhipe 

media.c: 
	$(htmltohipe_location) media.html > media.c

flex-grid: flex-grid.c
	$(CC) flex-grid.c -o flex-grid -lhipe 
flex-grid.c:
	$(htmltohipe_location) flex-grid.html > flex-grid.c

whitelist: whitelist.c
	$(CC) whitelist.c -o whitelist -lhipe 
whitelist.c:
	$(htmltohipe_location) whitelist.html > whitelist.c

nav: nav.c
	$(CC) nav.c -o nav -lhipe
nav.c:
	$(htmltohipe_location) nav.html > nav.c

runnav:
	./nav
	
runwhitelist:
	./whitelist

runmedia:
	./media

runflex-grid:
	./flex-grid

clean:
	rm *.c
	rm media flex-grid whitelist
