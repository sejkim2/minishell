#include <stdio.h>
#include <stdlib.h>

typedef enum s_symbol
{
    HI = 0,
    BYE,
    GOOD
}   t_symbol;

typedef struct s_token
{
    t_symbol symbol;
    char *value;
}   t_token;

typedef struct s_token_node
{
    t_token token;
    struct s_token_node *next;
}   t_token_node;

void init_token_1(t_token *token, t_symbol symbol, char *value)
{
    token->symbol = symbol;
    token->value = value;
}

void init_token(t_token_node *node)
{
    char *value;
    value = malloc(sizeof(char) * 2);
    value[0] = 'c';
    value[1] = '\0';
    init_token_1(&node->token, GOOD, value);
    node->next = 0;
}

int main(void)
{
    t_token_node node;
    init_token(&node);
    printf("[%d %s]", node.token.symbol, node.token.value);
}