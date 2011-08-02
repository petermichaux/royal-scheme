#include <stdio.h>
#include <ctype.h>
#include "scm.h"

/* if an error occurs returns negative */
int scm_write(FILE *out, scm_object object) {
    int result;
    scm_int c;

    if (scm_fixnum_is(object)) {
        /* Cast the fixnum's value to long because we need
         * to specify the format string yet we don't know
         * the size of a fixnum's value here. Casting to
         * long cannot lose information so the cast is
         * safe (i.e. won't print an incorrect value.)
         */
        result = fprintf(out, "%ld",
                     (long)scm_fixnum_value(object));
    } else if (scm_char_is(object)) {
        c = scm_char_value(object);
        switch(c) {
        case ' ':
            result = fprintf(out, "#\\space");
            break;
        case '\n':
            result = fprintf(out, "#\\newline");
            break;
        default:
            /* Check the value is in the ASCII range
             * to avoid loss in conversion to a shorter
             * int type in call to isgraph.
             */
            if (c < 128 && isgraph(c)) {
                result = fprintf(out, "#\\%c", (int)c);
            } else {
                result = fprintf(out, "#\\%lo", (long)c);
            }
        }
    } else {
        switch ((scm_int)object) {
        case (scm_int)scm_null:
            result = fprintf(out, "()");
            break;
        case (scm_int)scm_true:
            result = fprintf(out, "#t");
            break;
        case (scm_int)scm_false:
            result = fprintf(out, "#f");
            break;
        case (scm_int)scm_eof:
            result = fprintf(out, "#<eof>");
            break;
        default:
            scm_fatal("scm_write: illegal argument");
        }
    }
    return result;
}
