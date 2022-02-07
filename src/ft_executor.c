# include "../minishell.h"

void 	cmd_to_lower(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			cmd[i][j] = ft_tolower(cmd[i][j]);
			j++;
		}
		i++;
	}
}

void 	command_handler(char **cmd)
{
	cmd_to_lower(cmd);
	/*TODO Need to add some code */
}

void	execute(t_token *token)
{
	if (ft_strncmp(token->cmd[0], "echo", 5) == 0)
		ft_echo(token);
	else if (ft_strncmp(token->cmd[0], "cd", 3) == 0)
		ft_cd(token);
	else if (ft_strncmp(token->cmd[0], "pwd", 4) == 0)
		ft_pwd(token);
	else if (ft_strncmp(token->cmd[0], "export", 7) == 0)
		ft_export(token);
	else if (ft_strncmp(token->cmd[0], "unset", 6) == 0)
		ft_unset(token);
	else if (ft_strncmp(token->cmd[0], "env", 4) == 0)
		ft_env(token);
	else if (ft_strncmp(token->cmd[0], "exit", 5) == 0)
		ft_exit(token);
	else
		command_handler(token);


}

