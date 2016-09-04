P=tests
OBJECTS=slist.tests.o dlist.tests.o ../src/slist.o
CFLAGS= -g -Wall -O3 -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LDLIBS=-lcriterion
CC=clang

$(P):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) $(LDLIBS) 
	@mv *.o ../src/*.o ./bin/

clean:
	@rm ./bin/* tests
