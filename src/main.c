#include "./minishell.h"

int main(int ac, char **av)
{
	t_shell	mini;

	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	printf("%s", HEADER);
	//ft_init_shell(&mini, envp);
	ft_minishell(&mini);
	return (EXIT_SUCCESS);
}
