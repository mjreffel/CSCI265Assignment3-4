INC = ../include

XCFLAGS = -I$(INC)	## extra C flags

CC = gcc $(XCFLAGS)

RUNTEST = - (rm -f actualOutput/*; \
	cd input; \
	for f in *; do \
		echo input file: $$f passed through stdin; \
		../driver < $$f >../actualOutput/$$f; \
		diff ../actualOutput/$$f ../expectedOutput/$$f; \
		echo input file: $$f; \
		../driver $$f >../actualOutput/$$f; \
		diff ../actualOutput/$$f ../expectedOutput/$$f; \
	done)

driver: driver.o Input.o LineStorage.o
	$(CC) -o driver driver.o Input.o LineStorage.o

runtest: driver
	$(RUNTEST)

gcov: driver.o Input.o LineStorage.o
	$(CC) -fprofile-arcs -ftest-coverage -c Input.c
	$(CC) -fprofile-arcs -ftest-coversge -o driver driver.o Input.o LineStorage.o
	$(RUNTEST)
	gcov Input.c
	rm -f list.o # gcov version is dangerous to leave around

export: Input.o

driver.o: $(INC)/kwic.h $(INC)/Input.h $(INC)/LineStorage.h driver.c
	$(CC) -c -o driver.o $(CFLAGS) driver.c

Input.o: $(INC)/kwic.h $(INC)/Input.h $(INC)/LineStorage.h Input.c
	$(CC) -c $(CFLAGS) Input.c

LineStorage.o: $(INC)/kwic.h $(INC)/LineStorage.h LineStorage.c
	$(CC) -c $(CFLAGS) LineStorage.c

clean:
	rm -f *.o actualOutput/* driver  *.gcov *.gcda *.gcno
