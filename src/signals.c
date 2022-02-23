# include "../minishell.h"

void	sig_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	signal_exit_status = 1;
}

void	sig_handler2(int signum)
{
	(void)signum;
	ft_putendl_fd("", 1);
}

void	sig_handler3(int signum)
{
	(void) signum;

	if (signum == SIGINT)
	{
		write(1, "^C\n", 3);
		signal_exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		write(1, "^\\Quit: 3\n", 10);
		signal_exit_status = 131;
	}
}

void	set_exit_status(int cmd_i)
{
	if (WIFEXITED(signal_exit_status))
		signal_exit_status = WEXITSTATUS(signal_exit_status);
	else if (WIFSIGNALED(signal_exit_status))
	{
//		if (WTERMSIG(signal_exit_status) == SIGQUIT)
//			write(1, "Quit: 3\n", 8);
		signal_exit_status = 128 + WTERMSIG(signal_exit_status);
	}
}
