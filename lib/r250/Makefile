.PHONY: static_32 static_64 clean
CFLAGS=-O3 -ansi -I ../include/ -fPIC
SOURCES = r250.c randlcg.c
OBJ32= r250_32.o randlcg_32.o
OBJ64= r250_64.o randlcg_64.o

r250_64.o: r250.c
	$(CC) $(CFLAGS) -m64 -c -o $@ $<

randlcg_64.o: randlcg.c
	$(CC) $(CFLAGS) -m64 -c -o $@ $<

r250_32.o: r250.c
	$(CC) $(CFLAGS) -m32 -c -o $@ $<

randlcg_32.o: randlcg.c
	$(CC) $(CFLAGS) -m32 -c -o $@ $<

static_32: clean $(OBJ32) $(SOURCES)
	ar rcs libr250_32.a $(OBJ32)
	
static_64: clean $(OBJ64) $(SOURCES)
	ar rcs libr250_64.a $(OBJ64)

clean: 
	rm -f libr250_32.a
	rm -f libr250_64.a
	rm -f r250_32.o
	rm -f randlcg_32.o
	rm -f r250_64.o
	rm -f randlcg_64.o

