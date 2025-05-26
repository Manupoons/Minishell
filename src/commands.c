# include "./minishell.h"

extern char	**environ;

void	exec_ls(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve("/bin/ls", argv, NULL);
		perror("ls fail");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	exec_cd(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve("/bin/cd", argv, NULL);
		perror("cd fail");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

int	exec_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

void	exec_echo(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve("/bin/echo", argv, NULL);
		perror("echo fail");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

static int is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit(char **args)
{
	int	code;

	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		return ;
	}
	code = atoi(args[1]);
	exit(code);
}


void	exec_history()
{
	HIST_ENTRY	**history;
	int			i;

	history = history_list();
	if (!history)
		return;
	i = 0;
	while (history[i])
	{
		printf("%d %s\n", i + 1, history[i]->line);
		i++;
	}
}

void	exec_env(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve("/usr/bin/env", argv, environ);
		perror("env fail");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}

void	exec_export(char **argv)
{
	if (!argv[1])
		return;
	for (int i = 1; argv[i]; i++)
	{
		char *arg = argv[i];
		char *equal = strchr(arg, '=');
		if (!equal)
		{
			fprintf(stderr, "export: invalid format: %s\n", arg);
			continue;
		}

		*equal = '\0'; // split VAR=VALUE
		char *key = arg;
		char *value = equal + 1;

		if (setenv(key, value, 1) != 0)
			perror("setenv");
		
		*equal = '='; // restore original string
	}
}


void	exec_comms(char **argv)
{
	if (!argv || !argv[0])
		return;
	if (ft_strncmp(argv[0], "ls", 1) == 0)
		exec_ls(argv);
	else if (ft_strncmp(argv[0], "cd", 1) == 0)
		exec_cd(argv);
	else if (ft_strncmp(argv[0], "pwd", 1) == 0)
		exec_pwd();
	else if (ft_strncmp(argv[0], "echo", 1) == 0)
		exec_echo(argv);
	else if (ft_strncmp(argv[0], "env", 1) == 0)
		exec_env(argv);
	else if (ft_strncmp(argv[0], "exit", 1) == 0)
		exec_exit(argv);
	else if (ft_strncmp(argv[0], "history", 1) == 0)
		exec_history();
}