#include "./minishell.h"

int word_counter(t_token *tokens)
{
    int count;

    count = 0;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        count++;
        tokens = tokens->next;
    }

    return (count);
}

t_arg   *init_arg(int count)
{
    t_arg   *arg_list;

    arg_list = malloc(sizeof(t_arg));
    if (!arg_list)
        error_message("failed to alloc mem");
    arg_list->args_count = count;
    arg_list->argv =  malloc(sizeof(char *) * (arg_list->args_count + 1));
    if (!arg_list->argv)
        error_message("failed to alloc mem");
    arg_list->argv[count] = NULL;
    arg_list->next = NULL;
    return (arg_list);    
}

t_arg   *parse_tokens(t_token *tokens)
{
    t_arg   *head_arg;
    t_arg   *curr_arg;
    t_token *curr_token;
    int     index;

    printf("Starting parsing\n");
    head_arg = NULL;
    curr_arg = NULL;
    curr_token = tokens;
    index = 0;
    printf("Looping\n");
    while (curr_token)
    {
        if (!curr_arg && !(curr_token->type == TOKEN_PIPE))
        {
            printf("enters here once\n");
            curr_arg = init_arg(word_counter(curr_token));
            printf("Token amount %d\n", curr_arg->args_count);
            head_arg = curr_arg;
        }
        if (curr_token->type == TOKEN_WORD)
        {
printf("Word123 %s \n", curr_token->token);
            index += handle_word_token(curr_arg, curr_token->token, index);
        }
        else if (curr_token->type == TOKEN_PIPE)
            curr_arg = handle_pipe_token(curr_arg, curr_token->next, &index);
        else
            handle_redir_token(curr_arg, curr_token);
        printf("Restarting loop\n");
        curr_token = curr_token->next;
    }
    printf("finish creating parsing\n");
    return (head_arg);
}

int  handle_word_token(t_arg *curr_arg, char *token, int index)
{
    curr_arg->argv[index] = strdup(token);
    return (1);
}

t_arg   *handle_pipe_token(t_arg *curr_arg, t_token *next_tokens, int *index)
{
    t_arg   *new;

    if (!curr_arg)
        error_message("pipe without command before it.\n");
    if (!next_tokens)
        error_message("pipe without command after it.\n");
    new = init_arg(word_counter(next_tokens));
    curr_arg->next = new;
    *index = 0;
    return (new);
}


void    handle_redir_token(t_arg *curr_arg, t_token *token)
{
    t_token *file_token;
    t_parser *redir;

    printf("starting handle redir\n");
    file_token = token->next;
    if (!file_token || file_token->type != TOKEN_WORD)
        error_message("Syntax error_ redirection without filename.");
    redir = malloc(sizeof(t_parser));
    if (!redir)
        error_message("failed to alloc.");
    printf("Starting to fill t_parse\n");
    redir->type = token->type;
    printf("redir->type\n");
    redir->cmd = ft_strdup(file_token->token);
        printf("redir->cmd\n");
    redir->fd_in = 0;
    redir->fd_out = 1;
    if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
    {
        redir->fd_in = 1;
    printf("redir->in or heredoc\n");

    }
    else if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
    {
            printf("redir->TOKEN_APPEND or TOKEN_REDIR_OUT\n");

            redir->fd_out = 1;
    }
    printf("Exit if\n");
    redir->next = NULL;
    append_to_parser(&(curr_arg->parser), redir);
}


void    append_to_parser(t_parser **head, t_parser *redir)
{
    t_parser    *tmp;

    printf("starting to append\n");
    if (!*head)
        *head = redir;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next =  redir; 
    }
    printf("Appended to parser\n");
}
