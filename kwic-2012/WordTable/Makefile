INC = ../include

XCFLAGS = -I$(INC) ## extra C flags
CFLAGS = -g	## a suitable option for the runtest

CC = gcc $(XCFLAGS)

driver: driver.o WordTable.o
	$(CC) -o driver driver.o WordTable.o

runtest: driver
	./driver

gcov: driver.o WordTable.o
	$(CC) -fprofile-arcs -ftest-coverage -c WordTable.c
	$(CC) -fprofile-arcs -ftest-coverage -o driver driver.o WordTable.o
	./driver
	gcov WordTable.c
	rm -f list.o # gcov version is dangerous to leave around

export: WordTable.o

driver.o: $(INC)/kwic.h $(INC)/WordTable.h driver.c
	$(CC) -c $(CFLAGS) driver.c

WordTable.o: $(INC)/kwic.h $(INC)/WordTable.h WordTable.c
	$(CC) -c $(CFLAGS) WordTable.c

clean:
	rm -f *.o act/* driver  *.gcov *.gcda *.gcno
