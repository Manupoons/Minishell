#include "./minishell.h"

int word_counter(t_token *tokens)
{
    int count;

    count = 0;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
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

    head_arg = NULL;
    curr_arg = NULL;
    curr_token = tokens;
    index = 0;
    while (curr_token)
    {
        if (!curr_arg)
        {
            curr_arg = init_arg(word_counter(curr_token));
            head_arg = curr_arg;
        }
        if (curr_token->type == TOKEN_WORD)
            index += handle_word_token(curr_arg, curr_token->token, index);
        else if (curr_token->type == TOKEN_PIPE)
            curr_arg = handle_pipe_token(curr_arg, curr_token->next);
        else
            handle_redir_token(curr_arg, curr_token); 
        curr_token = curr_token->next;
    }
    return (head_arg);
}

int  handle_word_token(t_arg *curr_arg, char *token, int index)
{
    curr_arg->argv[index] = strdup(token);
    return (1)
}

t_arg   *handle_pipe_token(t_arg *curr_arg, t_token *next_tokens)
{
    t_arg   *new;

    new = init_arg(word_counter(next_tokens));
    curr_arg->next = new;
    return (new)
}


void    handle_redir_token(t_arg *curr_arg, t_token *redir_token)
{
    t_token *file_token;
    t_parser *redir;

    file_token = redir_token->next;
    if (!file_token || file_token->type != TOKEN_WORD)
        error_message("Syntax error. Change this output later");
    redir = malloc(sizeof(t_parser));
    if (!redir)
        error_message("failed to alloc.");
    if (redir_token->type == TOKEN_REDIR_IN)
        redir->fd_in = redir_token->type
    else if (redir_token->type == TOKEN_REDIR_OUT)
        redir->fd_out = redir_token->type
    redir->cmd = ft_strdup(file_token->token);
    redir->next = NULL;
    append_to_parser(&(curr(curr_arg->)))
}


void    append_to_parser(t_parser *head, t_arg *redir)
{
    t_parser    *tmp;

    if (!head)
        head = redir;
    else
    {
        tmp = head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next =  redir; 
    }
}