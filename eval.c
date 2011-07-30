#include "scm.h"

/* Until we have lists and symbols, just echo. The result of
 * echoing is the repl application is a pretty printer.
 */
scm_object scm_eval(scm_object expression) {
    return expression;
}
