/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:08 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/09 15:41:01 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_prev_exec(t_shell *mini, char *temp)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->arg)
		free_args(mini->arg);
	mini->tokens = NULL;
	mini->arg = NULL;
	mini->tokens = tokenizer(temp, &mini->status);
	// print_tokens(mini->tokens);
	mini->arg = parse_tokens(mini->tokens, mini->env, &mini->status);
	// print_parser(mini->arg);
}	

static void	free_minishell(t_shell *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->arg)
		free_args(mini->arg);
	ft_free_env(&mini->env);
}

static void	ft_minishell(t_shell *mini, char **envp)
{
	char	*line;
	char	*temp;

	mini->tokens = NULL;
	mini->env = NULL;
	mini->arg = NULL;
	ft_lst_env_init(mini, envp);
	while (1)
	{
		line = readline(READLINE_MSG);
		if (!line)
			break ;
		temp = ft_strtrim(line, " \t\n\v\f\r");
		if (temp && *temp)
			add_history(temp);
		ft_prev_exec(mini, temp);
		if (g_signal != S_HEREDOC_CANCEL)
			ft_cmd_exec(mini);
		ft_memfree(temp);
		ft_memfree(line);
		g_signal = S_BASE;
	}
	free_minishell(mini);
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
