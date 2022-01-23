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

void	execute(char **cmd)
{
	if (ft_strncmp(main->cmd[1], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(main->cmd[1], "cd", 3) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(main->cmd[1], "pwd", 4) == 0)
		ft_pwd(cmd);
	else if (ft_strncmp(main->cmd[1], "export", 7) == 0)
		ft_export(cmd);
	else if (ft_strncmp(main->cmd[1], "unset", 6) == 0)
		ft_unset(cmd);
	else if (ft_strncmp(main->cmd[1], "env", 4) == 0)
		ft_env(cmd);
	else if (ft_strncmp(main->cmd[1], "exit", 5) == 0)
		ft_exit(cmd);
	else
		command_handler(cmd);


}

