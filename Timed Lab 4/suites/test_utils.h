
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *tl4_suite(void);

// Define a check containing only one test case of the same name
#define tcase_singleton(suite, setup_fixture, teardown_fixture, func)   \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** tl4 Header Info *********************************/
/******************************************************************************/

// #define UNUSED_PARAM(x) ((void)x) // This macro is only used for turning off compiler errors initially
// #define UNUSED_FUNC(x) ((void)x)  // This macro is only used for turning off compiler errors initially

#define DEBUG_FLAG "-d"

#include "../tl04.h"

int _set_character(struct ascii_image *image, int row, int col, char c);
struct ascii_image *_create_image(int height, int width, char *name);
int _draw_hollow_box(struct ascii_image *image, int row, int col, int height, int width, char c);
void _free_image(struct ascii_image *image);
void _free_image_safe_name(struct ascii_image *image, const char *name);

