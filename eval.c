#include "scm.h"

/* Until we have lists and symbols, just echo.
 * The result of this echoing is that the repl
 * application is a simple pretty printer.
 */
scm_object scm_eval(scm_object expression) {
    return expression;
}
