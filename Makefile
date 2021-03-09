CFLAGS  = -g -std=c11 -Wextra -Wall -pedantic -O2
#CFLAGS 	= -g -std=c11 -Wextra -Wall -pedantic -O2 -DUSE_INLINE
#CFLAGS 	= -g -std=c11 -Wextra -Wall -pedantic -O2
LDFLAGS = -g
LDLIBS  = -lm # pokud potřebujeme matematickou knihovnu libm

all: program

# překlad prvního modulu
primes.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c

# překlad druhého modulu - implicitní akce
ppm.o: ppm.c ppm.h

error.o: error.c error.h

steg-decode.o: steg-decode.c ppm.h error.h bitset.h

# sestavení (stejné jako pro implicitní akci)
program: primes.o ppm.o error.o steg-decode.o
	$(CC) $(LDFLAGS) -o program primes.o ppm.o error.o steg-decode.o $(LDLIBS)

# testování výsledku (regresní testy a podobně)
test: program
	./program
	time ./program
	./program jiné du1-obrazek.ppm

# úklid
clean:
	rm -f  *~  *.bak  *.o  program

# vytvoření archívu
archiv:
	tar czvf xmudra04.tar.gz *.c *.h Makefile