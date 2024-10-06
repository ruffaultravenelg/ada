#ifndef BALISES_H
#define BALISES_H

#define WINDOW_TAGNAME "window"
#define IS_WINDOW(balise) (strcmp(balise->tag_name, WINDOW_TAGNAME) == 0)
#define CONTAINER_TAGNAME "lst"
#define IS_CONTAINER(balise) (strcmp(balise->tag_name, CONTAINER_TAGNAME) == 0)

// Attributes
typedef struct {
    char* key;
    char* value;
} attribute_t;

// Balise type
typedef struct balise_t {
    char* tag_name;

    attribute_t* attributes;
    int attribute_count;
    
    struct balise_t** children;
    int child_count;
} balise_t;

/**
 * Creates a new balise with the given tag name.
 * 
 * @param tag_name The name of the tag.
 * @return A pointer to the newly created balise, or NULL if memory allocation fails.
 */
balise_t* create_balise(char* tag_name);

/**
 * Adds an attribute to the given balise.
 * 
 * @param balise The balise to which the attribute will be added.
 * @param key The key of the attribute.
 * @param value The value of the attribute.
 */
void add_attribute(balise_t* balise, char* key, char* value);

/**
 * Retrieves the value of an attribute with the given key from the balise.
 * 
 * @param balise The balise from which the attribute value will be retrieved.
 * @param key The key of the attribute.
 * @return The value of the attribute, or NULL if the attribute is not found.
 */
char* get_attribute(balise_t* balise, char* key);

/**
 * Retrieves the value of an attribute with the given key from the balise. If the attribute is not found, the default value is returned.
 * 
 * @param balise The balise from which the attribute value will be retrieved.
 * @param key The key of the attribute.
 * @param default_value The default value to be returned if the attribute is not found.
 * @return The value of the attribute, or NULL if the attribute is not found.
 */
char* get_attribute_default(balise_t* balise, char* key, char* default_value);

/**
 * Checks if the balise has an attribute with the given key.
 * 
 * @param balise The balise to be checked.
 * @param key The key of the attribute.
 * @return 1 if the attribute exists, 0 otherwise.
 */
int has_attribute(balise_t* balise, char* key);

/**
 * Adds a child balise to the parent balise.
 * 
 * @param parent The parent balise.
 * @param child The child balise to be added.
 */
void add_child(balise_t* parent, balise_t* child);

/**
 * Retrieves the child balise at the given index from the parent balise.
 * 
 * @param parent The parent balise.
 * @param index The index of the child balise.
 * @return A pointer to the child balise, or NULL if the index is out of bounds.
 */
balise_t* get_child(balise_t* parent, int index);

/**
 * Retrieves the number of children of the parent balise.
 * 
 * @param parent The parent balise.
 * @return The number of children.
 */
int get_child_count(balise_t* parent);

/**
 * Frees the memory allocated for the balise and its children.
 * 
 * @param balise The balise to be freed.
 */
void free_balise(balise_t* balise);

/**
 * Prints the balise and its children.
 * 
 * @param balise The balise to be printed.
 */
void print_balise(balise_t* balise);

#endif // BALISES_H