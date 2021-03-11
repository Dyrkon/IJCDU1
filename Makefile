CFLAGS  = -g -std=c11 -Wextra -Wall -pedantic -O2
#CFLAGS = -g -std=c11 -Wextra -Wall -pedantic -O2 -DUSE_INLINE
#CFLAGS = -m32 -std=c11 -Wextra -Wall -pedantic -O2
#LDFLAGS = -m32
LDFLAGS = -g
LDLIBS  = -lm # pokud potřebujeme matematickou knihovnu libm
CC = gcc
TIME = time

all: ijcdu1 ijcdu1-i

primes-i.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS1) primes.c

primes.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c

ppm.o: ppm.c ppm.h

error.o: error.c error.h

steg-decode.o: steg-decode.c ppm.h error.h bitset.h

# sestavení (stejné jako pro implicitní akci)
ijcdu1: primes.o ppm.o error.o steg-decode.o
	$(CC) $(LDFLAGS) -o ijcdu1 primes.o ppm.o error.o steg-decode.o $(LDLIBS)

#ijcdu1-i: primes-i.o error.o
#	$(CC) $(LDFLAGS) -o ijcdu1-i primes-i.o error.o $(LDLIBS)

# úklid
clean:
	rm -f  *~  *.bak  *.o  program

# vytvoření archívu
archiv:
	tar czvf xmudra04.tar.gz *.c *.h Makefile

run:
	./ijcdu1
	./ijcdu1 du1-obrazek.ppm
	#./ijcdu1-i