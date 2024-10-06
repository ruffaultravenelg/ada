#ifndef STYLESHEET_H
#define STYLESHEET_H

#include "graphics.h"

typedef struct {
    char* key;
    char* value;
} style_attribute_t;

typedef struct {
    char* name;
    style_attribute_t* attributes;
    int attribute_count;
} style_t;

typedef struct {
    style_t** styles;
    int style_count;
} stylesheet_t;


/**
 * @brief Loads a stylesheet from the specified file path.
 *
 * This function reads a stylesheet from the given file path and returns a pointer
 * to a `stylesheet_t` structure containing the parsed stylesheet data.
 *
 * @param path The file path to the stylesheet to be loaded.
 * @return A pointer to a `stylesheet_t` structure containing the loaded stylesheet data.
 *         Returns NULL if the stylesheet could not be loaded.
 */
stylesheet_t *load_stylesheet(const char *path);

/**
 * @brief Frees the memory allocated for the given stylesheet.
 *
 * This function frees the memory allocated for the given stylesheet and all its
 * associated styles and attributes.
 *
 * @param stylesheet The stylesheet to be freed.
 */
void free_stylesheet(stylesheet_t *stylesheet);

/**
 * @brief Retrieves the style with the specified name from the given stylesheet.
 *
 * This function create a new style, containing all style_attribute_t of all styles pointed by `name`
 *
 * @param stylesheet The stylesheet from which the style will be retrieved.
 * @param name The name of the style to be retrieved.
 * @return A pointer to the created style, or NULL if the style is not found.
 */
style_t *get_style(stylesheet_t *stylesheet, const char *name);

/**
 * @brief Frees the memory allocated for a style_t object.
 * 
 * This function releases all resources associated with the given style_t object.
 * After calling this function, the style_t object should not be used.
 * 
 * @param style A pointer to the style_t object to be freed.
 */
void free_style(style_t *style);

/**
 * @brief Retrieves the value of the attribute with the specified key from the given style.
 *
 * This function retrieves the value of the attribute with the specified key from the given style.
 *
 * @param style The style from which the attribute value will be retrieved.
 * @param key The key of the attribute.
 * @param default_value The default value to be returned if the attribute is not found.
 * @return The value of the attribute, or NULL if the attribute is not found.
 */
char* get_style_attribute(style_t *style, const char *key, const char *default_value);

/**
 * @brief Prints the given style to the standard output.
 *
 * This function prints the given style to the standard output.
 *
 * @param style The style to be printed.
 */
void print_stylesheet(stylesheet_t* stylesheet);

#endif // STYLESHEET_H