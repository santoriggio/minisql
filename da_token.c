#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "da_token.h"

struct DA_Token *create_da_token(){
    struct DA_Token *da = malloc(sizeof(*da));
    da->count = 0;
    da->capacity = 32;
    da->list = malloc(sizeof(struct Token) * da->capacity);
    return da;
}


int da_token_push(struct DA_Token *da, enum TokenType type, char *val){
    if(da->count == da->capacity){
        da->capacity *= 2;
        da->list = realloc(da->list, sizeof(struct Token) * da->capacity);
    }


    da->list[da->count].type = type;

    if(val == NULL){
        da->list[da->count].val = NULL;
    }else{
        da->list[da->count].val = strdup(val);
    }


    da->count++;

    return da->count;
}

void da_token_print(struct DA_Token *da){
    for(size_t i = 0; i < da->count; i++){
        struct Token *tk = &da->list[i];
        printf("TokenType: %d of val: %s\n", tk->type, tk->val);
    }
}

void da_token_free(struct DA_Token *da){
   for(size_t i = 0; i < da->count; i++){
      free(da->list[i].val);
   } 
   free(da->list);
   free(da);
}
