
#ifndef JINJA_H
#define JINJA_H

/* Add include files here */

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>

PyObject* jinja_initialize(const char* templdir);

void jinja_finalize(PyObject* jinja);

/*
 * Return value: New reference.
 * Fetches a template and returns the template instance.
 */
PyObject* jinja_template(PyObject* jinja, const char* templname);

/*
 * Call it the first time with a Jinja environment. And the next times with
 * NULL as parameter. Each time will return a template name.
 * This is similar to how strtok works.
 */
char* jinja_templates(PyObject* jinja);

/*
 * Renders a template and writes the result to "out".
 * Returns a new string. Caller must deallocate it.
 */
char* jinja_render(PyObject* templ, PyObject* context);

/*
 * Shortcut call to both jinja_template and jinja_render.
 * Caller must deallocate the returned string.
 */
char* jinja_templaterender(PyObject* jinja, const char* templname, PyObject* context);

#ifdef __cplusplus
}
#endif

#endif /* JINJA_H */
