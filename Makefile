.PHONY: clean cleaner

scm: scm.h util.o model.o read.o eval.o print.o repl.c
	cc -Wall -ansi -o scm util.o model.o read.o eval.o \
         print.o repl.c

util.o: scm.h util.c
	cc -Wall -ansi -c util.c

model.o: scm.h model.c
	cc -Wall -ansi -c model.c

read.o: scm.h read.c
	cc -Wall -ansi -c read.c

eval.o: scm.h eval.c
	cc -Wall -ansi -c eval.c

print.o: scm.h print.c
	cc -Wall -ansi -c print.c

clean:
	rm -f *.o

cleaner: clean
	rm -f scm
