

make: gettimings

gettimings:gettimings.o
	clang gettimings.o -o gettimings
gettimings.o:gettimings.c
	clang -c gettimings.c