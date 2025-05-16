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

int main(void)
{
    print_banner();
    char    *line;

    while (1) {
        line = readline("minishell$ ");

        if (!line) {
            printf("exit\n");
            break;
        }

        if (*line) {
            add_history(line);
            printf("You typed: %s\n", line);
        }

        free(line);
    }

    return 0;
}