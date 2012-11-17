#ifndef SCM_H
#define SCM_H

#include <stdio.h>
#include <limits.h>

/************************* util.c *************************/

void scm_fatal(char *fmt, ...);

/************************ model.c *************************/

/* scm_int must be large enough to hold any Scheme fixnum
 * and any character value.
 */
typedef long scm_int;

/* A scm_object can be any of Scheme's many types: boolean,
 * the empty list, number, symbol, pair, vector, etc.
 */
typedef long scm_object;

/* immediate objects tagging system
 *     01 fixnum
 *   0110 characters
 *   1110 special objects (e.g. null, true, false, and eof)
 */

#define scm_fixnum_mask    3
#define scm_fixnum_tag     1
#define scm_fixnum_bits    2

#define scm_char_mask     15
#define scm_char_tag       6
#define scm_char_bits      4

#define scm_special_mask  15
#define scm_special_tag   14
#define scm_special_bits   4

#define scm_fixnum_make(val) ((scm_object) \
   ((((scm_int)(val)) << scm_fixnum_bits) + scm_fixnum_tag))
#define scm_fixnum_is(object) \
    ((((scm_int)(object))&scm_fixnum_mask)==scm_fixnum_tag)
#define scm_fixnum_value(object) \
    (((scm_int)(object)) >> scm_fixnum_bits)

/* Assume a two's complement hardware representation and
 * arithmetic right shift of signed integers.
 *
 * Ensure that any number can be algebraically negated
 * and the result is still in the acceptable range.
 */
#define scm_fixnum_min (((((scm_int)1) \
   << (8 * sizeof(scm_object) - 1)) >> scm_fixnum_bits) + 1)
#define scm_fixnum_max (-(scm_fixnum_min))

#define scm_char_make(val) ((scm_object) \
    ((((scm_int)(val)) << scm_char_bits) + scm_char_tag))
#define scm_char_is(object) \
    ((((scm_int)(object)) & scm_char_mask) == scm_char_tag)
#define scm_char_value(object) \
    (((scm_int)(object)) >> scm_char_bits)

#define scm_special_make(n) ((scm_object) \
    (((n) << scm_special_bits) + scm_special_tag))

#define scm_null  scm_special_make(0)
#define scm_true  scm_special_make(1)
#define scm_false scm_special_make(2)
#define scm_eof   scm_special_make(3)

/************************* read.c *************************/

scm_object scm_read(FILE *in);

/************************* eval.c *************************/

scm_object scm_eval(scm_object expression);

/************************ print.c *************************/

int scm_write(FILE *out, scm_object object);

#endif
