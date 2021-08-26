#! /bin/sh
# File to compile a client program. Takes a single argument
# filepath to html file compile to hipe client.
./htmltohipe $1 > tmp.c
gcc tmp.c -lhipe -o cli
