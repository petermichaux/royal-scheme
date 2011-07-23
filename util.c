#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "scm.h"

/* scm_fatal is borrowed from K&R2e page 174 where it is
 * called "error".
 *
 * Purposely ignoring return values of fprintf and
 * vfprintf because we want to continue to the exit
 * even if there is an error printing.
 */
void scm_fatal(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
