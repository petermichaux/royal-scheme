CC = gcc

FLAGS = -ansi -pedantic-errors -Wall -Wextra            \
        -Wmissing-include-dirs                          \
        -Wswitch-default -Wswitch-enum -Wundef          \
        -Wdeclaration-after-statement -Wcast-qual       \
        -Wcast-align -Wstrict-prototypes                \
        -Wmissing-prototypes -Wmissing-declarations     \
        -Wmissing-field-initializers -Wunreachable-code \
        -Wvariadic-macros -Werror

.PHONY: clean cleaner

scm: scm.h util.o model.o read.o eval.o print.o repl.c
	$(CC) $(FLAGS) -o scm util.o model.o read.o eval.o \
         print.o repl.c

util.o: scm.h util.c
	$(CC) $(FLAGS) -c util.c

model.o: scm.h model.c
	$(CC) $(FLAGS) -c model.c

read.o: scm.h read.c
	$(CC) $(FLAGS) -c read.c

eval.o: scm.h eval.c
	$(CC) $(FLAGS) -c eval.c

print.o: scm.h print.c
	$(CC) $(FLAGS) -c print.c

clean:
	rm -f *.o

cleaner: clean
	rm -f scm
