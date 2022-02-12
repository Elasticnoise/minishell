# include "../minishell.h"

void	sig_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
//	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	signal_exit_status = 1;
}

void	sig_handler2(int signum)
{
	(void)signum;
	ft_putendl_fd("", 1);
}
