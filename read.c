#include <stdio.h>
#include <ctype.h>
#include "scm.h"

static int scm_is_delimiter(int c) {
    return c == '\t' || c == '\n' ||
           c == '\r' || c == ' '  ||
           c == ')'  || c == ';'  ||
           c == EOF;
}

static int scm_digit_value(int c) {
    return c - '0';
}

static scm_object scm_read_number(FILE *in) {
    char is_negative = 0;
    int c;
    scm_int num = 0, tmp;

    c = getc(in);
    if (c == '-') {
        is_negative = 1;
        c = getc(in);
    }
    if (!isdigit(c)) {
        scm_fatal("scm_read_number: "
            "number must start with a digit");
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
    if (!scm_is_delimiter(c)) {
        scm_fatal("scm_read_number: "
            "number not followed by a delimiter");
    }
    if (c != EOF) {
        c = ungetc(c, in);
        if (c == EOF) {
            scm_fatal("scm_read_number: could not ungetc");
        }
    }
    /* The next line assumes that any value of num, which
     * is not greater than scm_fixnum_max, can be negated
     * and still fit into a fixnum. This is true because
     * of assumption of two's complement hardware.
     */
    return scm_fixnum_make(is_negative ? -num : num);
}

scm_object scm_read(FILE *in) {
    int c0, c1;
    scm_object result;

loop:
    switch (c0 = getc(in)) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        goto loop;
    case ';':
        /* comments continue to the end of the line */
        while ((c0 = getc(in)) != EOF) {
            if (c0 == '\n') {
                break;
            }
        }
        goto loop;
    case '+':
    case '-':
        c1 = getc(in);
        if (isdigit(c1)) {
            c1 = ungetc(c1, in);
            if (c1 == EOF) {
                scm_fatal("scm_read: could not ungetc");
            }
            result = scm_read_number(in);
            if (c0 == '-') {
                /* We know scm_read_number returns a
                 * positive result in this case and
                 * so we can negate with our assumption
                 * of two's complement architecture.
                 */
                result = scm_fixnum_make(
                             - scm_fixnum_value(result));
            }
        }
        else {
            /* TODO Add symbol support for the symbols
             * '+', '-' and those starting with '+' '-'.
             */
            scm_fatal("scm_read: symbols not supported");
        }
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        c0 = ungetc(c0, in);
        if (c0 == EOF) {
            scm_fatal("scm_read: could not ungetc");
        }
        result = scm_read_number(in);
        break;
    default:
        scm_fatal("scm_read: unexpected char '\\%o'", c0);
    }

    return result;
}
