#include <stdio.h>
#include "scm.h"

/* if an error occurs returns negative */
int scm_write(FILE *out, scm_object object) {
    int result;

    /* Cast the fixnum's value to long because we need to
     * specify the format string yet we don't know the size
     * of a fixnum's value here. Casting to long cannot
     * loose information so the cast is safe (i.e. won't
     * print an incorrect value.)
     */
    result = fprintf(out, "%ld",
                 (long)scm_fixnum_value(object));
    return result;
}
