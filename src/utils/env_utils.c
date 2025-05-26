/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/26 19:19:27 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

char    *get_env_name(char  *name)
{
    int i;
    
    i = 0;
    while (name[i] && name[i] != '=' && name[i] != ' ')
        i++;
    return(ft_substr(name, 0, i));
}

char    *get_env_value(char *value)
{
    int i;

    i = 0;
    while (value[i] && value[i] != '=' && value[i] != ' ')
        i++;
    if (value[i + 1] == '\"')
        return (ft_substr(value, i + 2, ft_strlen(value) - i));
    else
        return (ft_substr(value, i + 1, ft_strlen(value) - i));
}

void    ft_add_back_env(t_env **lst, t_env *new)
{
    t_env   *tmp;

    if (!lst || !(*lst))
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

t_env   *ft_lst_new_env(char *name, char *value, int alloc)
{
    t_env   *new_node;
    
    new_node = ft_calloc(1, sizeof(t_env));
    new_node->env_name = name;
    new_node->env_value = value;
    if (alloc)
    {
        new_node->env_name = ft_strdup(name);
        new_node->env_value = ft_strdup(value);
        if (!new_node->env_name || !new_node->env_value)
        {
            return (NULL);
        }
    }
    new_node->next = NULL;
    return (new_node);
}

void    ft_lst_env_init(t_env **env, char **envp)
{
    t_env   *new;
    int     i;
    char    *name;
    char    *value;
    
    new = NULL;
    i = -1;
    while (++i < ft_arraylen(envp))
    {
        name = get_env_name(envp[i]);
        value = get_env_value(envp[i]);
        new = ft_lst_new_env(name, value, 1);
        ft_add_back_env(env, envp);
    }
}