# include "./minishell.h"

int	is_comms(t_shell *mini)
{
	if (!ft_strncmp(mini->arg->argv[0], "echo", 4))
		return (1);
	// else if (!ft_strncmp(mini->arg->argv[0], "cd", 2))
	// 	return (1);
	else if (!ft_strncmp(mini->arg->argv[0], "pwd", 3))
		return (1);
	// else if (!ft_strncmp(mini->arg->argv[0], "export", 6))
	// 	return (1);
	// else if (!ft_strncmp(mini->arg->argv[0], "unset", 5))
	// 	return (1);
	// else if (!ft_strncmp(mini->arg->argv[0], "env", 3))
	// 	return (1);
	else if (!ft_strncmp(mini->arg->argv[0], "exit", 4))
		return (1);
	else
		return (0);
}

void	ft_comms(t_shell *mini)
{
	if (ft_strncmp(mini->arg->argv[0], "echo", 4) == 0)
		ft_echo(mini);
	// else if (ft_strncmp(mini->arg->argv[0], "cd", 2) == 0)
	// 	ft_cd(argv);
	else if (ft_strncmp(mini->arg->argv[0], "pwd", 3) == 0)
		ft_pwd(mini);
	// else if (ft_strncmp(mini->arg->argv[0], "export", 6) == 0)
	// 	ft_export(argv);
	// else if (ft_strncmp(mini->arg->argv[0], "unset", 5) == 0)
	// 	ft_unset(argv);
	// else if (ft_strncmp(mini->arg->argv[0], "env", 3) == 0)
	// 	ft_env(argv);
	else if (ft_strncmp(mini->arg->argv[0], "exit", 4) == 0)
		ft_exit(mini);
}