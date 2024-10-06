#ifndef STYLES_H
#define STYLES_H

#include "stylesheet.h"
#include "balises.h"
#include "graphics.h"

/**
 * @brief Compiles a color from a given string representation.
 *
 * This function takes a string representing a color and converts it into a 
 * color_t type. The string should be in a format that the function can 
 * recognize and parse.
 *
 * @param color A string representing the color to be compiled.
 * @return A color_t value representing the compiled color.
 */
color_t css_compile_style_color(const char* color);

// Layout types
typedef enum {
    LAYOUT_VERTICAL,
    LAYOUT_HORIZONTAL
} css_layout_t;


/**
 * @brief Compiles a layout configuration from a given string.
 *
 * This function takes a string representation of a layout and compiles it into
 * a css_layout_t structure. The layout string should specify the arrangement of
 * elements, where "row" indicates a horizontal layout and "column" indicates
 * a vertical layout.
 *
 * @param layout A string representing the layout configuration.
 *               - "row": Horizontal layout
 *               - "column": Vertical layout
 * @return A compiled css_layout_t structure based on the provided layout string.
 */
css_layout_t css_compile_layout(const char* layout);

// Size type
typedef enum{
    SIZE_PIXEL,
    SIZE_PERCENT
} css_size_type_t;
typedef struct {
    css_size_type_t type;
    int value;
} css_size_t;

css_size_t css_compile_size(const char* size);

#endif // STYLES_H