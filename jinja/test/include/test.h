/* test.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef TEST_H
#define TEST_H

#include "corto/corto.h"
#include "_type.h"
#include "_api.h"
#include "_meta.h"
#include "_interface.h"

#ifdef __cplusplus
extern "C" {
#endif


TEST_EXPORT corto_word _test_testTemplateEnv(
    corto_string dir);
#define test_testTemplateEnv(dir) _test_testTemplateEnv(dir)
#include "JinjaTestSuite.h"
#include "jinja/jinja.h"
#include "corto/test/test.h"

#ifdef __cplusplus
}
#endif
#endif

