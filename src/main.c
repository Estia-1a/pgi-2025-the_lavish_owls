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

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
        filename = argv[i + 1];
        i++; // Skip next argument car on l'a déjà traité
    } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
        command = argv[i + 1];
        i++; // Skip next argument car on l'a déjà traité
    }
  }
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
}
    return 0;
}