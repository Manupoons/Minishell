/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debugger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:14:22 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/07 10:20:49 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token %d: [%s] (Type: %d)\n", i++, tokens->token,
			tokens->type);
		tokens = tokens->next;
	}
}

// void	print_parser(t_arg *head)
// {
// 	int		i;
// 	int		cmd_num;
// 	t_redir	*redir;

// 	i = 0;
// 	cmd_num = 0;
// 	while (head)
// 	{
// 		printf("\n=== Command %d ===\n", cmd_num++);
// 		printf("Arguments count: %d\n", head->args_count);
// 		while (i++ < head->args_count)
// 			printf("argv[%d]: %s\n", i, head->argv[i]);
// 		redir = head->redirs;
// 		if (redir)
// 			printf("Redirections:\n");
// 		while (redir)
// 		{
// 			printf("  → File: %s | fd_in: %d | fd_out: %d | type: %d\n",
// 				redir->cmd, redir->fd_in, redir->fd_out, redir->type);
// 			redir = redir->next;
// 		}
// 		head = head->next;
// 	}
// }
