/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:08 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 19:39:28 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_minishell(t_shell *mini, char **envp)
{
	char		*line;
	char		*temp;
	//t_parser	*parser;

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
			add_history(temp);
		ft_prev_exec(mini, temp);
		// if (g_signal != S_HEREDOC_CANCEL)
		// 	ft_cmd_exec(mini);
		// ft_memfree(temp);
		// ft_memfree(line);
		//mini->parser = NULL;
	}
	ft_free_env(&mini->env);
}

void	ft_prev_exec(t_shell *mini, char *temp)
{
	mini->tokens = tokenizer(temp);
	//print_tokens(mini->tokens); // Tokenizer working correctly
	printf("Finish tokenizer\n");
	mini->arg = parse_tokens(mini->tokens);
	print_parser(mini->arg);
	printf("Working\n");
}

// cat input.txt | g e


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
