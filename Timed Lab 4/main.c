/**
 * @file main.c
 * @author YOUR TAs!
 * @date 2021
 */
#include "tl04.h"

/**
 * @brief A main function that you can use for testing.
 * 
 * Implementing this function is NOT necessary for the timed lab.
 * You can use this if you want to create custom tests.
 * We have included a basic test as an example.
 *
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int main(int argc, char const *argv[])
{
    UNUSED_PARAM(argc);
    UNUSED_PARAM(argv);

    // Creates a 5x5 image called "art", whose data is initially filled with periods.
    struct ascii_image *image = create_image(5, 5, "art");

    // Sets a character in the top-right corner with 'X'.
    set_character(image, 0, 4, 'X');

    // Draws a 3x3 hollow rectangle in the bottom-left corner.
    draw_hollow_box(image, 2, 0, 3, 3, 'O');

    // Adds the .png extension to the image's name.
    add_extension(image, ".png");

    // Prints the image's name and data.
    print_image(image);

    // Destroy the image, avoiding memory leaks.
    destroy_image(image);
}
