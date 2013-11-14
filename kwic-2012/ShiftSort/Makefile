INC = ../include

XCFLAGS = -I$(INC) ## extra C flags

CC = gcc $(XCFLAGS)

driver: driver.o ShiftSort.o LineStorage.o WordTable.o
	$(CC) -o driver driver.o ShiftSort.o LineStorage.o WordTable.o

runtest: driver
	./driver

gcov: driver.o ShiftSort.o LineStorage.o WordTable.o
	$(CC) -fprofile-arcs -ftest-coverage -c ShiftSort.c
	$(CC) -fprofile-arcs -ftest-coverage -o driver driver.o ShiftSort.o LineStorage.o WordTable.o
	./driver
	gcov ShiftSort.c
	rm -f list.o # gcov version is dangerous to leave around

export: ShiftSort.o

driver.o: $(INC)/kwic.h $(INC)/ShiftSort.h
	$(CC) -c $(CFLAGS) driver.c

ShiftSort.o: $(INC)/kwic.h $(INC)/ShiftSort.h $(INC)/LineStorage.h \
		ShiftSort.c
	$(CC) -c $(CFLAGS) ShiftSort.c

LineStorage.o: $(INC)/kwic.h $(INC)/LineStorage.h LineStorage.c
	$(CC) -c $(CFLAGS) LineStorage.c

WordTable.o: $(INC)/kwic.h $(INC)/WordTable.h WordTable.c
	$(CC) -c $(CFLAGS) WordTable.c

clean:
	rm -f *.o act/* driver *.gcov *.gcda *.gcno
