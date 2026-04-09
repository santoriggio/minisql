#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "da_token.h"
#include "lexer.h"
#include "parser.h"

FILE *create_table(char *table_name, char **columns, size_t column_count){
    size_t name_len = strlen(table_name);
    char *path = malloc(sizeof(*path) * (name_len + 4 + 1));

    path[0] = '\0';
        
    strcat(path, table_name);
    strcat(path, ".csv");

    FILE *f = fopen(path, "w");

    if(f == NULL){
        free(path);
        printf("Error while creating table '%s'\n", table_name);
        return NULL;
    }

    for(size_t i = 0; i < column_count; i++){
        fprintf(f, "%s", columns[i]);
        if(i < column_count - 1){
             fprintf(f, ",");
        }
    }

    int printed = fprintf(f, "\n");

    free(path);

    if(printed < 0){
        printf("Error while writing table '%s'\n", table_name);
        return NULL;
    }


    printf("Table '%s' created\n", table_name);
    return f;
}

int close_file(FILE *f){
    return fclose(f);
}

int sum_argv(int argc, char *argv[]){
    int sum = 0;
    for(int i = 1; i < argc; i++){
        int len = strlen(argv[i]);
        sum+=len;

        if(i < argc - 2){
            sum+=1;
        }
    }
}

char *create_str(int argc, char *argv[]){
    int sum = sum_argv(argc, argv);
    char *args = malloc(sizeof(*args)*(sum + 1));

    args[0] = '\0';
    for(int i = 1; i < argc; i++){
        strcat(args, argv[i]);

        if(i < argc - 1){
            strcat(args, " ");
        }
    }

    return args;
}


void print_welcome(){
    printf("\n");
    printf("----------------\n");
    printf("\n");
    printf("Welcome to miniSQL, a mini implementation of some basic commands of SQL written in C\n");
    printf("\n");
    printf("----------------\n");
    printf("\n");
}

int main(int argc, char *argv[]){
    print_welcome();

    char res[1024] = {};
    while(1){
        printf("\n");
        printf("> ");
        fgets(res, 1024, stdin);

        if(!strcmp(res, "q\n")){
            return 2;
        }

        FILE *f = NULL;

        struct DA_Token *da = tokenizer(res);

        struct Command *cmd = parser(da);

        if(cmd->type == CREATE_TABLE){
            f = create_table(cmd->table_name, cmd->columns, cmd->column_count);

            if(f == NULL){
                return -1;
            }

        }

        da_token_free(da);
        parser_free(cmd);
        close_file(f);
    }


    return 0;
}
