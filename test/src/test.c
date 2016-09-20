/* $CORTO_GENERATED
 *
 * test.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

PyObject* _test_getTestTemplateEnv(
    corto_string dir)
{
/* $begin(test/getTestTemplateEnv) */
    char* templatesDir = NULL;
    corto_asprintf(&templatesDir, "%s/%s", TEST_ETC, dir);
    test_assert(templatesDir != NULL);
    PyObject* env = jinja_initialize(templatesDir);
    test_assert(env != NULL);
    corto_dealloc(templatesDir);
    return env;
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
