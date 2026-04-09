#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "da_token.h"
#include "lexer.h"
#include "parser.h"

FILE *create_table(char *path, char **columns, size_t column_count){
    FILE *f = fopen(path, "w");

    for(size_t i = 0; i < column_count; i++){
        fprintf(f, "%s", columns[i]);
        if(i < column_count - 1){
             fprintf(f, ",");
        }
    }

    fprintf(f, "\n");

    return f;
}

int close_file(FILE *f){
    return fclose(f);
}

int main(int argc, char *argv[]){
    FILE *f = NULL;

    int sum = 0;
    for(int i = 1; i < argc; i++){
        int len = strlen(argv[i]);
        sum+=len;

        if(i < argc - 2){
            sum+=1;
        }
    }

    // sum + null \0
    char *args = malloc(sizeof(*args)*(sum + 1));

    args[0] = '\0';
    for(int i = 1; i < argc; i++){
        strcat(args, argv[i]);

        if(i < argc - 1){
            strcat(args, " ");
        }
    }

    struct DA_Token *da = tokenizer(args);

    da_token_print(da);

    struct Command *cmd = parser(da);

    if(cmd->type == CREATE_TABLE){
        f = create_table("users.csv", cmd->columns, cmd->column_count);
    }

    da_token_free(da);
    free(args);
    parser_free(cmd);
    close_file(f);

    return 0;
}
