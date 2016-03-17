#
CC=g++
CFLAGS=-c -Wall

all: testdatalist

testdatalist: main.o menu.o data.o
	$(CC) main.o menu.o data.o -o testdatalist

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

menu.o: menu.cpp
	$(CC) $(CFLAGS) menu.cpp

data.o: data.cpp
	$(CC) $(CFLAGS) data.cpp

clean:
	rm -rf *.o testdatalist