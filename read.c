#include <stdio.h>
#include <ctype.h>
#include "scm.h"

static int scm_is_delimiter(int c) {
    return isspace(c);
}

static int scm_digit_value(int c) {
    return c - '0';
}

/* Skip over whitespace and return the next sigificant
 * character.
 *
 * Like getc, returns EOF if end of file found or
 * an error occurs. Use ferror to discriminate.
 */
static int scm_nextc(FILE *in) {
    int c;

    while ((c = getc(in)) != EOF) {
        if (!isspace(c)) {
            break;
        }
    }
    return c;
}

static scm_object scm_read_number(FILE *in, int c) {
    char sign = '+';
    scm_int num = 0, tmp = -1;
    scm_object result;

    /* Carefully organize this code so only one check
     * for ferror below. If EOF is returned anywhere 
     * along the way, the next thing that will execute
     * is the ferror(in) call. */
    if (c == '-' || c == '+') {
        sign = c;
        c = getc(in);
    }
    while (isdigit(c)) {
        tmp = num * 10 + scm_digit_value(c);
        /* The next line assumes that if adding c in the
         * line above causes tmp to overflow, the overflow
         * will mean tmp is less than num. This will be
         * true if the base of the number being read is
         * small in comparison to the size of tmp.
         */
        if ((tmp < num) || (tmp > scm_fixnum_max)) {
            scm_fatal("scm_read_number: number too large");
        }
        num = tmp;
        c = getc(in);
    }
    if (ferror(in)) {
        scm_fatal("scm_read_number: getc error");
    }
    /* If tmp is still negative then it was never assigned
     * to indicating the body of the while loop above
     * did not execute even once.
     */
    if (tmp < 0) {
        scm_fatal("scm_read_number: "
            "must be at least one digit");
    }
    if (scm_is_delimiter(c)) {
        /* Push the delimiter back on the stream so it can
         * be read again elsewhere. This will be important
         * in the case of a ')' delimiter, for example,
         * as some other code in this reader will be waiting
         * for that character to indicate the end of a list.
         *
         * Check for EOF in case scm_is_delimiter allows it
         * as a delimiter. If trying to push EOF back on the
         * stream we will not know if an error has occured.
         */
        if (c != EOF) {
            c = ungetc(c, in);
            if (c == EOF) {
                scm_fatal("scm_read_number: ungetc error");
            }
        }
    } else {
        scm_fatal("scm_read_number: "
            "number not followed by a delimiter");
    }
    /* The next line assumes that any value of num, which
     * is not greater than scm_fixnum_max, can be negated
     * and still fit into a fixnum. This is true because
     * of assumption of two's complement hardware.
     */
    result = scm_fixnum_make(sign == '-' ? -num : num);

    return result;
}

scm_object scm_read(FILE *in) {
    int c;
    scm_object result;

    /* The reader code checks ferror(in) to determine if an
     * error occured during reading. If ferror(in)
     * already indicates error then results of ferror(in)
     * will be ambiguous.
     */
    if (ferror(in)) {
        scm_fatal("scm_read: can't read stream with error");
    }

    c = scm_nextc(in); /* get first non-space */

    switch (c) {
    case '+': case '-':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        result = scm_read_number(in, c);
        break;
    case EOF:
        if (ferror(in)) {
            scm_fatal("scm_read: getc error");
            break;
        }
        /********** FALL THROUGH **********/
    default:
        scm_fatal("scm_read: unexpected char '\\%o'", c);
    }

    return result;
}
