/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:08 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/31 12:08:59 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_minishell(t_shell *mini, char **envp)
{
	char		*line;
	char		*temp;
	t_parser	*parser;

	mini->env = NULL;
	mini->parser = NULL;
	ft_lst_env_init(&mini->env, envp);
	while (1)
	{
		if (g_signal == S_SIGINT)
			mini->status = 1;
		line = readline(READLINE_MSG);
		if (!line)
			break ;
		temp = ft_strtrim(line, " \t\n\v\f\r");
		if (temp[0] != '\0')
		{
			add_history(temp);
			parser = malloc(sizeof(t_parser));
			if (!parser)
				break ;
			parser->cmd = ft_strdup(temp);
			parser->fd_in = 0;
			parser->fd_out = 1;
			parser->next = NULL;
			mini->parser = parser;
			mini->arg = malloc(sizeof(t_cmd));
			if (!mini->arg)
				break ;
			mini->arg->argv = NULL;
			mini->arg->args_count = 0;
			mini->arg->parser = NULL;
			mini->arg->next = NULL;
		}
		if (g_signal != S_HEREDOC_CANCEL)
			ft_cmd_exec(mini);
		ft_memfree(temp);
		ft_memfree(line);
		mini->parser = NULL;
	}
	ft_free_env(&mini->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mini;

	if (argc != 1 || argv[1])
		return (EXIT_FAILURE);
	printf("%s", HEADER);
	init_signal();
	ft_minishell(&mini, envp);
	return (EXIT_SUCCESS);
}
