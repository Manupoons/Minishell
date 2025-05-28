#include "./minishell.h"

int count_word_tokens(t_token *tokens)
{
    int count;

    count = 0;
    while (tokens)
    {
        if (tokens->type = TOKEN_WORD)
            count++;
        tokens = tokens->next;
    }
    return (count);
}



t_cmd   *parse_tokens(t_token *tokens)
{
    t_cmd           *cmd_list;
    t_token_type    type;
    int             count;

    cmd_list = NULL;
    count = 0;
    cmd_list->args_count = count_word_tokens(tokens);
    while (tokens)
    {
        type = tokens->type;
        if (type == TOKEN_WORD)
            count += add_token_to_cmds(cmd_list, tokens->token);
        // else if (type == TOKEN_REDIR_IN)

        // else if (type == TOKEN_PIPE)
        tokens = tokens->next;
    }
    return (cmd_list);
}

t_cmd   *init_cmd(int count)
{
    t_cmd   *cmd_list;

    cmd_list = malloc(sizeof(t_cmd));
    if (!cmd_list)
        error_message("failed to alloc mem");
    cmd_list->args_count = count;
    cmd_list->argv =  malloc(sizeof(char *) * (cmd_list->args_count + 1));
    if (!cmd_list->argv)
        error_message("failed to alloc mem");
    cmd->
}



int add_token_to_cmds(t_cmd *cmd_list, char *tokens)
{
    cmd_list->argv = malloc(sizeof(char *) * cmd_list->args_count);
    
}


crear comando raíz current_cmd
args_count = 0

for each token in token_list:
    if token es palabra:
        agregar token a current_cmd.argv
        args_count++
    else if token es redirección:
        crear nodo parser con tipo y archivo
        agregar a current_cmd.parser
    else if token es PIPE:
        finalizar argv con NULL y guardar args_count en current_cmd
        crear nuevo t_cmd y enlazar con current_cmd->next
        current_cmd = current_cmd->next
        args_count = 0

finalizar último argv con NULL y guardar args_count
retornar comando raíz
