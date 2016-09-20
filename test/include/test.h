/* test.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef TEST_H
#define TEST_H

#include <corto/corto.h>
#include <_interface.h>
#include <jinja/jinja.h>
#include <corto/test/test.h>

#include <_type.h>
#include <_api.h>
#include <_meta.h>

#ifdef __cplusplus
extern "C" {
#endif


TEST_EXPORT PyObject* _test_getTestTemplateEnv(
    corto_string dir);
#define test_getTestTemplateEnv(dir) _test_getTestTemplateEnv(dir)
#include <JinjaTestSuite.h>

#ifdef __cplusplus
}
#endif
#endif

