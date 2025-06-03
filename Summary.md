# Summary From Project
This md summarises all important definitions or information from this project.

## Library - minishell.h

First, we'll describe the function of each struct::

1. `typedef enum e_signal`: 

2. `e_token_type`: it's use to classify the different types of inputs tokens we have. 

3. `typedef struct s_token t_token`: a list of node which saves the token create and the type of token. 

4. `typedef struct s_arg t_arg`: struct is filled with commands, arguments and redirections links. Struct is needed to know what to run per pipe part.

5. `typedef struct s_partser t_parser`: saves redirections for that command. It's needed to open files and hanlde redirect FDs.

> **Example**
> ```
> cat input.txt | grep "error" > out.txt
> --- 
> t_arg (cmd: cat)
>  - argv: ["cat", "input.txt"]
>  - parser: NULL
>
> t_arg (cmd: grep)
> - argv: ["grep", "error"]
>  - parser: [ type: TOKEN_REDIR_OUT, cmd: "out.txt" ]
> ```
