#include "./minishell.h"

void print_banner(void) {
    printf("\033[1;36m");  // Bright cyan
    printf("  __  __ _       _     _          _ _ \n");
    printf(" |  \\/  (_)     (_)   | |        | | |\n");
    printf(" | \\  / |_ _ __  _  __| | ___  __| | |\n");
    printf(" | |\\/| | | '_ \\| |/ _` |/ _ \\/ _` | |\n");
    printf(" | |  | | | | | | | (_| |  __/ (_| |_|\n");
    printf(" |_|  |_|_|_| |_|_|\\__,_|\\___|\\__,_(_)\n");
    printf("\033[0m\n");  // Reset color
}

char **split_line(char *line)
{
    char **args;
    char *token;
    int i = 0;

    args = malloc(sizeof(char *) * 100);
    if (!args)
        return NULL;

    token = strtok(line, " ");
    while (token)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}

int main(void)
{
    print_banner();
    char    *line;
    char    **argv;

    while ((line = readline("minishell$ ")) != NULL)
    {

        if (!line)
        {
            printf("exit\n");
            break;
        }

        if (*line)
        {
            add_history(line);
            argv = split_line(line);
            exec_comms(argv);
            free(argv);
        }
        free(line);
    }
    rl_clear_history();
    return 0;
}