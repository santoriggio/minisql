#ifndef DA_TOKEN_H
#define DA_TOKEN_H

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    EOF_TOKEN,
    UNKNOWN,
    LPAREN,
    RPAREN,
    EQUAL,
    COMMA
};

struct Token {
    enum TokenType type;
    char *val;
};

struct DA_Token {
    size_t capacity;
    size_t count;
    struct Token *list;
};

struct DA_Token *create_da_token();

int da_token_push(struct DA_Token *da, enum TokenType type, char *val);

void da_token_print(struct DA_Token *da);

void da_token_free(struct DA_Token *da);

#endif
