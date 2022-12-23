/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:27:33 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:27:49 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_out(t_cmd *cmd, int out)
{
	if (cmd->red != NULL && cmd->red->type == OUT)
	{
		redirection(cmd);
		return (cmd->fd_out);
	}
	else
		return (out);
}

int	return_in(t_cmd *cmd, int in)
{
	if (cmd->red != NULL && cmd->red->type == IN)
	{
		redirection(cmd);
		return (cmd->fd_in);
	}
	else
		return (in);
}

void	execute(t_mini *mini)
{
	t_cmd	*tcmd;
	int		isb;

	if (!mini || !mini->cmd)
		return ;
	tcmd = mini->cmd;
	isb = 0;
	if (tcmd->exec)
		isb = isbuiltins(tcmd->exec->arg);
	if (mini->pipes == 0 && isb > 0)
	{
		redirection(tcmd);
		ft_dup2(tcmd->fd_out, 1);
		ft_dup2(tcmd->fd_in, 0);
		if (tcmd)
			exec_builtins(isb, export_args_arr(tcmd->exec));
	}
	else
		exec(mini);
}
