INC = ../include

XCFLAGS = -I$(INC)	## local C flags

CC = gcc $(XCFLAGS)

driver: driver.o Output.o ShiftSort.o
	$(CC) -o driver driver.o Output.o ShiftSort.o

runtest: driver
	./driver > actualOutput
	diff actualOutput expectedOutput

gcov: driver.o Output.o ShiftSort.o
	$(CC) -fprofile-arcs -ftest-coverage -c Output.c
	$(CC) -fprofile-arcs -ftest-coverage -o driver driver.o Output.o ShiftSort.o
	./driver > /dev/null
	gcov Output.c
	rm -f list.o # gcov version is dangerous to leave around

export: Output.o

driver.o: $(INC)/kwic.h $(INC)/Output.h $(INC)/ShiftSort.h driver.c
	$(CC) -c -o driver.o $(CFLAGS) driver.c

Output.o: $(INC)/kwic.h $(INC)/Output.h $(INC)/ShiftSort.h \
		Output.c
	$(CC) -c $(CFLAGS) Output.c

ShiftSort.o: $(INC)/kwic.h $(INC)/ShiftSort.h ShiftSort.c
	$(CC) -c $(CFLAGS) ShiftSort.c

clean:
	rm -f *.o actualOutput driver *.gcov *.gcda *.gcno
