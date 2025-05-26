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
void max_pixel(char *source_path) {
    unsigned char *data = NULL;
    int width, height, channel_count;
    
    
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    
    if (result == 0 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }
    
    int max_sum = -1;  
    int max_x = 0, max_y = 0;  
    unsigned char max_R = 0, max_G = 0, max_B = 0;  
    
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            int pixel_index = (y * width + x) * 3;
            
          
            unsigned char R = data[pixel_index];
            unsigned char G = data[pixel_index + 1];
            unsigned char B = data[pixel_index + 2];
            
            
            int sum = R + G + B;
            
            
            if (sum > max_sum) {
                max_sum = sum;
                max_x = x;
                max_y = y;
                max_R = R;
                max_G = G;
                max_B = B;
            }
        }
    }
    
    // Afficher le résultat
    printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, max_R, max_G, max_B);
    free(data);
}

void second_line(const char *source_path) {
    unsigned char *data;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels)) {
        if (height < 2) {
            printf("Error: Image height must be at least 2 pixels.\n");
            return;
        }

        int index = (1 * width + 0) * channels; // (1,0) = 1ère colonne, 2e ligne
        printf("second_line: %d, %d, %d\n", data[index], data[index+1], data[index+2]);
    } else {
        printf("Error reading image: %s\n", source_path);
    }
}

void max_component(const char *source_path, char component) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) != 1 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }

    int max_value = -1;
    int max_x = 0, max_y = 0;
    int comp_index = (component == 'R') ? 0 : (component == 'G') ? 1 : 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            int value = data[index + comp_index];
            if (value > max_value) {
                max_value = value;
                max_x = x;
                max_y = y;
            }
        }
    }
               
    printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_value);
    free(data);
}

void min_pixel(const char *source_path) {
    unsigned char *data;
    int width, height, channels;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }

    int min_sum = 256 * 3; // plus que max RGB (255+255+255)
    int min_x = 0, min_y = 0;
    int min_r = 0, min_g = 0, min_b = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            int r = data[index];
            int g = data[index + 1];
            int b = data[index + 2];

            int sum = r + g + b;
            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
                min_r = r;
                min_g = g;
                min_b = b;
            }
        }
    }

    printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, min_r, min_g, min_b);
}

void min_component(const char *source_path, const char component) {
    unsigned char *data;
    int width, height, channels;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }

    int min_value = 256;
    int min_x = 0, min_y = 0;
    int offset = 0;

    if (component == 'R') offset = 0;
    else if (component == 'G') offset = 1;
    else if (component == 'B') offset = 2;
    else {
        printf("Invalid component: %c. Use R, G or B.\n", component);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels + offset;
            int value = data[index];

            if (value < min_value) {
                min_value = value;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_value);
}

void color_red(const char *source_path) {
    unsigned char *data;
    int width, height, channels;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }

    int total_pixels = width * height;
    int size = total_pixels * channels;

    for (int i = 0; i < size; i += channels) {
        // Garder le rouge, mettre vert et bleu à 0
        // Rouge = data[i + 0], Vert = data[i + 1], Bleu = data[i + 2]
        if (channels >= 3) {
            data[i + 1] = 0; // G
            data[i + 2] = 0; // B
        }
    }

    if (!write_image_data("image_out.bmp", data, width, height)) {
        printf("Error writing image_out.bmp\n");
    } else {
        printf("Red-only image written to image_out.bmp\n");
    }
}