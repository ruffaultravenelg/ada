#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "styles.h"

///////////////////////
//// COMPILE COLOR ////
///////////////////////

// Defined colors
typedef struct {
    char* name;
    color_t color;
} defined_color_t;

// Defined colors
defined_color_t definedColors[] = {
    {"red", {255, 0, 0}},
    {"blue", {0, 0, 255}},
    {"green", {0, 255, 0}},
    {"yellow", {255, 255, 0}},
    {"black", {0, 0, 0}},
    {"white", {255, 255, 255}},
    {"gray", {128, 128, 128}},
    {"purple", {128, 0, 128}},
    {"orange", {255, 165, 0}},
    {"pink", {255, 192, 203}},
    {"brown", {165, 42, 42}},
    {"cyan", {0, 255, 255}},
    {"magenta", {255, 0, 255}},
    {"olive", {128, 128, 0}},
    {"lime", {0, 255, 0}},
    {"maroon", {128, 0, 0}},
    {"teal", {0, 128, 128}}
};

// Compile "red", "blue", "#FF0000" to a color_t
color_t css_compile_style_color(const char* color){

    // Defined color
    for (int i = 0; i < sizeof(definedColors) / sizeof(defined_color_t); i++){
        if (strcmp(color, definedColors[i].name) == 0){
            return definedColors[i].color;
        }
    }

    // Hexadecimal color
    if (color[0] == '#'){
        unsigned int hex;
        sscanf(color + 1, "%x", &hex);
        return (color_t){(hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF};
    }

    // Default color
    fprintf(stderr, "Unknown color: %s\n", color);
    exit(-1);

}


////////////////////////
//// COMPILE LAYOUT ////
////////////////////////
css_layout_t css_compile_layout(const char* layout){
    if (strcmp(layout, "row") == 0){
        return LAYOUT_HORIZONTAL;
    } else if (strcmp(layout, "column") == 0){
        return LAYOUT_VERTICAL;
    } else {
        fprintf(stderr, "Unknown layout: %s\n", layout);
        exit(-1);
    }
}

//////////////////////////
//// COMPILE CSS SIZE ////
//////////////////////////

css_size_t css_compile_size(const char* size){

    // Percentage
    if (size[strlen(size) - 1] == '%'){
        int converted_size = atoi(size);
        if (converted_size < 0 || converted_size > 100){
            fprintf(stderr, "Invalid percentage: %d\n", converted_size);
            exit(-1);
        }
        return (css_size_t){SIZE_PERCENT, converted_size};
    }

    // Pixel
    int converted_size = atoi(size);
    if (converted_size < 0){
        fprintf(stderr, "Invalid pixel size: %d\n", converted_size);
        exit(-1);
    }
    return (css_size_t){SIZE_PIXEL, converted_size};

}