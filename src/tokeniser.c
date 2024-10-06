#include "tokeniser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static Token_t* create_token(TokenType_t type, const char* value) {
    Token_t* token = (Token_t*)malloc(sizeof(Token_t));
    token->type = type;
    token->value = strdup(value);
    return token;
}

static void add_token(TokenList_t* token_list, Token_t* token) {
    token_list->tokens = (Token_t**)realloc(token_list->tokens, sizeof(Token_t*) * (token_list->count + 1));
    token_list->tokens[token_list->count++] = token;
}

TokenList_t tokenise(const char* content) {
    TokenList_t token_list;
    token_list.tokens = NULL;
    token_list.count = 0;
    const char* ptr = content;
    char buffer[256];
    size_t buffer_index = 0;

    while (*ptr != '\0') {

        // Skip whitespace characters
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }

        // Handle different token types
        switch (*ptr)
        {
            case '<':
                add_token(&token_list, create_token(TOKEN_TYPE_BALISE_OPEN, NULL));
                ptr++;
                continue;
            
            case '>':
                add_token(&token_list, create_token(TOKEN_TYPE_BALISE_CLOSE, NULL));
                ptr++;
                continue;

            case '/':
                add_token(&token_list, create_token(TOKEN_TYPE_SLASH, NULL));
                ptr++;
                continue;

            case '=':
                add_token(&token_list, create_token(TOKEN_TYPE_EQUAL, NULL));
                ptr++;
                continue;
            
            case '{':
                add_token(&token_list, create_token(TOKEN_TYPE_CURLY_OPEN, NULL));
                ptr++;
                continue;

            case '}':
                add_token(&token_list, create_token(TOKEN_TYPE_CURLY_CLOSE, NULL));
                ptr++;
                continue;
        
            default:
                break;
        }

        // Handle string literals enclosed in double quotes
        if (*ptr == '"') {
            ptr++;
            while (*ptr != '"' && *ptr != '\0') {
                buffer[buffer_index++] = *ptr++;
            }
            buffer[buffer_index] = '\0';
            add_token(&token_list, create_token(TOKEN_TYPE_STRING, buffer));
            buffer_index = 0;
            if (*ptr == '"') {
                ptr++;
            }
        } 

        // Handle css value
        else if (*ptr == ':') {
            ptr++;
            while (*ptr != '\0' && isspace(*ptr)) {
                ptr++;
            }
            while (*ptr != ';' && *ptr != '\0') {
                buffer[buffer_index++] = *ptr++;
            }
            buffer[buffer_index] = '\0';
            add_token(&token_list, create_token(TOKEN_TYPE_CSS_VALUE, buffer));
            buffer_index = 0;
            if (*ptr == ';') {
                ptr++;
            }
        }

        // Handle alphanumeric characters (words)
        else if (isalpha(*ptr)) {
            while (*ptr != '\0' && isalnum(*ptr)) {
                buffer[buffer_index++] = *ptr++;
            }
            buffer[buffer_index] = '\0';
            add_token(&token_list, create_token(TOKEN_TYPE_TEXT, buffer));
            buffer_index = 0;
        } 

        // Handle any other characters
        else {
            fprintf(stderr, "Unexpected character: '%c'\n", *ptr);
            exit(-1);
        }

    }

    return token_list;
}

void free_token(Token_t* token){
    free(token->value);
    free(token);
}

void free_tokens(TokenList_t* token_list){
    for (size_t i = 0; i < token_list->count; i++) {
        free_token(token_list->tokens[i]);
    }
    free(token_list->tokens);
}

Token_t get_token(TokenList_t* token_list, size_t index){
    if (index < token_list->count) {
        return *token_list->tokens[index];
    }
    Token_t empty_token = {0};
    return empty_token;
}