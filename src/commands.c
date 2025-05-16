# include "./minishell.h"

void    exec_ls(char **argv)
{
    pid_t   pid;
    int     status;

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

void    exec_cd(char **argv)
{
    pid_t   pid;
    int     status;

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

void    exec_pwd(char **argv)
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    
    if (pid == 0)
    {
        execve("/bin/pwd", argv, NULL);
        perror("pwd fail");
        exit(EXIT_FAILURE);
    }
    else
        waitpid(pid, &status, 0);
}

void    exec_echo(char **argv)
{
    pid_t   pid;
    int     status;

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
    int i = 0;

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

void exec_exit(char **args)
{
    int code;

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


void    exec_history()
{
    HIST_ENTRY **history;
    int         i;

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

void    exec_comms(char **argv)
{
    if (!argv || !argv[0])
        return;
    if (strcmp(argv[0], "ls") == 0)
        exec_ls(argv);
    if (strcmp(argv[0], "cd") == 0)
        exec_cd(argv);
    if (strcmp(argv[0], "pwd") == 0)
        exec_pwd(argv);
    if (strcmp(argv[0], "echo") == 0)
        exec_echo(argv);
    if (strcmp(argv[0], "exit") == 0)
        exec_exit(argv);
    if (strcmp(argv[0], "history") == 0)
        exec_history();
}