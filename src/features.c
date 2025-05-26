#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>
#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld()
{
    printf("Hello World !");
}

void dimension(const char *filename)
{
    unsigned char *data;
    int w, h, c;
    if (read_image_data(filename, &data, &w, &h, &c) != 0)
    {
        printf("dimension: %d, %d\n", w, h);
        free_image_data(data);
    }
}

void first_pixel(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    
    
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    if (result == 0 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }
    
    
    unsigned char r = data[0];  
    unsigned char g = data[1];    
    unsigned char b = data[2];  
    
   
    printf("first_pixel: %d, %d, %d\n", r, g, b);
    
   
    free(data);
}

void tenth_pixel(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    
    
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    
    if (result == 0 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }
    
    
    if (width < 10) {
        printf("L'image doit avoir au moins 10 pixels de largeur\n");
        free(data);
        return;
    }
    
    
    int pixel_index = 9; // 10ème pixel = index 9
    int data_index = pixel_index * 3; // Chaque pixel = 3 bytes (RGB)
    
    
    unsigned char R = data[data_index];     // Position 27
    unsigned char G = data[data_index + 1]; // Position 28
    unsigned char B = data[data_index + 2]; // Position 29
    
    
    printf("tenth_pixel: %d, %d, %d\n", R, G, B);
    
    
    free(data);
}