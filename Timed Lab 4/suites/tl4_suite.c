/**
 * @file tl4_suite.c
 * @author David, Dillon
 * @brief Testing Suites to TL4 - Summer2020
 * @date 07-12-2020
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

int mallocs_until_fail = -1;

// allow infinite mallocs by default
static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static char *render_image(int width, int height, const char *data) {
    size_t new_len = height * (width + 1);
    char *str = malloc(new_len + 1);
    for (int row = 0; row < height; row++) {
        memcpy(&str[row * (width + 1)], &data[row * width], width);
    }
    for (int row = 0; row < height; row++) {
        str[row * (width + 1) + width] = '\n';
    }
    str[new_len] = '\0';
    return str;
}

const char *_big_image =
    "..|.."
    "./_\\."
    ".|@|."
    ".|_|."
    "/___\\"
    ".VvV.";
static int _big_image_width = 5;
static int _big_image_height = 6;
static struct ascii_image *_create_big_image(void) {
    struct ascii_image *img = _create_image(_big_image_height, _big_image_width, "big_image");
    memcpy(img->data, _big_image, _big_image_width * _big_image_height);
    return img;
}

static struct ascii_image *_create_small_image(void) {
    struct ascii_image *img = _create_image(3, 3, "small_image");
    return img;
}

static void assert_image_data(struct ascii_image *image, struct ascii_image *expected) {
    if ((image->data == NULL) && (expected->data != NULL)) {
        ck_abort_msg("expected data to not be NULL");
    } else if ((image->data != NULL) && (expected->data == NULL)) {
        ck_abort_msg("expected data to be NULL");
    } else if ((image->data != NULL) && (expected->data != NULL)) {
        int same = memcmp(image->data, expected->data, expected->width * expected->height) == 0;
        // don't generate strings if comparison succeeds
        if (!same) {
            char *e = render_image(expected->width, expected->height, expected->data);
            char *i = render_image(image->width, image->height, image->data);
            ck_abort_msg("expected image \n%sbut got image \n%s", e, i);
            free(e);
            free(i);
        }
    }
}

static void assert_image(struct ascii_image *image, struct ascii_image *expected) {
    ck_assert_msg(image->width == expected->width, "expected width %d, but got width %d", expected->width, image->width);
    ck_assert_msg(image->height == expected->height, "expected height %d, but got height %d", expected->height, image->height);
    if ((image->name == NULL) && (expected->name != NULL)) {
        ck_abort_msg("expected name \"%s\", but was NULL", expected->name);
    } else if ((image->name != NULL) && (expected->name == NULL)) {
        ck_abort_msg("expected name NULL, but was \"%s\"", image->name);
    } else if ((image->name != NULL) && (expected->name != NULL)) {
        ck_assert_msg(strncmp(image->name, expected->name, strlen(expected->name) + 1) == 0, "expected name \"%s\", but was \"%s\"", expected->name, image->name);
    }
    assert_image_data(image, expected);
}

/* set_character tests */

START_TEST(test_set_character_NULL_image) {
    ck_assert_msg(set_character(NULL, 0, 0, '@') != SUCCESS, "set_character should return FAILURE on a NULL image");
}
END_TEST

START_TEST(test_set_character_out_of_bounds) {
    int height = 6, width = 5;
    struct ascii_image img = { .height = height, .width = width, .data = NULL, .name = NULL };
    ck_assert_msg(
            set_character(&img, -1, 0, '@') != SUCCESS,
            "set_character should return FAILURE when setting a character in a row %d of a %dx%d image",
            -1, width, height
            );
    ck_assert_msg(
            set_character(&img, 0, -1, '@') != SUCCESS,
            "set_character should return FAILURE when setting a character in a column %d of a %dx%d image",
            -1, width, height
            );
    ck_assert_msg(
            set_character(&img, height, 0, '@') != SUCCESS,
            "set_character should return FAILURE when setting a character in a row %d of a %dx%d image",
            height, width, height
            );
    ck_assert_msg(
            set_character(&img, 0, width, '@') != SUCCESS,
            "set_character should return FAILURE when setting a character in a column %d of a %dx%d image",
            width, width, height
            );
}
END_TEST

START_TEST(test_set_character_square_first_pixel) {
    int width = 3, height = 3;
    struct ascii_image *img = _create_image(height, width, "test");
    ck_assert_msg(set_character(img, 0, 0, '@') == SUCCESS,
            "set_character should return SUCCESS when setting character (r: %d, c: %d) of a %dx%d image",
            0, 0,
            width, height
            );
    assert_image(img, &(struct ascii_image) {
        .name = "test", .width = width, .height = height,
        .data = "@.." "..." "..."
    });
    _free_image(img);
}
END_TEST

START_TEST(test_set_character_square_last_pixel) {
    int width = 3, height = 3;
    struct ascii_image *img = _create_image(height, width, "test");
    ck_assert_msg(set_character(img, 2, 2, '@') == SUCCESS,
            "set_character should return SUCCESS when setting character (r: %d, c: %d) of a %dx%d image",
            2, 2,
            width, height
            );
    assert_image(img, &(struct ascii_image) {
        .name = "test", .width = width, .height = height,
        .data = "..." "..." "..@"
    });
    _free_image(img);
}
END_TEST

START_TEST(test_set_character_single_column) {
    int width = 1, height = 4;
    struct ascii_image *img = _create_image(height, width, "test");
    ck_assert_msg(set_character(img, 2, 0, '@') == SUCCESS,
            "set_character should return SUCCESS when setting character (r: %d, c: %d) of a %dx%d image",
            2, 0,
            width, height
            );
    assert_image(img, &(struct ascii_image) {
        .name = "test", .width = width, .height = height,
        .data = "..@."
    });
    _free_image(img);
}
END_TEST

START_TEST(test_set_character_rectangle) {
    int width = 4, height = 3;
    struct ascii_image *img = _create_image(height, width, "test");
    ck_assert_msg(set_character(img, 1, 2, '@') == SUCCESS,
            "set_character should return SUCCESS when setting character (r: %d, c: %d) of a %dx%d image",
            1, 2,
            width, height
            );
    assert_image(img, &(struct ascii_image) {
        .name = "test", .width = width, .height = height,
        .data = "...." "..@." "...."
    });
    _free_image(img);
}
END_TEST

START_TEST(test_set_character_basic) {
    struct ascii_image *img = _create_big_image();
    struct ascii_image *img_copy = _create_big_image();
    _set_character(img_copy, 2, 3, '=');
    ck_assert_msg(set_character(img, 2, 3, '=') == SUCCESS,
            "set_character should return SUCCESS when setting character (r: %d, c: %d) of a %dx%d image",
            2, 3,
            _big_image_width, _big_image_height
            );
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

/* draw_hollow_box tests */

START_TEST(test_draw_hollow_box_NULL_image) {
    ck_assert_msg(draw_hollow_box(NULL, 0, 0, 0, 0, '@') != SUCCESS, "draw_hollow_box should return FAILURE on a NULL image");
}
END_TEST

START_TEST(test_draw_hollow_box_width_height_too_small) {
    struct ascii_image *img = _create_small_image();
    struct ascii_image *img_copy = _create_small_image();
    ck_assert_msg(draw_hollow_box(img, 0, 0, 1, 0, '@') != SUCCESS, "draw_hollow_box should return FAILURE when drawing box with width 0");
    ck_assert_msg(draw_hollow_box(img, 0, 0, 0, 1, '@') != SUCCESS, "draw_hollow_box should return FAILURE when drawing box with height 0");
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

START_TEST(test_draw_hollow_box_one_by_one) {
    int row = 0, col = 0, height = 1, width = 1;
    struct ascii_image *img = _create_small_image();
    struct ascii_image *img_copy = _create_small_image();
    ck_assert_msg(draw_hollow_box(img, row, col, height, width, '%') == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
    _draw_hollow_box(img_copy, row, col, height, width, '%');
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

START_TEST(test_draw_hollow_box_small) {
    int row = 1, col = 1, height = 2, width = 2;
    struct ascii_image *img = _create_small_image();
    struct ascii_image *img_copy = _create_small_image();
    ck_assert_msg(draw_hollow_box(img, row, col, height, width, '&') == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
    _draw_hollow_box(img_copy, row, col, height, width, '&');
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

START_TEST(test_draw_hollow_box_basic_rectangle) {
    int row = 1, col = 1, height = 3, width = 4;
    struct ascii_image *img = _create_image(4, 5, "test");
    struct ascii_image *img_copy = _create_image(4, 5, "test");
    ck_assert_msg(draw_hollow_box(img, row, col, height, width, '@') == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
    _draw_hollow_box(img_copy, row, col, height, width, '@');
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

START_TEST(test_draw_hollow_box_full_image) {
    int row = 0, col = 0, height = _big_image_height, width = _big_image_width;
    struct ascii_image *img = _create_big_image();
    struct ascii_image *img_copy = _create_big_image();
    ck_assert_msg(draw_hollow_box(img, row, col, height, width, '@') == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
    _draw_hollow_box(img_copy, row, col, height, width, '@');
    assert_image(img, img_copy);
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

START_TEST(test_draw_hollow_box_comprehensive) {
    struct ascii_image *img = _create_big_image();
    struct ascii_image *img_copy = _create_big_image();
    {
        int row = 0, col = 0, height = 1, width = 3;
        char c = '@';
        ck_assert_msg(draw_hollow_box(img, row, col, height, width, c) == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
        _draw_hollow_box(img_copy, row, col, height, width, c);
        assert_image(img, img_copy);
    }
    {
        int row = 2, col = 2, height = 3, width = 2;
        char c = '&';
        ck_assert_msg(draw_hollow_box(img, row, col, height, width, c) == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
        _draw_hollow_box(img_copy, row, col, height, width, c);
        assert_image(img, img_copy);
    }
    {
        int row = 1, col = 1, height = 2, width = 2;
        char c = '!';
        ck_assert_msg(draw_hollow_box(img, row, col, height, width, c) == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
        _draw_hollow_box(img_copy, row, col, height, width, c);
        assert_image(img, img_copy);
    }
    {
        int row = 1, col = 1, height = 3, width = 3;
        char c = '/';
        ck_assert_msg(draw_hollow_box(img, row, col, height, width, c) == SUCCESS, "draw_hollow_box should succeed when drawing %dx%d box at (r: %d, c: %d) on %dx%d image", width, height, row, col, img_copy->width, img_copy->height);
        _draw_hollow_box(img_copy, row, col, height, width, c);
        assert_image(img, img_copy);
    }
    _free_image(img);
    _free_image(img_copy);
}
END_TEST

/* create_image tests */

START_TEST(test_create_image_NULL_name) {
    ck_assert_msg(create_image(1, 1, NULL) == NULL, "create_image should return NULL if given a NULL name");
}
END_TEST

START_TEST(test_create_image_width_height_too_small) {
    ck_assert_msg(create_image(0, 1, "test") == NULL, "create_image should return NULL if given height 0");
    ck_assert_msg(create_image(1, 0, "test") == NULL, "create_image should return NULL if given width 0");
}
END_TEST

START_TEST(test_create_image_one_by_one) {
    struct ascii_image *img;
    char *name = "test";
    img = create_image(1, 1, name);
    ck_assert_msg(img != NULL, "create_image should not return NULL for a 1x1 image");
    ck_assert_msg(img->height == 1, "create_image should set height to 1 for a 1x1 image");
    ck_assert_msg(img->width == 1, "create_image should set width to 1 for a 1x1 image");
    _free_image_safe_name(img, name);
}
END_TEST

START_TEST(test_create_image_sets_name) {
    struct ascii_image *img;
    char *name = "test";
    img = create_image(1, 1, name);
    ck_assert_msg(img != NULL, "create_image should not return NULL for a 1x1 image");
    ck_assert_msg(img->name != NULL, "create_image should set 'image->name' when given a non-NULL name");
    ck_assert_msg(strncmp(img->name, name, strlen(name) + 1) == 0, "create_image set name to \"%s\", expected \"%s\"", img->name, name);
    ck_assert_msg(img->name != name, "create_image should deep copy the 'name' parameter");
    _free_image_safe_name(img, name);
}
END_TEST

START_TEST(test_create_image_data_is_periods) {
    char *name = "test";
    struct ascii_image *expected = _create_image(3, 3, name);
    struct ascii_image *img;
    img = create_image(3, 3, name);
    ck_assert_msg(img != NULL, "create_image should not return NULL for a %dx%d image", expected->width, expected->height);
    ck_assert_msg(img->data != NULL, "create_image should set 'image->data' for a %dx%d image", expected->width, expected->height);
    assert_image_data(img, expected);
    _free_image_safe_name(img, name);
    _free_image(expected);
}
END_TEST

START_TEST(test_create_image_comprehensive) {
    char *name = "test";
    struct ascii_image *expected = _create_image(4, 4, name);
    struct ascii_image *img;
    img = create_image(4, 4, name);
    ck_assert_msg(img != NULL, "create_image should not return NULL for a %dx%d image", expected->width, expected->height);
    assert_image(img, expected);
    _free_image_safe_name(img, name);
    _free_image(expected);
}
END_TEST

START_TEST(test_create_image_malloc_failure) {
    mallocs_until_fail = 0;
    char *name = "test";
    struct ascii_image *img = create_image(1, 1, name);
    ck_assert_msg(img == NULL, "create_image should return NULL on malloc failure");
    _free_image_safe_name(img, name);
}
END_TEST

START_TEST(test_create_image_one_malloc_left) {
    mallocs_until_fail = 1;
    char *name = "test";
    struct ascii_image *img = create_image(1, 1, name);
    ck_assert_msg(img == NULL, "create_image should return NULL when only one allocation can be performed");
    _free_image_safe_name(img, name);
}
END_TEST

/* destroy_image tests */

START_TEST(test_destroy_image_NULL_image) {
    destroy_image(NULL);
}
END_TEST

START_TEST(test_destroy_image_NULL_name) {
    struct ascii_image *img = _create_image(3, 3, NULL);
    destroy_image(img);
}
END_TEST

START_TEST(test_destroy_image_NULL_data) {
    char *name = "test";
    struct ascii_image *img = _create_image(3, 3, name);
    free(img->data);
    img->data = NULL;
    destroy_image(img);
}
END_TEST

START_TEST(test_destroy_image_full_image) {
    char *name = "test";
    struct ascii_image *img = _create_image(3, 3, name);
    destroy_image(img);
}
END_TEST

/* add_extension tests */

START_TEST(test_add_extension_NULL_image) {
    ck_assert_msg(add_extension(NULL, ".png") != SUCCESS, "add_extension should return FAILURE when passed a NULL image");
}
END_TEST

START_TEST(test_add_extension_NULL_extension) {
    struct ascii_image *img = _create_image(3, 3, "image");
    ck_assert_msg(add_extension(img, NULL) != SUCCESS, "add_extension should return FAILURE when passed a NULL extension");
    _free_image(img);
}
END_TEST

START_TEST(test_add_extension_empty_name) {
    struct ascii_image *img = _create_image(3, 3, "");
    char *expected_name = ".png";
    ck_assert_msg(add_extension(img, ".png") == SUCCESS, "add_extension should return SUCCESS when passed an empty name and a valid extension");
    ck_assert_msg(img->name != NULL, "add_extension should not set 'image->name' to NULL");
    ck_assert_msg(strncmp(img->name, expected_name, strlen(expected_name) + 1) == 0, "expected name \"%s\", but got name \"%s\"", expected_name, img->name);
    _free_image(img);
}
END_TEST

START_TEST(test_add_extension_short_name) {
    struct ascii_image *img = _create_image(3, 3, "a");
    char *expected_name = "a.png";
    ck_assert_msg(add_extension(img, ".png") == SUCCESS, "add_extension should return SUCCESS when passed an empty extension");
    ck_assert_msg(img->name != NULL, "add_extension should not set 'image->name' to NULL");
    ck_assert_msg(strncmp(img->name, expected_name, strlen(expected_name) + 1) == 0, "expected name \"%s\", but got name \"%s\"", expected_name, img->name);
    _free_image(img);
}
END_TEST

START_TEST(test_add_extension_short_extension) {
    struct ascii_image *img = _create_image(3, 3, "a");
    char *expected_name = "ab";
    ck_assert_msg(add_extension(img, "b") == SUCCESS, "add_extension should return SUCCESS when passed a valid extension");
    ck_assert_msg(img->name != NULL, "add_extension should not set 'image->name' to NULL");
    ck_assert_msg(strncmp(img->name, expected_name, strlen(expected_name) + 1) == 0, "expected name \"%s\", but got name \"%s\"", expected_name, img->name);
    _free_image(img);
}
END_TEST

START_TEST(test_add_extension_comprehensive) {
    struct ascii_image *img = _create_image(3, 3, "image");
    char *expected_name = "image.tar.bz2";
    ck_assert_msg(add_extension(img, ".tar.bz2") == SUCCESS, "add_extension should return SUCCESS when passed a valid extension");
    ck_assert_msg(img->name != NULL, "add_extension should not set 'image->name' to NULL");
    ck_assert_msg(strncmp(img->name, expected_name, strlen(expected_name) + 1) == 0, "expected name \"%s\", but got name \"%s\"", expected_name, img->name);
    _free_image(img);
}
END_TEST

START_TEST(test_add_extension_alloc_failure) {
    struct ascii_image *img = _create_image(3, 3, "image");
    mallocs_until_fail = 0;
    char *name = img->name;
    ck_assert_msg(add_extension(img, ".png") == FAILURE, "add_extension should return FAILURE when allocation fails");
    ck_assert_msg(img->name == name, "add_extension should not change 'image->name' when allocation fails");
    _free_image(img);
}
END_TEST

Suite *tl4_suite(void)
{
    Suite *s = suite_create("tl4_suite");

    // set_character tests
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_NULL_image);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_out_of_bounds);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_square_first_pixel);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_square_last_pixel);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_single_column);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_rectangle);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_set_character_basic);

    // draw_hollow_box tests
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_NULL_image);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_width_height_too_small);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_one_by_one);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_small);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_basic_rectangle);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_full_image);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_draw_hollow_box_comprehensive);

    // create_image tests
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_NULL_name);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_width_height_too_small);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_one_by_one);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_sets_name);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_data_is_periods);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_comprehensive);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_malloc_failure);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_create_image_one_malloc_left);

    // destroy_image tests
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_destroy_image_NULL_image);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_destroy_image_NULL_name);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_destroy_image_NULL_data);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_destroy_image_full_image);

    // add_extension tests
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_NULL_image);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_NULL_extension);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_empty_name);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_short_name);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_short_extension);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_comprehensive);
    tcase_singleton(s, reset_mallocs_until_fail, NULL, test_add_extension_alloc_failure);

    return s;
}
