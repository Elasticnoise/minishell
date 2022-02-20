#include "../minishell.h"

int	ft_check_exit_status(char *str)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		i++;
		sign++;
	}
	while (str && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if ((i - sign) > 19)
		return (-1);
	return (0);
}

int	ft_check_n(long long int n, char c)
{
	long long int	max;
	long long int	min;

	max = 9223372036854775807;
	min = -9223372036854775807;
	if (n > max / 10 || n < min / 10)
		return (-1);
	if (n == (max / 10) && (c == '8' || c == '9'))
		return (-1);
	if (n == (min / 10) && c == '9')
		return (-1);
	return (0);
}

int	ft_exit_status(char *str)
{
	long long int	n;
	int				i;
	int				sign;

	if (str && ft_strncmp("-9223372036854775808", str, ft_strlen(str)) == 0)
		return (0);
	n = 0;
	sign = 1;
	i = 0;
	if (str && str[i] == '-')
		sign = -1;
	if (str && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str && ft_isdigit(str[i]))
	{
		if (ft_check_n(n, str[i]))
			return (-1);
		n = 10 * n + (str[i] - 48) * sign;
		i++;
	}
	n = n % 256;
	while (n < 0)
		n = n + 256;
	return (n);
}

void	ft_exit_err_msg(char *str)
{
	signal_exit_status = 255;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	check_exit_status(t_env **env)
{
	if (get_shlvl(env) == 1)
		return (1);
	else
	{
		signal_exit_status = 0;
		return (0);
	}
}

int	ft_exit(t_token *token, t_env **n_env)
{
	lvl_down(n_env);
	ft_putstr_fd("exit\n", 1);
	if (ft_check_exit_status(token->cmd[1]))
		ft_exit_err_msg(token->cmd[1]);
	else
	{
		if (token->cmd[1] && token->cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		signal_exit_status = ft_exit_status(token->cmd[1]);
		if (signal_exit_status == -1)
			ft_exit_err_msg(token->cmd[1]);
	}
	return (signal_exit_status);
}
