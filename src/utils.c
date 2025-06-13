#include <estia-image.h>
#include <stddef.h>  // Pour NULL
#include <stdio.h>   // Pour printf
#include <stdlib.h>  // Pour free
#include "utils.h"

/**
 * @brief Here, you have to define functions of the pixel struct : getPixel and setPixel.
 * 
 */

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height,
                    const unsigned int n, const unsigned int x, const unsigned int y) {
    if (!data || x >= width || y >= height || n < 3) {
        return NULL;
    }

    unsigned int index = (y * width + x) * n;
    return (pixelRGB*) &data[index];
}

void set_pixel(unsigned char* data, const unsigned int width, const unsigned int height,
               const unsigned int n, const unsigned int x, const unsigned int y, pixelRGB* pixel) {
    if (!data || !pixel || x >= width || y >= height || n < 3) {
        return;
    }

    unsigned int index = (y * width + x) * n;
    data[index + 0] = pixel->R;
    data[index + 1] = pixel->G;
    data[index + 2] = pixel->B;
}

void print_pixel(const char* filename, int x, int y) {
    unsigned char* data = NULL;
    int width, height, n;

    if (read_image_data(filename, &data, &width, &height, &n) == 0) {
        fprintf(stderr, "Error reading image: %s\n", filename);
        return;
    }

    pixelRGB* pixel = get_pixel(data, width, height, n, x, y);
    if (pixel) {
        printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    } else {
        fprintf(stderr, "Invalid coordinates (%d, %d) for image size %dx%d\n", x, y, width, height);
    }

    free(data); // Always free memory allocated by read_image_data
}







