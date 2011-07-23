#include <stdio.h>
#include "scm.h"

void repl(void) {
    int p;
    scm_object object;

    while (1) {
        p = printf("> ");
        if (p < 0) {
            scm_fatal("repl: print failed");
        }
        /* TODO Currently scm_read and scm_eval exit in the
         * case of failure. Eventually scm_read and
         * scm_eval will return Scheme error objects in the
         * case of failure. For example, scm_read may
         * return a syntax error for bad user input. Check
         * the return value for errors and report them to
         * the user.
         */
        object = scm_read(stdin);
        object = scm_eval(object);
        p = scm_write(stdout, object);
        if (p < 0) {
            scm_fatal("repl: print failed");
        }
        p = printf("\n");
        if (p < 0) {
            scm_fatal("repl: print failed");
        }
    }
}

int main(void) {
    printf("Welcome to Royal Scheme. Ctrl-c to exit.\n");
    repl();
    return 0;
}
