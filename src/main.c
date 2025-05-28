#include "./minishell.h"

static void	ft_minishell(t_shell *msh, char **envp)
{
	char	*input;
	char	*tmp;

	ft_lst_env_init(&msh->env, envp);
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (tmp[0] != 0)
			add_history(tmp);
		//ft_prev_exec(tmp, msh);
		ft_cmd_exec(msh);
		//ft_clean_shell(tmp, input, msh);
	}
	//t_free_list(&msh->env);
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
