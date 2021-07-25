/**
 * @file tl04.c
 * @author Sahit Kavukuntla
 * @brief Command-line argument & string parsing logic
 * @date 2021-04-21
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <string.h>
#include <stdio.h>
#include "tl04.h"

/*

The following macros and struct are defined in tl04.h. You will need to use these:

#define FAILURE 1
#define SUCCESS 0

struct ascii_image {
    int width;      // The number of columns in the ASCII image. Must be at least 1.
    int height;     // The number of rows in the ASCII image. Must be at least 1.
    char *name;     // The name of the ASCII image. This must be non-null, and must point to a deep copy that was allocated specifically for this struct.
    char *data;     // The image's data, which is a non-null, 1-dimensional char array of size width*height. Note: despite being a char*, this is not a string.
};

*/

/** @brief A debug function that prints an image's data.
 *
 * This function is already provided for you. You can use this function to help debug your code.
 * @param image The image to display.
 */
void print_image(struct ascii_image *image) {
    printf("Image name: %s\n", image->name);
    for (int i = 0; i < image->height * image->width; i++) {
        printf("%c", image->data[i]);
        if (i % image->width == image->width - 1) printf("\n");
    }
}


/**
 * @brief Write a character to an image using row and column coordinates.
 *
 * If image is NULL or row is not within [0, image->height - 1], or col is not within [0, image->width - 1], then return FAILURE. (You can assume image->data is not NULL, as long as image is not NULL.)
 * Otherwise, write the character c to the requested coordinates in image->data, and return SUCCESS.
 * Since image->data is a 1D array that represents a 2D image, you should use a calculation similar to the OFFSET macro from Homework 8.
 *
 * Examples:
 *
 * Assume that 'img' is a pointer to a struct ascii_image with width=3, height=3, and its data looks like this:
 *
 *      ...
 *      ...
 *      ...
 *
 * After calling set_character(img, 2, 1, 'C'), SUCCESS will be returned and the image will look like this:
 *
 *      ...
 *      ...
 *      .C.
 *
 * Then, after calling set_character(img, 1, 0, 'A'), SUCCESS will again be returned and the image will look like this:
 *
 *      ...
 *      A..
 *      .C.
 *
 * Calling set_character(img, 0, 3, 'B') or set_character(img, 4, 2, 'D') will return FAILURE and not modify the image at all.
 * set_character(NULL, 0, 0, 'X') will also return FAILURE. set_character(img, 0, 0, 'X') will return FAILURE if img->data is NULL.
 *
 * @param image A struct ascii_image that should be modified. See tl04.h for the definition of this struct.
 * @param row The row where the character will be drawn. Must be in [0, image->height - 1].
 * @param col The column where the character will be drawn. Must be in [0, image->width - 1].
 * @param c The character that will be drawn to the image.
 * @return returns FAILURE if image is NULL, or if row or col is out-of-bounds; returns SUCCESS otherwise
 */
int set_character(struct ascii_image *image, int row, int col, char c) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // These are just to turn off compiler errors initially
    // Please delete once you have implemented the function
    // UNUSED_PARAM(image);
    // UNUSED_PARAM(row);
    // UNUSED_PARAM(col);
    // UNUSED_PARAM(c);

    if (image == NULL || image->data == NULL || row < 0 || row > image->height - 1 || col < 0 || col > image->width - 1) {
    	return FAILURE;
    }

    image->data[col + row * image->width] = c;

    return SUCCESS;
}



/**
 * @brief Draw a hollowed-out rectangle to the image.
 *
 * If the provided image is NULL return FAILURE. (You may assume that if image is not NULL, then image->data is also not NULL)
 * Otherwise, use the provided row, column, width, and height coordinates to draw a hollowed-out rectangle to the image and return SUCCESS.
 * Note: it is fine if the provided rectangle coordinates result in a rectangle that is partially or completely outside the image's bounds.
 * If any pixel of the rectangle is out-of-bounds, simply do not draw it. You must not draw anything out-of-bounds.
 * For this reason, it is recommended to use set_character, which refuses to draw anything if the provided coordinates is out-of-bounds.
 * Also, draw_hollow_box should still return SUCCESS even if some or all of the rectangle is out-of-bounds.
 * (Note: none of our tests will intentionally draw out-of-bounds. However, you will still be penalized if you draw out-of-bounds when given proper input.)
 *
 * Examples:
 *
 * Assume that 'img' is a pointer to a struct ascii_image with width=7, height=5, and its data looks like this:
 *
 *      .......
 *      .......
 *      .......
 *      .......
 *      .......
 *
 * After calling draw_hollow_box(img, 2, 1, 3, 4, 'X'), SUCCESS will be returned and the image will look like this:
 *
 *      .......
 *      .......
 *      .XXXX..
 *      .X..X..
 *      .XXXX..
 *
 * Then, after calling draw_hollow_box(img, 0, 1, 1, 3, 'A') and draw_hollow_box(img, 1, 5, 3, 2, 'B'), the image looks like this:
 *
 *      .AAA...
 *      .....BB
 *      .XXXXBB
 *      .X..XBB
 *      .XXXX..
 *
 * Calling draw_hollow_box with a NULL image or an image with a NULL data should return FAILURE.
 *
 * @param image A struct ascii_image that should be modified. See tl04.h for the definition of this struct.
 * @param row The row where the top-left coordinate of the rectangle will be placed. This uses the same convention as in HW8 (row 0 = top row).
 * @param column The column where the top-left coordinate of the rectangle will be placed. This uses the same convention as in HW8 (column 0 = leftmost column).
 * @param height The height of the hollowed-out rectangle. This must be at least 1, or else draw_hollow_box will return FAILURE.
 * @param width The width of the hollowed-out rectangle. This must be at least 1, or else draw_hollow_box will return FAILURE.
 * @param c The character to use when drawing the rectangle.
 * @return Returns FAILURE if the image is NULL, or if height or width is less than 1. Otherwise, returns SUCCESS.
 */
int draw_hollow_box(struct ascii_image *image, int row, int col, int height, int width, char c) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // These are just to turn off compiler errors initially
    // Please delete once you have implemented the function
    // UNUSED_PARAM(image);
    // UNUSED_PARAM(row);
    // UNUSED_PARAM(col);
    // UNUSED_PARAM(height);
    // UNUSED_PARAM(width);
    // UNUSED_PARAM(c);

	if (image == NULL || width < 1 || height < 1) {
		return FAILURE;
	}

	for (int r = 0; r < height; r++) {
		for (int co = 0; co < width; co++) {
			if (r == 0 || r == height - 1 || co == 0 || co == width - 1) {
				set_character(image, row + r, col + co, c);
			}
		}
	}

    return SUCCESS;
}



/**
 * @brief Using the provided height, width, and name, create a new ascii_image allocated on the heap whose data is initially filled with '.' characters.
 *
 * The provided height and width must be at least 1, and the provided name must be non-NULL. If any of these conditions are not met, return NULL without allocating anything.
 * Otherwise, you should create and return a new struct ascii_image.
 * You must dynamically allocate the following things:
 *      A struct ascii_image. The image's height and width parameters should match the provided height and width. Its name and data parameters must point to the allocated name and data.
 *      A deep copy of the provided name. This name must be identical to the provided name, but it must be a separate allocation.
 *      An array of characters of size height*width. This array will be the "image" part of the ascii_image, and will be structured similarly to the HW8 videobuffer.
 *          After successfully allocating the data array, you must fill the array with '.' characters. This creates a "blank" canvas for the image.
 * If all three of these allocations succeed, you should return a pointer to the struct ascii_image, which itself contains pointers to the deep-copied name and data array.
 * If a malloc failure happens at any moment, return NULL. Also, you MUST ensure there are no memory leaks.
 * For example, if you successfully allocate the struct ascii_image and the name deep-copy, but the malloc for the image data fails, you must free the image and name before returning NULL.
 *
 * @param height The height of the image. This must be stored in the created ascii_image struct, and should be used when allocating the image data array.
 * @param width The width of the image. This must be stored in the created ascii_image struct, and should be used when allocating the image data array.
 * @param name The name of the image. This must NOT be assigned directly to the image; you MUST create a deep-copy of this name, similar to what you did in HW9.
 * @return Returns NULL if the height or width is less than 1, if the name is NULL, or if there was a malloc failure. Returns a valid ascii_image pointer otherwise.
 */
struct ascii_image *create_image(int height, int width, char *name) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // These are just to turn off compiler errors initially
    // Please delete once you have implemented the function

    if (height < 1 || width < 1) {
    	return NULL;
    }

    struct ascii_image *img = malloc(sizeof(struct ascii_image));
    if (img == NULL) {
    	return NULL;
    }

    img->data = malloc(width * height);
    if (img->data == NULL) {
    	free(img);
    	return NULL;
    }

    if (name == NULL) {
    	free(img->data);
    	free(img);
    	return NULL;
    } else {
    	img->name = malloc(strlen(name) + 1);
    	if (img->name == NULL) {
    		free(img->data);
    		free(img);
    		return NULL;
    	}
    	strcpy(img->name, name);
    }
    img->width = width;
    img->height = height;

    //memset(img, '.', sizeof(img->data));
    for (int r = 0; r < height; r++) {
    	for (int c = 0; c < width; c++) {
    		set_character(img, r, c, '.');
    	}
    }

    return img;


    //return NULL;    // Don't forget to replace this!
}



/**
 * @brief Using the provided image pointer, completely deallocate the data used by the ascii_image.
 *
 * You must deallocate not only the ascii_image struct itself, but also the ascii_image's deep-copied name and its image data array.
 * Note that it is possible for image to be NULL, as well as image->name and image->data to be NULL as well(assuming image is not NULL).
 * You should not need to handle these cases too differently, since free(NULL) is a harmless operation.
 * However, you MUST avoid using image->data or image->name if image is NULL, as this will cause a segfault.
 * You do not need to return anything. After calling destroy_image, the data that image points to must be deallocated, as well as the data that image->name and image->data previously pointed to.
 *
 * @param image The image to be destroyed.
 */
void destroy_image(struct ascii_image *image) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // This is just to turn off compiler errors initially
    // Please delete once you have implemented the function
    //UNUSED_PARAM(image);
    if (image == NULL) {
    	return;
    }
    free(image->data);
    free(image->name);
    free(image);
}

/**
 * @brief Append the extension string to the end of the name of the provided ascii_image.
 *
 * If image or extension is NULL, or if there is a malloc/realloc failure, return FAILURE. image->name MUST remain unmodified. (You can assume that image->name is not NULL, as long as image is not NULL.)
 * Otherwise, modify image->name so that it points to an allocation with the original image name and the extension concatenated together, and return SUCCESS.
 * You must only copy the characters from the extension string; you should not assign the image's name to be the extension. Also, you should not attempt to free the extension string.
 * There must be NO MEMORY LEAKS. If you allocate new space for the name+extension, make sure to deallocate the name's old space once you're done using it.
 *
 * It is required to either use malloc or realloc when implementing this function.
 * If you use realloc, make sure you remember how it works (remember that if successful, it copies the old allocation's data and frees it, and that if realloc fails, it does NOT free the old allocation).
 * You may use ANY of the functions from string.h in your code. Some of these functions will be extremely useful!
 * Make sure to allocate enough memory for both strings combined, or else you will get "write to invalid memory" valgrind errors!
 *
 * Examples:
 *
 * Assume that 'img' is a pointer to a struct ascii_image, and assume that its name is the following string allocated on the heap: {'a', 'r', 't', '\0'}, AKA "art".
 * After calling add_extension(img, ".png"), add_extension should return SUCCESS (assuming no mallocs fail).
 * Additionally, img->name should point to a new or expanded allocation with the following string: {'a', 'r', 't', '.', 'p', 'n', 'g', '\0'}, AKA "art.png".
 * Note that the extension can be any length. Calling add_extension(img, ".tar.gz") should then turn the image's name into "art.png.tar.gz".
 * add_extension(NULL, ".jpg") or add_extension(img, NULL) should both return FAILURE. Also, if a malloc fails, you should return FAILURE as well.
 *
 * @param image The image whose name should be extended. If add_extension is successful, image->name should have the extension appended to it.
 * @param extension The string that should be appended to the image's name.
 * @return Returns FAILURE if image or extension if NULL, or if there was a malloc/realloc failure. Otherwise, the image's name is extended and this function returns SUCCESS.
 */
int add_extension(struct ascii_image *image, char *extension) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // This is just to turn off compiler errors initially
    // Please delete once you have implemented the function
    // UNUSED_PARAM(image);
    // UNUSED_PARAM(extension);

    if (image == NULL || extension == NULL) {
    	return FAILURE;
    }

    char *name = image->name;

    char *newName = malloc(strlen(image->name) + strlen(extension) + 1);
    if (newName == NULL) {
    	return FAILURE;
    }

    //free(image->name);

    image->name = newName;
    strcpy(image->name, name);
    strcpy(image->name + strlen(name), extension);

    free(name);

    /////////////////////

    // char *name = realloc(image->name, strlen(image->name) + strlen(extension) + 1);

    // if (name == NULL) {
    // 	return FAILURE;
    // }

    // char *newName = strcat(image->name, extension);

    // image->name = name;
    // strcpy(image->name, newName);

    //free(newName);

    return SUCCESS;
}
