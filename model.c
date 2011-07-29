#include "scm.h"

/* Algebraic negation. Object storage is designed
 * so that changing the sign of a Scheme number is
 * always a safe operation.
 */
scm_object scm_number_negate(scm_object o) {
    return scm_fixnum_make(-scm_fixnum_value(o));
}
