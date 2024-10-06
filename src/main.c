#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "graphics.h"
#include "renderer.h"
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "stylesheet.h"

#define DEFAULT_WINDOW_NAME "Window"
#define DEFAULT_WINDOW_WIDTH "800"
#define DEFAULT_WINDOW_HEIGHT "600"

void show_usage(const char *program_name) {
    printf("Usage: %s <file>\n", program_name);
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }

    // Parse file
    balise_t* root = parse_mct_file(argv[1]);

    // Throw error
    if (root == NULL){
        perror("Could not parse file");
        return -1;
    }

    // Check root type
    if (!IS_WINDOW(root)){
        perror("Root balise must be a window");
        return -1;
    }

    // Set window properties
    setTitle(get_attribute_default(root, "title", DEFAULT_WINDOW_NAME));
    setWidth(atoi(get_attribute_default(root, "width", DEFAULT_WINDOW_WIDTH)));
    setHeight(atoi(get_attribute_default(root, "height", DEFAULT_WINDOW_HEIGHT)));

    // Get stylesheet
    stylesheet_t* stylesheet = load_stylesheet(get_attribute_default(root, "stylesheet", NULL));

    // Debug
    printf("LOADED MINIMAL CONTENT TREE:\n");
    print_balise(root);

    printf("\nLOADED STYLESHEET:\n");
    print_stylesheet(stylesheet);

    // Initialize graphics
    init();

    // Render balise
    renderRoot(root, stylesheet);

    // Wait for debug purposes
    delay(10);

    // Deinitialize graphics
    deinit();

    // Free memory
    free_balise(root);

    return 0;
}
