#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>
#include "features.h"
#include "utils.h"
#include <limits.h>

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
    int width=0, height=0, channel_count= 0 ;
    
    
    int result = read_image_data(source_path, &data, &width, &height, &channel_count);
    
    printf("tenth_pixel: %d, %d, %d", data[27], data[28], data[29]);
    
    
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


void color_green(const char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(source_path, &data, &width, &height, &channels) != 1 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }

    // Garde uniquement la composante verte
    for (int i = 0; i < width * height * channels; i += channels) {
        data[i] = 0;         // R = 0
        // data[i+1] = G (on garde)
        data[i + 2] = 0;     // B = 0
        // Si image avec alpha, on ne touche pas à data[i+3]
    }

    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'ecriture de l'image\n");
    } else {
        printf("L'image avec seulement le vert a ete enregistree dans image_out.bmp\n");
    }

    free(data);
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

void stat_report(const char *filename) {
    unsigned char *data = NULL;
    int width, height, channels;

    if (read_image_data(filename, &data, &width, &height, &channels) == 0) {
        fprintf(stderr, "Error reading image: %s\n", filename);
        return;
    }

    int max_pixel_sum = -1, min_pixel_sum = 256 * 3;
    pixelRGB max_pixel = {0, 0, 0}, min_pixel = {0, 0, 0};
    unsigned char max_r = 0, max_g = 0, max_b = 0;
    unsigned char min_r = 255, min_g = 255, min_b = 255;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelRGB *p = get_pixel(data, width, height, channels, x, y);
            if (!p) continue;

            int pixel_sum = p->R + p->G + p->B;

            if (pixel_sum > max_pixel_sum) {
                max_pixel_sum = pixel_sum;
                max_pixel = *p;
            }
            if (pixel_sum < min_pixel_sum) {
                min_pixel_sum = pixel_sum;
                min_pixel = *p;
            }

            if (p->R > max_r) max_r = p->R;
            if (p->G > max_g) max_g = p->G;
            if (p->B > max_b) max_b = p->B;

            if (p->R < min_r) min_r = p->R;
            if (p->G < min_g) min_g = p->G;
            if (p->B < min_b) min_b = p->B;
        }
    }

    FILE *f = fopen("stat_report.txt", "w");
    if (!f) {
        fprintf(stderr, "Unable to write stat_report.txt\n");
        free(data);
        return;
    }

    fprintf(f, "max_pixel: R=%d G=%d B=%d\n", max_pixel.R, max_pixel.G, max_pixel.B);
    fprintf(f, "min_pixel: R=%d G=%d B=%d\n", min_pixel.R, min_pixel.G, min_pixel.B);
    fprintf(f, "max_component R: %d\n", max_r);
    fprintf(f, "max_component G: %d\n", max_g);
    fprintf(f, "max_component B: %d\n", max_b);
    fprintf(f, "min_component R: %d\n", min_r);
    fprintf(f, "min_component G: %d\n", min_g);
    fprintf(f, "min_component B: %d\n", min_b);

    fclose(f);
    free(data);
}

void color_gray(unsigned char *data, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            unsigned char r = data[idx + 0];
            unsigned char g = data[idx + 1];
            unsigned char b = data[idx + 2];
            unsigned char gray = (r + g + b) / 3;
            data[idx + 0] = gray;
            data[idx + 1] = gray;
            data[idx + 2] = gray;
            // Si channels == 4, on laisse l'alpha intact
        }
    }
}

void color_invert(const char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    // Lire les données de l'image
    if (read_image_data(source_path, &data, &width, &height, &channels) != 1 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }

    // Inverser les couleurs pour chaque pixel
    for (int i = 0; i < width * height * channels; i += channels) {
        data[i] = 255 - data[i];         // Inverser R
        data[i + 1] = 255 - data[i + 1]; // Inverser G
        data[i + 2] = 255 - data[i + 2]; // Inverser B
        // Si il y a un canal alpha (channels == 4), on ne le touche pas
    }

    // Écrire l'image inversée
    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur lors de l'ecriture de l'image\n");
    } else {
        printf("L'image avec les couleurs inversees a ete enregistree dans image_out.bmp\n");
    }

    // Libérer la mémoire
    free(data);
}
void color_blue(const char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }
    
    int total_pixels = width * height;
    int size = total_pixels * channels;
    
    for (int i = 0; i < size; i += channels) {
        // Garder le bleu, mettre rouge et vert à 0
        // Rouge = data[i + 0], Vert = data[i + 1], Bleu = data[i + 2]
        if (channels >= 3) {
            data[i + 0] = 0; // R
            data[i + 1] = 0; // G
            // data[i + 2] reste inchangé (B)
        }
    }
    
    if (!write_image_data("image_out.bmp", data, width, height)) {
        printf("Error writing image\n");
    }
    
    free(data);
}

void rotate_acw(const char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    // Lire les données de l'image
    if (read_image_data(source_path, &data, &width, &height, &channels) != 1 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }

    // Après rotation 90° anti-horaire :
    // - nouvelle largeur = ancienne hauteur
    // - nouvelle hauteur = ancienne largeur
    int new_width = height;
    int new_height = width;

    // Créer un nouveau buffer pour l'image rotée
    unsigned char *rotated_data = malloc(new_width * new_height * channels);
    if (rotated_data == NULL) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    // Effectuer la rotation 90° anti-horaire
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Position dans l'image originale
            int original_index = (y * width + x) * channels;
            
            // Position dans l'image rotée
            // Pour rotation 90° anti-horaire : (x, y) -> (y, width-1-x)
            int new_x = y;
            int new_y = width - 1 - x;
            int rotated_index = (new_y * new_width + new_x) * channels;
            
            // Copier les données pixel par pixel
            for (int c = 0; c < channels; c++) {
                rotated_data[rotated_index + c] = data[original_index + c];
            }
        }
    }

    // Écrire l'image rotée
    if (write_image_data("image_out.bmp", rotated_data, new_width, new_height) == 0) {
        printf("Erreur lors de l'ecriture de l'image\n");
    } else {
        printf("L'image avec rotation 90° anti-horaire a ete enregistree dans image_out.bmp\n");
    }

    // Libérer la mémoire
    free(data);
    free(rotated_data);
}

void rotate_cw(const char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }
    
    // Après rotation 90° horaire : largeur devient hauteur, hauteur devient largeur
    int new_width = height;
    int new_height = width;
    
    // Allouer mémoire pour l'image tournée
    unsigned char *rotated_data = malloc(new_width * new_height * channels);
    if (rotated_data == NULL) {
        printf("Error: Memory allocation failed\n");
        free(data);
        return;
    }
    
    // Rotation 90° sens horaire
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Position dans l'image originale
            int original_index = (y * width + x) * channels;
            
            // Position dans l'image tournée
            // Formule rotation 90° horaire: (x,y) -> (height-1-y, x)
            int new_x = height - 1 - y;
            int new_y = x;
            int rotated_index = (new_y * new_width + new_x) * channels;
            
            // Copier tous les canaux (RGB ou RGBA)
            for (int c = 0; c < channels; c++) {
                rotated_data[rotated_index + c] = data[original_index + c];
            }
        }
    }

    // Sauvegarder l'image tournée
    if (!write_image_data("image_out.bmp", rotated_data, new_width, new_height)) {
        printf("Error writing image\n");
    }
    
    // Libérer la mémoire
    free(data);
    free(rotated_data);
}

void color_gray_luminance(unsigned char *data, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            unsigned char r = data[idx + 0];
            unsigned char g = data[idx + 1];
            unsigned char b = data[idx + 2];
            unsigned char gray = (unsigned char)(0.21 * r + 0.72 * g + 0.07 * b);
            data[idx + 0] = gray;
            data[idx + 1] = gray;
            data[idx + 2] = gray;
            // Si RGBA (channels == 4), on laisse l'alpha intact
        }
    }
}

void mirror_horizontal(const char *source_path) {
    unsigned char *data;
    int width, height, channels;
    
    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Error reading image: %s\n", source_path);
        return;
    }
    
    // Allouer mémoire pour l'image miroir
    unsigned char *mirrored_data = malloc(width * height * channels);
    if (mirrored_data == NULL) {
        printf("Error: Memory allocation failed\n");
        free(data);
        return;
    }
    
    // Miroir horizontal : inverser les colonnes (gauche <-> droite)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Position dans l'image originale
            int original_index = (y * width + x) * channels;
            
            // Position dans l'image miroir
            // Miroir horizontal: (x,y) -> (width-1-x, y)
            int new_x = width - 1 - x;
            int new_y = y;
            int mirrored_index = (new_y * width + new_x) * channels;
            
            // Copier tous les canaux (RGB ou RGBA)
            for (int c = 0; c < channels; c++) {
                mirrored_data[mirrored_index + c] = data[original_index + c];
            }
        }
    }
    
    // Sauvegarder l'image miroir
    if (!write_image_data("image_out.bmp", mirrored_data, width, height)) {
        printf("Error writing image\n");
    }
    
    // Libérer la mémoire
    free(data);
    free(mirrored_data);
}

void mirror_total(char* filename) {
    int width, height, channels;
    unsigned char *data_in = NULL;
    
    // Lecture de l'image
    if (!read_image_data(filename, &data_in, &width, &height, &channels)) {
        printf("Erreur lors de la lecture de l'image.\n");
        return;
    }

    
    // Allocation pour l'image de sortie
    unsigned char *data_out = malloc(width * height * channels);
    if (!data_out) {
        printf("Erreur d'allocation mémoire.\n");
        free(data_in);
        return;
    }
    
    // Application de la symétrie complète
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Position dans l'image originale
            int src_index = (y * width + x) * channels;
            // Position dans l'image symétrique (miroir horizontal ET vertical)
            int dst_index = ((height - 1 - y) * width + (width - 1 - x)) * channels;
            
            // Copie des pixels
            for (int c = 0; c < channels; c++) {
                data_out[dst_index + c] = data_in[src_index + c];
            }
        }
    }
    
    // Sauvegarde de l'image
    if (!write_image_data("image_out.bmp", data_out, width, height)) {
        printf("Erreur lors de l'écriture de l'image.\n");
    } else {
        printf("Image avec symetrie complete sauvegardee !\n");
    }
    
    free(data_in);
    free(data_out);

}

void mirror_vertical(const char *source_path) {
    unsigned char *data = NULL;
    int width, height, channels;

    // Lire les données de l'image
    if (read_image_data(source_path, &data, &width, &height, &channels) != 1 || data == NULL) {
        printf("Erreur lors de la lecture de l'image\n");
        return;
    }

    // Créer un nouveau buffer pour l'image miroir
    unsigned char *mirrored_data = malloc(width * height * channels);
    if (mirrored_data == NULL) {
        printf("Erreur d'allocation mémoire\n");
        free(data);
        return;
    }

    // Effectuer la symétrie verticale (retourner l'image verticalement)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Position dans l'image originale
            int original_index = (y * width + x) * channels;
            
            // Position dans l'image miroir
            // Pour symétrie verticale : (x, y) -> (x, height-1-y)
            int mirror_x = x;
            int mirror_y = height - 1 - y;
            int mirrored_index = (mirror_y * width + mirror_x) * channels;
            
            // Copier les données pixel par pixel
            for (int c = 0; c < channels; c++) {
                mirrored_data[mirrored_index + c] = data[original_index + c];
            }
        }
    }

    // Écrire l'image miroir
    if (write_image_data("image_out.bmp", mirrored_data, width, height) == 0) {
        printf("Erreur lors de l'ecriture de l'image\n");
    } else {
        printf("L'image avec symétrie verticale (haut-bas inversé) a ete enregistree dans image_out.bmp\n");
    }

    // Libérer la mémoire
    free(data);
    free(mirrored_data);
}


void scale_crop(const char *filename, int center_x, int center_y, int crop_width, int crop_height) {
    int width, height, channels;
    unsigned char *data_in = NULL;



    // Calcul des coordonnées du rectangle de crop
    int x0 = center_x - crop_width / 2;
    int y0 = center_y - crop_height / 2;

    // Allocation du buffer de sortie
    unsigned char *data_out = (unsigned char*)malloc(crop_width * crop_height * channels);

     // Copie avec gestion des bords
    for (int y = 0; y < crop_height; ++y) {
        int in_y = y0 + y;
        for (int x = 0; x < crop_width; ++x) {
            int in_x = x0 + x;
            int out_idx = (y * crop_width + x) * channels;

            if (in_x >= 0 && in_x < width && in_y >= 0 && in_y < height) {
                int in_idx = (in_y * width + in_x) * channels;
                for (int c = 0; c < channels; ++c) {
                    data_out[out_idx + c] = data_in[in_idx + c];
                }
            } else {
                // Remplir en noir (ou transparent si alpha)
                for (int c = 0; c < channels; ++c)
                    data_out[out_idx + c] = 0;
                }
        }
    }
        
    // Sauvegarde l'image cropée
        if (!write_image_data("image_out.bmp", data_out, crop_width, crop_height)) {
            printf("Erreur lors de l'écriture de l'image.\n");
        }
        free(data_in);
        free(data_out);
}

void scale_nearest(char *source_path, float coeff){
    unsigned char* data;
    unsigned char* nouvelle_memoire;
    int width, height, channel_count, new_width, new_height;
    int x_avant, y_avant;
    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier : %s\n", source_path);
    }
    else{

        new_width = (int)(width*coeff);
        new_height = (int)(height*coeff);

        nouvelle_memoire = (unsigned char*)malloc(new_width*new_height*channel_count);


        int i,j;
        for(j=0; j<new_height; j++){
            for(i=0; i<new_width; i++){

                x_avant = (int)((float)i/coeff + 0.5);
                y_avant = (int)((float)j/coeff + 0.5);

                if(x_avant < 0){
                    x_avant = 0;
                }

                if(x_avant > width-1){
                    x_avant = width -1;
                }

                if(y_avant < 0){
                    y_avant = 0;
                }

                if(y_avant > height-1){
                    y_avant = height -1;
                }

                pixelRGB *pixel_avant = get_pixel(data, width, height, 
                                        channel_count, x_avant, y_avant);
                pixelRGB *pixel_apres = get_pixel(nouvelle_memoire, new_width, new_height, 
                                        channel_count, i, j);
                
                                        pixel_apres->R = pixel_avant->R;
                                        pixel_apres->G = pixel_avant->G;
                                        pixel_apres->B = pixel_avant->B;

            }
        }
    }
     if (write_image_data("image_out.bmp", nouvelle_memoire, new_width, new_height) == 0) {
            printf("Erreur 2 avec le fichier : %s\n", source_path);
        }
       
    free_image_data(data);
    free(nouvelle_memoire);
}

void color_desaturate(char *source_path){

    unsigned char* data;
    int width, height, channel_count;

    if (read_image_data(source_path, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier : %s\n", source_path);
    }
    else{
        int i, j;
        int min_val, max_val, new_val;

        for(j=0; j<height; j++){
            for(i=0; i<width; i++){

                pixelRGB *pixel = get_pixel(data, width, height, 
                channel_count, i, j );

                if(pixel !=NULL){

                    min_val=pixel->R;

                    if(pixel->G < min_val) min_val = pixel->G;
                    if(pixel->B < min_val) min_val = pixel->B;

                    min_val=pixel->R;
                    
                    if(pixel->G > max_val) max_val = pixel->G;
                    if(pixel->B > max_val) max_val = pixel->B;
                    new_val = (max_val + min_val) / 2;

                    pixel->R = new_val;
                    pixel->G = new_val;
                    pixel->B = new_val;
                }

            }
        }
    }
    if (write_image_data("image_out.bmp", data, width, height) == 0) {
        printf("Erreur 2 avec le fichier : %s\n", source_path);
    }
    
free_image_data(data);
}