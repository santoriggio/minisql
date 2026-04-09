#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "da_token.h"

const char *keywords[] = {
    "create",
    "table",
    "into",
    "values",
    "drop"
};

int is_keyword(char buf[]){
    size_t arrlen = sizeof(keywords) / sizeof(keywords[0]);
    for(size_t i = 0; i < arrlen; i++){
        if(!strcmp(keywords[i], buf)){
            return i;
        }
    }

    return -1;
}

void bufcmp(struct DA_Token *da, char buf[], size_t buflen){

    if(buflen == 0) return;

    int keyword = is_keyword(buf);

    if(keyword > -1){
        da_token_push(da, KEYWORD, buf);
        return;
    }

    da_token_push(da, IDENTIFIER, buf);
    return;
}

struct DA_Token *tokenizer(char *str) {
    struct DA_Token *da = create_da_token();

    size_t len = strlen(str);

    char buf[len + 1];
    size_t j = 0;
    for(size_t i = 0; i < len; i++){
        char curr = str[i];

        switch (curr){
            case '(':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                da_token_push(da, LPAREN, NULL);
                j = 0;
                break;
            case ')':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                da_token_push(da, RPAREN, NULL);
                j = 0;
                break;
            case ',':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                da_token_push(da, COMMA, NULL);
                j = 0;
                break;
            case '=':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                da_token_push(da, EQUAL, NULL);
                j = 0;
                break;
            case ';':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                da_token_push(da, EOF_TOKEN, NULL);
                j = 0;
                break;
            case ' ':
                buf[j] = '\0';
                bufcmp(da, buf, j);
                j = 0;
                break;
             default:
                buf[j] = curr;
                j++;
                break;
        };
    }

    return da;
}
