#include "./minishell.h"

// static void	ft_minishell(t_shell *msh, char **envp)
// {
// 	char	*line;
// 	char	*tmp;

// 	ft_lst_env_init(&msh->env, envp);
// 	while (1)
// 	{
// 		line = readline(READLINE_MSG);
// 		if (!line)
// 			break ;
// 		tmp = ft_strtrim(line, " \t\n\v\f\r");
// 		if (tmp[0] != 0)
// 			add_history(tmp);
// 		ft_prev_exec(tmp, msh);
// 		ft_cmd_exec(msh);
// 		ft_clean_shell(tmp, line, msh);
// 	}
// 	t_free_list(&msh->env);
// }

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
		line = readline(READLINE_MSG);
		if (!line)
			break ;
		temp = ft_strtrim(line, " \t\n\v\f\r");
		if (temp[0] != '\0')
			add_history(temp);
		if (temp[0] != '\0')
		{
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
			ft_cmd_exec(mini);
		}
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
	ft_minishell(&mini, envp);
	return (EXIT_SUCCESS);
}
