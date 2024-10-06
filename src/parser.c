#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "tokeniser.h"
#include "reader.h"
#include <string.h>

// Parse a list of token into a list of attributes and add them to a balise
void parse_attributes(TokenList_t* tokens, size_t* index, balise_t* balise){

    // Loop through tokens
    while (*index < tokens->count){

        // Get token
        Token_t token = get_token(tokens, *index);

        // Check if token is a closing balise
        if (token.type == TOKEN_TYPE_BALISE_CLOSE){
            return;
        }

        // Check if token is not a text
        if (token.type != TOKEN_TYPE_TEXT){
            fprintf(stderr, "Expected attribute name or closing balise\n");
            exit(-1);
        }

        // Get attribute name
        char* attribute_name = strdup(token.value);
        (*index)++;

        // Get equal sign
        if (get_token(tokens, *index).type != TOKEN_TYPE_EQUAL){
            free(attribute_name);
            fprintf(stderr, "Expected equal sign\n");
            exit(-1);
        }
        (*index)++;

        // Get attribute value
        if (get_token(tokens, *index).type != TOKEN_TYPE_STRING){
            free(attribute_name);
            fprintf(stderr, "Expected attribute value\n");
            exit(-1);
        }
        char* attribute_value = strdup(get_token(tokens, *index).value);
        (*index)++;

        // Add attribute to balise
        add_attribute(balise, attribute_name, attribute_value);

    }

}

// Parse a list of token into a balise
balise_t* parse_token(TokenList_t* tokens, size_t* index){

    // Get opening token
    if (get_token(tokens, *index).type != TOKEN_TYPE_BALISE_OPEN){
        fprintf(stderr, "Expected opening balise\n");
        exit(-1);
    }
    (*index)++;

    // Get balise name
    if (get_token(tokens, *index).type != TOKEN_TYPE_TEXT){
        fprintf(stderr, "Expected balise name\n");
        exit(-1);
    }

    // Create balise
    balise_t* balise = create_balise(strdup(get_token(tokens, *index).value));
    (*index)++;

    // Get attributes
    parse_attributes(tokens, index, balise);

    // Check end balise
    if (get_token(tokens, *index).type != TOKEN_TYPE_BALISE_CLOSE){
        free_balise(balise);
        fprintf(stderr, "Expected closing balise\n");
        exit(-1);
    }
    (*index)++;

    // If balise is a container, get children
    if (IS_CONTAINER(balise)){
    
        // Get children
        while (*index < tokens->count){
            
            Token_t token = get_token(tokens, *index);

            if (token.type != TOKEN_TYPE_BALISE_OPEN){
                fprintf(stderr, "Expected opening balise\n");
                exit(-1);
            }
            
            if (*index + 1 < tokens->count && get_token(tokens, *index + 1).type == TOKEN_TYPE_SLASH){
                (*index) += 2;
                if (get_token(tokens, *index).type != TOKEN_TYPE_TEXT){
                    fprintf(stderr, "Expected the balise name\n");
                    exit(-1);
                }
                if (strcmp(get_token(tokens, *index).value,  balise->tag_name) != 0){
                    fprintf(stderr, "Expected the closing balise name to be the same as the opening balise name\n");
                    exit(-1);
                }
                (*index)++; 
                if (get_token(tokens, *index).type != TOKEN_TYPE_BALISE_CLOSE){
                    fprintf(stderr, "Expected closing balise\n");
                    exit(-1);
                }
                (*index)++;
                break;
            }

            balise_t* child = parse_token(tokens, index);
            if (child != NULL){
                add_child(balise, child);
            }
        
        }

    } else if (IS_WINDOW(balise)){

        // Get the unique children
        Token_t token = get_token(tokens, *index);
        
        if (token.type != TOKEN_TYPE_BALISE_OPEN){
            fprintf(stderr, "A balise was expected\n");
            exit(-1);
        }

        balise_t* child = parse_token(tokens, index);
        if (child != NULL){
            add_child(balise, child);
        }

        if (*index + 1 < tokens->count && get_token(tokens, *index + 1).type == TOKEN_TYPE_SLASH){
            (*index) += 2;
            if (get_token(tokens, *index).type != TOKEN_TYPE_TEXT){
                fprintf(stderr, "Expected the balise name\n");
                exit(-1);
            }
            if (strcmp(get_token(tokens, *index).value,  balise->tag_name) != 0){
                fprintf(stderr, "Expected the closing balise name to be the same as the opening balise name\n");
                exit(-1);
            }
            (*index)++; 
            if (get_token(tokens, *index).type != TOKEN_TYPE_BALISE_CLOSE){
                fprintf(stderr, "Expected closing balise\n");
                exit(-1);
            }
            (*index)++;
        }

    }


    // Return balise
    return balise;

}

// Parse a .mct file and return the root balise
balise_t* parse_mct_string(const char* content){
    TokenList_t tokens = tokenise(content);
    size_t index = 0;
    balise_t* root = parse_token(&tokens, &index);
    free_tokens(&tokens);
    return root;
}

// Parses a .mct file and returns the root balise (usually a container balise)
balise_t* parse_mct_file(const char* file_path){
   
    // Read file
    char* content = read_file(file_path);

    // Parse content
    balise_t* root = parse_mct_string(content);

    // Free content
    free(content);

    return root;
}