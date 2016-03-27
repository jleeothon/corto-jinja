/* $CORTO_GENERATED
 *
 * test.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include "test.h"

corto_word _test_testTemplateEnv(
    corto_string dir)
{
/* $begin(test/testTemplateEnv) */
    char* templatesDir = corto_envparse("$PWD/test/%s", dir);
    test_assert(templatesDir != NULL);
    PyObject* env = jinja_initialize(templatesDir);
    test_assert(env != NULL);
    corto_dealloc(templatesDir);
    return (corto_word)env;
/* $end */
}

int testMain(int argc, char* argv[]) {
/* $begin(main) */
    int result = 0;
    test_Runner runner = test_RunnerCreate("alfie", argv[0], (argc > 1) ? argv[1] : NULL);
    if (!runner) return -1;
    if (corto_llSize(runner->failures)) {
        result = -1;
    }
    corto_delete(runner);
    return result;
/* $end */
}
