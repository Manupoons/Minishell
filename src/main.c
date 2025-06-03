/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:08 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/03 22:18:39 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_minishell(t_shell *mini, char **envp)
{
	char		*line;
	char		*temp;

	mini->tokens = NULL;
	mini->env = NULL;
	mini->arg = NULL;
	ft_lst_env_init(&mini->env, envp);
	while (1)
	{
		if (g_signal == S_SIGINT)
			mini->status = 1;
		line = readline(READLINE_MSG);
		if (!line)
			break ;
		temp = ft_strtrim(line, " \t\n\v\f\r");  
		if (temp && *temp)
			add_history(temp);
		if (ft_prev_exec(mini, temp))
			continue;
		if (g_signal != S_HEREDOC_CANCEL)
			ft_cmd_exec(mini);
		ft_memfree(temp);
		ft_memfree(line);
		g_signal = S_BASE;
	}
	ft_free_env(&mini->env);
}


int	ft_prev_exec(t_shell *mini, char *temp)
{
	mini->tokens = tokenizer(temp);
	if (!mini->tokens)
		return (1);
	//print_tokens(mini->tokens); // Tokenizer working correctly
	mini->arg = parse_tokens(mini->tokens);
	//print_parser(mini->arg);
	//printf("ARG PREV %s \n", mini->arg->prev->argv[0]);
	//printf("exit prev_exec\n");
	return (0);
}


//cat input.txt | grep error > output.log >> full.log | wc -l

// For extra: cat input.txt | grep "error" > output.log >> full.log && echo Done


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
