#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */

  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  char *filename = NULL;
  char *command = NULL;

 
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();

  } else if (strncmp( configuration.command, "dimension", 3) == 0) {
    dimension(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "first_pixel", 11) == 0) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    first_pixel(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "tenth_pixel", 11) == 0) {
    tenth_pixel(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "max_pixel", 9) == 0) {
    max_pixel(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "second_line", 11) == 0) {
    second_line(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "min_pixel", 9) == 0) {
    min_pixel(configuration.filenames[0]);

  } else if (strncmp(configuration.command, "min_component", 13) == 0) {
    char component = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 2 < argc && strcmp(argv[i + 1], "min_component") == 0) {
            component = argv[i + 2][0]; // ← ici on prend 'R', 'G' ou 'B'
            break;
        }
    }
    if (component == 0) {
        printf("Missing component after min_component (R, G or B)\n");
        return 1;
    }
    min_component(configuration.filenames[0], component);
  } else if (strncmp(configuration.command, "max_component", 13) == 0) {
    char *space = strchr(configuration.command, ' ');
    if (space == NULL || (space[1] != 'R' && space[1] != 'G' && space[1] != 'B')) {
        printf("Erreur : veuillez préciser la composante R, G ou B comme ceci : -c \"max_component R\"\n");
        return 1;
    }
    char component = space[1];
    max_component(configuration.filenames[0], component);
  } else if (strncmp(configuration.command, "print_pixel", 11) == 0) {
    if (argc >= 5) {
        int x = atoi(argv[argc - 2]);  // Deux derniers arguments sont X et Y
        int y = atoi(argv[argc - 1]);
        print_pixel(configuration.filenames[0], x, y);
    } else {
        fprintf(stderr, "Erreur : la commande print_pixel requiert deux arguments X et Y.\n");
    }
  }else if (strncmp(configuration.command, "color_red", 9) == 0) {
    color_red(configuration.filenames[0]);
  }else if (strncmp(configuration.command, "stat_report", 11) == 0) {
    stat_report(configuration.filenames[0]);
  }
  else if (strcmp(configuration.command, "color_green") == 0) {
    color_green(configuration.filenames[0]);
  }
  else if (strncmp(configuration.command, "color_invert", 12) == 0) {
    color_invert(configuration.filenames[0]);
  }
  else if (strcmp(command, "color_blue") == 0) {
    color_blue(configuration.filenames[0]);
  }
  else if (strncmp(configuration.command, "rotate_acw", 10) == 0) {
    rotate_acw(configuration.filenames[0]);
  }
  else if (strcmp(command, "rotate_cw") == 0) {
    rotate_cw(configuration.filenames[0]);
  }

  else if (strcmp(configuration.command, "color_gray") == 0) {
    int width, height, channels;
    unsigned char *data_in = NULL;
    // Lecture de l'image
    if (!read_image_data(configuration.filenames[0], &data_in, &width, &height, &channels)) {
        printf("Erreur lors de la lecture de l'image.\n");
        return 1;
    }
    // Application de la conversion en niveaux de gris
    color_gray(data_in, width, height, channels);
    // Sauvegarde de l'image
    if (!write_image_data("image_out.bmp", data_in, width, height)) {
        printf("Erreur lors de l'écriture de l'image.\n");
        free(data_in);
        return 1;
    }
    free(data_in);
    printf("Image convertie en niveaux de gris !\n");
  }
  else if (strcmp(command, "mirror_horizontal") == 0) {
    mirror_horizontal(configuration.filenames[0]);
  }
  else if (strcmp(command, "mirror_total") == 0) {
    mirror_total(configuration.filenames[0]);
  }
  else if (strncmp(configuration.command, "mirror_vertical", 15) == 0) {
    mirror_vertical(configuration.filenames[0]);
  }
  else if (strcmp(configuration.command, "color_gray_luminance") == 0) {
    int width, height, channels;
    unsigned char *data_in = NULL;
    if (!read_image_data(configuration.filenames[0], &data_in, &width, &height, &channels)) {
        printf("Erreur lors de la lecture de l'image.\n");
        return 1;
    }
    color_gray_luminance(data_in, width, height, channels);
    if (!write_image_data("image_out.bmp", data_in, width, height)) {
        printf("Erreur lors de l'écriture de l'image.\n");
        free(data_in);
        return 1;
    }
    free(data_in);
    printf("Image convertie en niveaux de gris (luminosité) !\n");
  }

  else if (strncmp(configuration.command, "scale_crop", 10) == 0) {
    // Recherche les 4 arguments supplémentaires
    int args_found = 0, cx = 0, cy = 0, cw = 0, ch = 0;
    for (int i = 1; i < argc - 4; i++) {
        if (strcmp(argv[i], "-c") == 0 && strcmp(argv[i + 1], "scale_crop") == 0) {
            cx = atoi(argv[i + 2]);
            cy = atoi(argv[i + 3]);
            cw = atoi(argv[i + 4]);
            ch = atoi(argv[i + 5]);
            args_found = 1;
            break;
        }
    }
    if (!args_found) {
        printf("Erreur : usage attendu : -c scale_crop center_x center_y width height\n");
        return 1;
    }
    scale_crop(configuration.filenames[0], cx, cy, cw, ch);
    printf("Image cropée !\n");
  }
  else if ( strncmp( configuration.command, "scale_nearest", 13) == 0 ) {
  /* scale_nearest() function is defined in feature.h and implemented in feature.c */
  float coeff;
  sscanf(configuration.arguments[0], "%f", &coeff);
  scale_nearest(configuration.filenames[0], coeff);
  }
  else if ( strncmp( configuration.command, "scale_bilinear", 15 ) == 0 ) {
  scale_bilinear( configuration.filenames[0], atof(configuration.arguments[0]) );
  }
  else if ( strcmp( configuration.command, "color_desaturate") == 0 ) {
  /* color_desaturate() function is defined in feature.h and implemented in feature.c */
  
  color_desaturate(configuration.filenames[0]);
}

    return 0;
}
