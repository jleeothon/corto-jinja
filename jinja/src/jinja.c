
#include "jinja/jinja.h"

/*
 * TODO Functions here do not clear the Python error indicator.
 */

#define debug (1)

#define if_goto(expr, label) do { if (expr) goto label; } while(0)
#define ifn_goto(expr, label) \
do { \
    if (!(expr)) { \
        if (debug && PyErr_Occurred()) { \
            fprintf(stdin, "Line %d\n", __LINE__); \
            PyErr_Print(); \
        } goto label; \
    } \
} while(0)

static int i = 0;
#define putsy() do { printf("%d (%d)\n", i, __LINE__); i++; } while (0)


PyObject* jinja_init(const char* templdir)
{
    Py_Initialize();

    PyObject* loadersModule = PyImport_ImportModule("jinja2.loaders");
    ifn_goto(loadersModule, errorImportLoadersModule);

    PyObject* environmentModule = PyImport_ImportModule("jinja2.environment");
    ifn_goto(environmentModule, errorImportEnvironmentModule);

    PyObject* fileSystemLoaderClass = PyObject_GetAttrString(loadersModule, "FileSystemLoader");
    ifn_goto(fileSystemLoaderClass, errorGetFileSystemLoaderClass);
    
    PyObject* environmentClass = PyObject_GetAttrString(environmentModule, "Environment");
    ifn_goto(environmentClass, errorGetEnvironmentClass);

    PyObject* fileSystemLoader = NULL;
    {
        PyObject* args = Py_BuildValue("(s)", templdir);
        ifn_goto(args, errorFileSystemLoader);
        fileSystemLoader = PyObject_Call(fileSystemLoaderClass, args, NULL);
        Py_DECREF(args);
    }
    ifn_goto(fileSystemLoader, errorFileSystemLoader);
    Py_DECREF(fileSystemLoaderClass);
    fileSystemLoaderClass = NULL;

    PyObject* environment = NULL;
    {
        PyObject* args = Py_BuildValue("()");
        ifn_goto(args, errorEnvironment);
        PyObject* kwargs = Py_BuildValue("{s:O}", "loader", fileSystemLoader);
        ifn_goto(kwargs, errorEnvironment);
        environment = PyObject_Call(environmentClass, args, kwargs);
        Py_DECREF(kwargs);
    }
    ifn_goto(environment, errorEnvironment);
    Py_DECREF(environmentClass);
    environmentClass = NULL;
    Py_DECREF(fileSystemLoader);
    fileSystemLoader = NULL;

    return environment;

errorEnvironment:
    Py_DECREF(fileSystemLoader);
errorFileSystemLoader:
    Py_DECREF(environmentClass);
errorGetEnvironmentClass:
    Py_DECREF(fileSystemLoaderClass);
errorGetFileSystemLoaderClass:
    Py_DECREF(environmentModule);
errorImportEnvironmentModule:
    Py_DECREF(loadersModule);
errorImportLoadersModule:
    Py_Finalize();
    return NULL;
}

void jinja_finalize(PyObject* jinja)
{
    Py_XDECREF(jinja);
    Py_Finalize();
}

PyObject* jinja_template(PyObject* jinja, const char* templname)
{
    PyObject* template = PyObject_CallMethod(jinja, "get_template", "(s)", templname);
    ifn_goto(template, error);
    return template;
error:
    return NULL;
}


static char* jinja_templatesFirst(PyObject* jinja, PyObject** iterator, PyObject** curr)
{
    /* Clear anything from previous calls */
    if (*iterator) {
        Py_DECREF(*iterator);
        *iterator = NULL;
    }
    if (*curr) {
        Py_DECREF(*curr);
    }

    /* Get iterator */
    PyObject* templates = PyObject_CallMethod(jinja, "list_templates", NULL);
    ifn_goto(templates, error);
    *iterator = PyObject_GetIter(templates);
    Py_DECREF(templates);
    ifn_goto(*iterator, error);

    /* Get string */
    char* s = NULL;
    *curr = PyIter_Next(*iterator);
    if (*curr) {
        s = PyUnicode_AsUTF8(*curr);
    } else {
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
    }
    return s;
error:
    if (PyErr_Occurred()) {
        PyErr_Print();
    }
    return NULL;
}


static char* jinja_templatesNext(PyObject** iterator, PyObject** curr)
{
    ifn_goto(*iterator, error);
    ifn_goto(*curr, error);

    Py_DECREF(*curr);
    *curr = PyIter_Next(*iterator);

    char* s = NULL;
    if (*curr) {
        s = PyUnicode_AsUTF8(*curr);
    } else {
        if (PyErr_Occurred()) {
            PyErr_Print();
        } else {
            Py_DECREF(*iterator);
            *iterator = NULL;
        }
    }
    return s;
error:
    return NULL;
}


/*
 * Call it the first time with a Jinja environment. And the next times with
 * NULL as parameter. Each time will return a template name.
 * This is similar to how strtok works.
 */
char* jinja_templates(PyObject* jinja)
{
    static PyObject* iterator = NULL;
    // static PyObject* next = NULL;
    static PyObject* curr = NULL;
    if (jinja) {
        return jinja_templatesFirst(jinja, &iterator, &curr);
    } else {
        return jinja_templatesNext(&iterator, &curr);
    }
}


char* jinja_render(PyObject* template, PyObject* dict)
{
    PyObject* result = PyObject_CallMethod(template, "render", "O", dict);
    ifn_goto(result, errorRender);
    
    char* _out = PyUnicode_AsUTF8(result);
    ifn_goto(_out, errorAsUTF8);
    
    char* out = malloc(strlen(_out) + 1);
    ifn_goto(out, errorDup);
    strcpy(out, _out);

    Py_DECREF(result);

    return out;

errorDup:
errorAsUTF8:
    Py_XDECREF(result);
errorRender:
    return NULL;
}


/* cortomain is called when the package is loaded by Corto. It is a good
 * place for initialization code that needs to be executed once.
 * The function can be safely removed if not needed. */
int cortomain(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    return 0;
}

