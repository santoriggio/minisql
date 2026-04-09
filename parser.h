#ifndef PARSER_H
#define PARSER_H

#include "da_token.h"
#include "parser.h"

enum CommandType {
    CREATE_TABLE,
    INSERT,
    SELECT,
    DROP
};

struct Command {
    enum CommandType type;
    char *table_name;
    char **columns;
    size_t column_count;
};

struct Command *parser(struct DA_Token *da);

void parser_free(struct Command *cmd);

#endif
