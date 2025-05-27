# include "./minishell.h"

void	ft_comms(char **argv)
{
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	// else if (ft_strncmp(argv[0], "cd", 2) == 0)
	// 	ft_cd(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
	// else if (ft_strncmp(argv[0], "export", 6) == 0)
	// 	ft_export(argv);
	// else if (ft_strncmp(argv[0], "unset", 5) == 0)
	// 	ft_unset(argv);
	// else if (ft_strncmp(argv[0], "env", 3) == 0)
	// 	ft_env(argv);
	else if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(argv);
}