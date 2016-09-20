/* $CORTO_GENERATED
 *
 * JinjaTestSuite.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <test.h>

/* $header() */
/* $end */

corto_void _test_JinjaTestSuite_setup(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/setup) */
    Py_Initialize();
/* $end */
}

corto_void _test_JinjaTestSuite_tc_getMissingTemplate(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_getMissingTemplate) */
    /* TODO This test prints to stderr */
    this->jinja = test_getTestTemplateEnv("templates");
    PyObject* jinja = (PyObject*)this->jinja;
    PyObject* template = jinja_template(jinja, "templateX.txt");
    test_assert(template == NULL);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_getTemplate(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_getTemplate) */
    this->jinja = test_getTestTemplateEnv("templates");
    PyObject* jinja = (PyObject*)this->jinja;
    PyObject* template = jinja_template(jinja, "template1.txt");
    test_assert(template != NULL);
    test_assert(strcmp(Py_TYPE(template)->tp_name, "Template") == 0);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_init_finalize(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_init_finalize) */
    this->jinja = test_getTestTemplateEnv("/usr/local");
    test_assert(this->jinja != NULL);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_listTemplates(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_listTemplates) */
    PyObject* jinja = test_getTestTemplateEnv("templates");
    int templateCount = 0;
    char* template = jinja_templates(jinja);
    test_assert(template != NULL);
    while (template) {
        templateCount++;
        template = jinja_templates(NULL);
    }
    test_assert(templateCount == 3);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_listTemplatesEmpty(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_listTemplatesEmpty) */
    PyObject* jinja = test_getTestTemplateEnv("templates0");
    char* template = jinja_templates(jinja);
    test_assert(template == NULL);
    test_assert(!PyErr_Occurred());
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_listTemplatesSingle(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_listTemplatesSingle) */
    PyObject* jinja = test_getTestTemplateEnv("templates1");
    int templateCount = 0;
    char* template = jinja_templates(jinja);
    test_assert(template != NULL);
    while (template) {
        templateCount++;
        template = jinja_templates(NULL);
    }
    test_assert(templateCount == 1);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_renderTemplateList(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_renderTemplateList) */
    PyObject* jinja = test_getTestTemplateEnv("templates");
    PyObject* template = jinja_template(jinja, "templateList.txt");
    test_assert(template != NULL);

    PyObject* dict = Py_BuildValue("{s: [s, s, s]}", "ingredients", "bacon", "eggs", "spam");
    char* text = jinja_render(template, dict);
    test_assert(text != NULL);
    test_assert(strcmp(text, "baconeggsspam") == 0);
    free(text);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_renderTemplateSimple(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_renderTemplateSimple) */
    PyObject* jinja = test_getTestTemplateEnv("templates");
    PyObject* template = jinja_template(jinja, "template1.txt");
    test_assert(template != NULL);

    PyObject* dict = PyDict_New();
    char* text = jinja_render(template, dict);
    test_assert(text != NULL);
    test_assert(strcmp(text, "Hello World") == 0);
    free(text);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_tc_renderTemplateVariable(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/tc_renderTemplateVariable) */
    PyObject* jinja = test_getTestTemplateEnv("templates");
    PyObject* template = jinja_template(jinja, "template2.txt");
    test_assert(template != NULL);

    PyObject* dict = Py_BuildValue("{s:s}", "name", "Jinja");
    char* text = jinja_render(template, dict);
    test_assert(text != NULL);
    test_assert(strcmp(text, "Hello, Jinja") == 0);
    free(text);
    jinja_finalize(this->jinja);
/* $end */
}

corto_void _test_JinjaTestSuite_teardown(
    test_JinjaTestSuite this)
{
/* $begin(test/JinjaTestSuite/teardown) */
    Py_Finalize();
/* $end */
}
