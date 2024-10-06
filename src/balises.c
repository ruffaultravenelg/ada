#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balises.h"
#include <string.h>

/**
 * Creates a new balise with the given tag name.
 * 
 * @param tag_name The name of the tag.
 * @return A pointer to the newly created balise, or NULL if memory allocation fails.
 */
balise_t* create_balise(char* tag_name) {
    balise_t* new_balise = (balise_t*)malloc(sizeof(balise_t));
    if (new_balise == NULL) {
        return NULL;
    }
    new_balise->tag_name = tag_name;
    new_balise->attributes = NULL;
    new_balise->attribute_count = 0;
    new_balise->children = NULL;
    new_balise->child_count = 0;
    return new_balise;
}

/**
 * Adds an attribute to the given balise.
 * 
 * @param balise The balise to which the attribute will be added.
 * @param key The key of the attribute.
 * @param value The value of the attribute.
 */
void add_attribute(balise_t* balise, char* key, char* value) {
    balise->attributes = (attribute_t*)realloc(balise->attributes, (balise->attribute_count + 1) * sizeof(attribute_t));
    if (balise->attributes == NULL) {
        return;
    }
    balise->attributes[balise->attribute_count].key = key;
    balise->attributes[balise->attribute_count].value = value;
    balise->attribute_count++;
}

/**
 * Retrieves the value of an attribute with the given key from the balise.
 * 
 * @param balise The balise from which the attribute value will be retrieved.
 * @param key The key of the attribute.
 * @return The value of the attribute, or NULL if the attribute is not found.
 */
char* get_attribute(balise_t* balise, char* key) {
    for (int i = 0; i < balise->attribute_count; i++) {
        if (strcmp(balise->attributes[i].key, key) == 0) {
            return balise->attributes[i].value;
        }
    }
    return NULL;
}

/**
 * Checks if the balise has an attribute with the given key.
 * 
 * @param balise The balise to be checked.
 * @param key The key of the attribute.
 * @return 1 if the attribute exists, 0 otherwise.
 */
int has_attribute(balise_t* balise, char* key) {
    for (int i = 0; i < balise->attribute_count; i++) {
        if (strcmp(balise->attributes[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Adds a child balise to the parent balise.
 * 
 * @param parent The parent balise.
 * @param child The child balise to be added.
 */
void add_child(balise_t* parent, balise_t* child) {
    parent->children = (balise_t**)realloc(parent->children, (parent->child_count + 1) * sizeof(balise_t*));
    if (parent->children == NULL) {
        return;
    }
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

/**
 * Retrieves the child balise at the given index from the parent balise.
 * 
 * @param parent The parent balise.
 * @param index The index of the child balise.
 * @return A pointer to the child balise, or NULL if the index is out of bounds.
 */
balise_t* get_child(balise_t* parent, int index) {
    if (index < 0 || index >= parent->child_count) {
        return NULL;
    }
    return parent->children[index];
}

/**
 * Retrieves the number of children of the parent balise.
 * 
 * @param parent The parent balise.
 * @return The number of children.
 */
int get_child_count(balise_t* parent) {
    return parent->child_count;
}

/**
 * Frees the memory allocated for the balise and its children.
 * 
 * @param balise The balise to be freed.
 */
void free_balise(balise_t* balise) {
    if (balise == NULL) {
        return;
    }
    for (int i = 0; i < balise->child_count; i++) {
        free_balise(balise->children[i]);
    }
    free(balise->children);
    free(balise->attributes);
    free(balise);
}

/**
 * Prints the balise and its children with indentation based on depth.
 * 
 * @param balise The balise to be printed.
 * @param tab_count The number of tabs to indent.
 */
void print_balise_depth(balise_t* balise, int tab_count) {
    for (int i = 0; i < tab_count; i++) {
        printf("    ");
    }
    printf("<%s", balise->tag_name);
    for (int i = 0; i < balise->attribute_count; i++) {
        printf(" %s=\"%s\"", balise->attributes[i].key, balise->attributes[i].value);
    }
    printf(">\n");
    if (!IS_CONTAINER(balise) && !IS_WINDOW(balise)) {
        return;
    }
    for (int i = 0; i < balise->child_count; i++) {
        print_balise_depth(balise->children[i], tab_count + 1);
    }
    for (int i = 0; i < tab_count; i++) {
        printf("    ");
    }
    printf("</%s>\n", balise->tag_name);
}

/**
 * Prints the balise and its children.
 * 
 * @param balise The balise to be printed.
 */
void print_balise(balise_t* balise){
    print_balise_depth(balise, 0);
}

/**
 * Retrieves the value of an attribute with the given key from the balise. If the attribute is not found, the default value is returned.
 * 
 * @param balise The balise from which the attribute value will be retrieved.
 * @param key The key of the attribute.
 * @param default_value The default value to be returned if the attribute is not found.
 * @return The value of the attribute, or NULL if the attribute is not found.
 */
char* get_attribute_default(balise_t* balise, char* key, char* default_value){
    if (has_attribute(balise, key)){
        return get_attribute(balise, key);
    }
    return default_value;
}