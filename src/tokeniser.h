#ifndef TOKENISER_H
#define TOKENISER_H

#include <stddef.h>

typedef enum{
    TOKEN_TYPE_TEXT,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_BALISE_OPEN,
    TOKEN_TYPE_BALISE_CLOSE,
    TOKEN_TYPE_SLASH,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_CSS_VALUE, // ": 10%" because it's more simple
    TOKEN_TYPE_CURLY_OPEN,
    TOKEN_TYPE_CURLY_CLOSE
} TokenType_t;

typedef struct {
    TokenType_t type;
    char* value;
} Token_t;

typedef struct {
    Token_t** tokens;
    size_t count;
} TokenList_t;


TokenList_t tokenise(const char* content);
void free_tokens(TokenList_t* token_list);
Token_t get_token(TokenList_t* token_list, size_t index);

#endif // TOKENISER_H
