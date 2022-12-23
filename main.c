/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:16:41 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/27 02:05:30 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob
	= {
	.gc = NULL,
	.venv = NULL,
	.is_runing = 0,
	.status = 0
};

void	disp(t_cmd *cmd);

static void	global_init(char **env)
{
	sig_init();
	g_glob.gc = gc_init();
	if (!g_glob.gc)
		_error_exit("malloc", strerror(errno), 1);
	venv_init(env);
}

void	save_io(t_mini *mini)
{
	mini->tmp_fd[0] = dup(STDIN_FILENO);
	mini->tmp_fd[1] = dup(STDOUT_FILENO);
	if (mini->tmp_fd[0] == -1 || mini->tmp_fd[1] == -1)
		_error("dup", strerror(errno), 1);
}

void	reset_io(t_mini *mini)
{
	if (dup2(mini->tmp_fd[0], STDIN_FILENO) == -1
		|| dup2(mini->tmp_fd[1], STDOUT_FILENO) == -1)
		_error("dup2", strerror(errno), 1);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_mini	mini;

	(void)argc;
	(void)argv;
	global_init(env);
	save_io(&mini);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		gc_append(g_glob.gc, line, GC_TMP);
		g_glob.is_runing = 1;
		if (parse(line, &mini))
			execute(&mini);
		g_glob.is_runing = 0;
		gc_clean(&g_glob.gc, GC_TMP);
		reset_mini(&mini);
		reset_io(&mini);
	}
	gc_clean(&g_glob.gc, GC_DESTROY_SELF);
	return (0);
}
