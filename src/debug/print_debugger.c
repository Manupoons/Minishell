# include "../../inc/minishell.h"

void print_tokens(t_token *tokens)
{
    int i = 0;
    while (tokens)
    {
        printf("Token %d: [%s] (Type: %d)\n", i++, tokens->token, tokens->type);
        tokens = tokens->next;
    }
}
void print_parser(t_arg *head)
{
    int i, cmd_num = 0;

    while (head)
    {
        printf("\n=== Command %d ===\n", cmd_num++);
        printf("Arguments count: %d\n", head->args_count);

        for (i = 0; i < head->args_count; i++)
        {
            printf("argv[%d]: %s\n", i, head->argv[i]);
        }

        // Redirections
        t_redir *redir = head->redirs;
        if (redir)
            printf("Redirections:\n");
        while (redir)
        {
            printf("  → File: %s | fd_in: %d | fd_out: %d | type: %d\n",
                   redir->cmd, redir->fd_in, redir->fd_out, redir->type);
            redir = redir->next;
        }

        head = head->next;
    }
}
