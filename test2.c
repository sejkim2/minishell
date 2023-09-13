#include <stdio.h>

typedef enum e_symbol
{
	WORD = 0,
	ASSIGNMENT_WORD,
	REDIRECTION,
	PIPE,
    AND_IF,
    OR_IF,
    EQUAL,
    L_BRA,
    R_BRA,
    SIMPLE_COMMAND_ELEMENT,
    SIMPLE_COMMAND,
    COMMAND,
    PIPELINE,
    SUBSHELL,
    LIST,
    ROOT
}   t_symbol;

int main(void)
{
    t_symbol symbol;
    symbol = OR_IF;

    switch (symbol)
    {
    case WORD:
        printf("WORD\n");
        break;
    case ASSIGNMENT_WORD:
        printf("ASSIGNMENT_WORD\n");
        break;
    case REDIRECTION:
        printf("REDIRECTION\n");
        break;
    case PIPE:
        printf("PIPE\n");
        break;
    case AND_IF:
        printf("AND_IF\n");
        break;
    case OR_IF:
        printf("OR_IF\n");
        break;
    case EQUAL:
        printf("EQUAL\n");
        break;
    case L_BRA:
        printf("L_BRA\n");
        break;
    case R_BRA:
        printf("R_BRA\n");
        break;
    case SIMPLE_COMMAND:
        printf("SIMPLE_COMMAND\n");
        break;
    case SIMPLE_COMMAND_ELEMENT:
        printf("SIMPLE_COMMAND_ELEMENT\n");
        break;
    case COMMAND:
        printf("COMMAND\n");
        break;
    case PIPELINE:
        printf("PIPELINE\n");
        break;
    case SUBSHELL:
        printf("SUBSHELL\n");
        break;
    case LIST:
        printf("LIST\n");
        break;
    case ROOT:
        printf("ROOT\n");
        break;
    default:
        break;
    }

}