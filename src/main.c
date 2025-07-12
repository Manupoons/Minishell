/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:08 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 15:40:50 by jdorazio         ###   ########.fr       */
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
	mini->arg = parse_tokens(mini->tokens, mini->env, &mini->status);
}

static void	free_minishell(t_shell *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->arg)
		free_args(mini->arg);
	ft_free_env(&mini->env);
}

static int	ft_read_and_trim(char **line, char **temp)
{
	*line = readline(get_prompt());
	if (!*line)
		return (0);
	*temp = ft_strtrim(*line, " \t\n\v\f\r");
	if (*temp && **temp)
		add_history(*temp);
	return (1);
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
		if (!ft_read_and_trim(&line, &temp))
		{
			printf("exit\n");
			break ;
		}
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
	print_header();
	init_signal();
	ft_minishell(&mini, envp);
	return (EXIT_SUCCESS);
}
