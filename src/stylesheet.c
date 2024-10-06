#include "stylesheet.h"
#include "tokeniser.h"
#include "reader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////
//// ATTRIBUTE ////
///////////////////
style_attribute_t create_attribute(char* key, char* value) {
    style_attribute_t attribute;
    attribute.key = key;
    attribute.value = value;
    return attribute;
}
void free_attribute(style_attribute_t attribute) {
    free(attribute.key);
    free(attribute.value);
}
void print_attribute(style_attribute_t attribute) {
    printf("%s: %s\n", attribute.key, attribute.value);
}

///////////////
//// STYLE ////
///////////////
style_t* create_style(const char* name) {
    style_t* style = (style_t*)malloc(sizeof(style_t));
    if (style == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    style->name = strdup(name);
    style->attributes = NULL;
    style->attribute_count = 0;
    return style;
}
void add_attribute_to_style(style_t* style, style_attribute_t attribute) {
    style->attributes = (style_attribute_t*)realloc(style->attributes, (style->attribute_count + 1) * sizeof(style_attribute_t));
    if (style->attributes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    style->attributes[style->attribute_count] = attribute;
    style->attribute_count++;
}
char* get_style_attribute(style_t *style, const char *key, const char *default_value) {
    for (int i = 0; i < style->attribute_count; i++) {
        if (strcmp(style->attributes[i].key, key) == 0) {
            return style->attributes[i].value;
        }
    }
    return strdup(default_value);
}
void free_style(style_t* style) {
    free(style->name);
    for (int i = 0; i < style->attribute_count; i++) {
        free_attribute(style->attributes[i]);
    }
    free(style->attributes);
    free(style);
}
void print_style(style_t* style) {
    printf("%s{\n", style->name);
    for (int i = 0; i < style->attribute_count; i++) {
        printf("\t");
        print_attribute(style->attributes[i]);
    }
    printf("}\n");
}


////////////////////
//// STYLESHEET ////
////////////////////
stylesheet_t* create_stylesheet() {
    stylesheet_t* stylesheet = (stylesheet_t*)malloc(sizeof(stylesheet_t));
    if (stylesheet == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    stylesheet->styles = NULL;
    stylesheet->style_count = 0;
    return stylesheet;
}
void add_style_to_stylesheet(stylesheet_t* stylesheet, style_t* style) {
    stylesheet->styles = (style_t**)realloc(stylesheet->styles, (stylesheet->style_count + 1) * sizeof(style_t*));
    if (stylesheet->styles == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }
    stylesheet->styles[stylesheet->style_count] = style;
    stylesheet->style_count++;
}
void free_stylesheet(stylesheet_t *stylesheet) {
    for (int i = 0; i < stylesheet->style_count; i++) {
        free_style(stylesheet->styles[i]);
    }
    free(stylesheet->styles);
    free(stylesheet);
}
void print_stylesheet(stylesheet_t* stylesheet) {
    for (int i = 0; i < stylesheet->style_count; i++) {
        print_style(stylesheet->styles[i]);
    }
}
style_t* search_style(stylesheet_t* stylesheet, const char* name) {
    for (int i = 0; i < stylesheet->style_count; i++) {
        if (strcmp(stylesheet->styles[i]->name, name) == 0) {
            return stylesheet->styles[i];
        }
    }
    return NULL;
}

// Create a new style, add all style_attribute_t of all styles pointed by `name` (name is a string of the form "style1 style2 style3")
style_t *get_style(stylesheet_t *stylesheet, const char *name){

    // Create new style
    style_t* new_style = create_style(name);

    // Empty name
    if (name == NULL){
        return new_style;
    }

    // Split name
    char* token = strtok(strdup(name), " ");
    while (token != NULL) {
        style_t* style = search_style(stylesheet, token);
        if (style != NULL){
            for (int i = 0; i < style->attribute_count; i++) {
                add_attribute_to_style(new_style, style->attributes[i]);
            }
        }
        token = strtok(NULL, " ");
    }

    return new_style;

}

stylesheet_t* load_sample_stylesheet() {

    stylesheet_t* stylesheet = create_stylesheet();

    style_t* style = create_style("a");
    add_attribute_to_style(style, create_attribute("backcolor", "#ff0000"));
    add_attribute_to_style(style, create_attribute("width", "50px"));
    add_attribute_to_style(style, create_attribute("height", "50px"));
    add_style_to_stylesheet(stylesheet, style);

    style_t* style2 = create_style("b");
    add_attribute_to_style(style2, create_attribute("backcolor", "#00ff00"));
    add_attribute_to_style(style2, create_attribute("width", "50px"));
    add_attribute_to_style(style2, create_attribute("height", "50px"));
    add_style_to_stylesheet(stylesheet, style2);

    return stylesheet;

}

// Parse tokens and fill style
void parse_css_attributes(TokenList_t* tokens, size_t* index, style_t* style) {

    while (*index < tokens->count) {

        // Get token
        Token_t token = get_token(tokens, *index);

        // Check for closing balise
        if (token.type == TOKEN_TYPE_CURLY_CLOSE) {
            break;
        }

        // Get attribute name
        if (token.type != TOKEN_TYPE_TEXT) {
            fprintf(stderr, "Expected attribute name\n");
            exit(-1);
        }
        char* attribute_name = strdup(token.value);
        (*index)++;

        // Check for value
        if (get_token(tokens, *index).type != TOKEN_TYPE_CSS_VALUE) {
            fprintf(stderr, "Expected ':'\n");
            exit(-1);
        }
        char* attribute_value = strdup(get_token(tokens, *index).value);
        (*index)++;

        // Add attribute
        add_attribute_to_style(style, create_attribute(attribute_name, attribute_value));

    }

}

// Parse tokens and fill the stylesheet
void parse_tokens(TokenList_t tokens, stylesheet_t* stylesheet) {
 
    for (size_t i = 0; i < tokens.count; i++) {

        // Get style name
        Token_t* token = tokens.tokens[i];
        if (token->type != TOKEN_TYPE_TEXT) {
            fprintf(stderr, "Expected style name\n");
            exit(-1);
        }

        // Create style
        style_t* style = create_style(token->value);

        // Check for '{'
        i++;
        if (i >= tokens.count || tokens.tokens[i]->type != TOKEN_TYPE_CURLY_OPEN) {
            fprintf(stderr, "Expected '{'\n");
            exit(-1);
        }

        // Get attributes
        i++;
        parse_css_attributes(&tokens, &i, style);

        // Check for '}'
        if (i >= tokens.count || tokens.tokens[i]->type != TOKEN_TYPE_CURLY_CLOSE) {
            fprintf(stderr, "Expected '}'\n");
            exit(-1);
        }

        // Add stylesheet
        add_style_to_stylesheet(stylesheet, style);

    }

}

// Example of how to use this function in load_stylesheet
stylesheet_t *load_stylesheet(const char *path) {
    // No file provided
    if (path == NULL) {
        return load_sample_stylesheet();
    }

    // Create stylesheet
    stylesheet_t *stylesheet = create_stylesheet();

    char* content = read_file(path);

    // Tokenise content
    TokenList_t tokens = tokenise(content);

    // Free content
    free(content);

    // Parse tokens
    parse_tokens(tokens, stylesheet);

    // Free tokens
    free_tokens(&tokens);

    // Return the filled stylesheet
    return stylesheet;
}
