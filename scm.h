#ifndef SCM_H
#define SCM_H

#include <stdio.h>
#include <limits.h>

/************************* util.c *************************/

void scm_fatal(char *fmt, ...);

/************************ model.c *************************/

/* Assume scm_int is large enough to hold any
 * scm_object fixnum.
 */
typedef long scm_int;

/* A scm_object can be any of Scheme's many types:
 * the empty list, boolean, number, symbol,
 * pair, vector, string, port, etc. For now we only have
 * fixnums which will fit in a scm_int.
 */
typedef scm_int scm_object;

/* Trival conversions to and from fixnum since they are
 * currently the only type.
 */
#define scm_fixnum_make(val) ((scm_object)(val))
#define scm_fixnum_value(object) ((scm_int)(object))
/* assume a two's complement hardware representation */
#define scm_fixnum_min \
    (((scm_int)1)<<(8*sizeof(scm_object)-1))
#define scm_fixnum_max (-(scm_fixnum_min+1))

/************************* read.c *************************/

scm_object scm_read(FILE *in);

/************************* eval.c *************************/

scm_object scm_eval(scm_object expression);

/************************ print.c *************************/

int scm_write(FILE *out, scm_object object);

#endif
