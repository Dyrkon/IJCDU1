CFLAGS  = -g -std=c11 -Wextra -Wall -pedantic -O2
CFLAGS2 = -g -std=c11 -Wextra -Wall -pedantic -O2 -DUSE_INLINE
#CFLAGS = -m32 -std=c11 -Wextra -Wall -pedantic -O2
#LDFLAGS = -m32
LDFLAGS = -g
LDLIBS  = -lm # pokud potřebujeme matematickou knihovnu libm
CC = gcc
TIME = time

all: primes primes-i

primes-i.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS1) -c primes.c -o primes-i.o

primes.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c

ppm.o: ppm.c ppm.h

error.o: error.c error.h

steg-decode.o: steg-decode.c ppm.h error.h bitset.h

primes: primes.o ppm.o error.o steg-decode.o
	$(CC) $(LDFLAGS) -o primes primes.o ppm.o error.o steg-decode.o $(LDLIBS)

primes-i: primes-i.o ppm.o error.o steg-decode.o
	$(CC) $(LDFLAGS) -o primes-i primes-i.o ppm.o error.o steg-decode.o $(LDLIBS)

clean:
	rm -f  *~  *.bak  *.o  primes primes-i

archiv:
	tar czvf xmudra04.tar.gz *.c *.h Makefile

run: primes primes-i
	./primes
	./primes du1-obrazek.ppm
	./primes-i