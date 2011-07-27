CC = gcc

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -Werror    \
         -Wmissing-include-dirs                          \
         -Wswitch-default -Wswitch-enum -Wundef          \
         -Wdeclaration-after-statement -Wcast-qual       \
         -Wcast-align -Wstrict-prototypes                \
         -Wmissing-prototypes -Wmissing-declarations     \
         -Wmissing-field-initializers -Wunreachable-code \
         -Wvariadic-macros

OBJECTS = util.o model.o read.o eval.o print.o repl.o

.PHONY: clean cleaner

scm: scm.h $(OBJECTS)
	$(CC) $(CFLAGS) -o scm $(OBJECTS)

clean:
	rm -f *.o

cleaner: clean
	rm -f scm
