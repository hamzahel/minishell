/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:30:22 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:03:54 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(int builtin, char **para)
{
	if (builtin == ECHO)
		echo(para);
	else if (builtin == PWD)
		pwd();
	else if (builtin == CD)
		cd(para);
	else if (builtin == EXIT)
		ft_exit(para);
	else if (builtin == UNSET)
		unset(para);
	else if (builtin == EXPORT)
		export(para);
	else if (builtin == ENV)
		env(para);
}

void	traitement(int in, int out, t_cmd *cmd)
{
	int		ret;
	char	*tmp;
	char	**para;

	if (cmd->fd_in > 2)
		in = cmd->fd_in;
	if (cmd->fd_out > 2)
		out = cmd->fd_out;
	ft_dup2(out, 1);
	ft_dup2(in, 0);
	if (cmd->exec)
	{
		ret = isbuiltins(cmd->exec->arg);
		if (ret != 0)
		{
			exec_builtins(ret, export_args_arr(cmd->exec));
			exit(0);
		}
		para = export_args_arr(cmd->exec);
		tmp = get_path(para);
		if (!tmp)
			tmp = *para;
		execve(tmp, para, export_env_arr());
		_error_exit(tmp, strerror(errno), 127);
	}
}

int	assign_fork(t_mini *mini, t_cmd *cmd, int *in, int *out)
{
	pid_t	pid;

	(void) in;
	if (cmd->fd_in > 2)
		*in = cmd->fd_in;
	if (cmd->fd_out > 2)
		*out = cmd->fd_out;
	if (cmd->cnt == mini->pipes)
		*out = 1;
	pid = fork();
	if (pid != 0 && cmd->cnt == mini->pipes)
		mini->pid[0] = pid;
	return (pid);
}

void	parent(t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	while (pid != -1)
	{
		if (pid == mini->pid[0])
			mini->pid[1] = status;
		pid = waitpid(-1, &status, 0);
	}
	g_glob.status = mini->pid[1];
}

void	exec(t_mini *mini)
{
	t_cmd	*cmd;
	int		fd[2];
	int		io[2];
	pid_t	pid;

	io[0] = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		pipe(fd);
		io[1] = fd[1];
		pid = assign_fork(mini, cmd, &io[0], &io[1]);
		if (pid == 0 && !close(fd[0]))
		{
			sig_restore();
			redirection(cmd);
			traitement(io[0], io[1], cmd);
		}
		close_file(&io[0], 0);
		close_file(&io[1], 1);
		close(fd[1]);
		io[0] = fd[0];
		cmd = cmd->next;
	}
	parent(mini);
}
