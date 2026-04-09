#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "da_token.h"
#include "parser.h"
#include "lexer.h"

int parse_create_table(struct DA_Token *da){
    for(size_t i = 0; i < da->count; i++){
        if(i == 0 && strcmp(da->list[0].val, "create")){
            return -1;
        }
        if(i == 1 && strcmp(da->list[1].val, "table")){
            return -1;
        }
    }

    return 1;
}

struct Command *parser(struct DA_Token *da){
    struct Command *cmd = malloc(sizeof(*cmd));

    int parsed = parse_create_table(da);

    if(parsed > -1){
        cmd->type = CREATE_TABLE;
        cmd->table_name = da->list[2].val;
        cmd->column_count = 2;
        cmd->columns = malloc(sizeof(char*)*cmd->column_count);
        cmd->columns[0] = da->list[4].val;
        cmd->columns[1] = da->list[6].val;
    }

    return cmd;
}

void parser_free(struct Command *cmd){
    free(cmd->columns);
    free(cmd);
}
