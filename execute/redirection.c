/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:27:37 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:59:00 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in(t_cmd *cmd, t_red *red)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	red->fd = open(red->file, red->oflags);
	if (red->fd == -1)
	{
		_error("open", strerror(errno), 1);
		return (0);
	}
	cmd->fd_in = red->fd;
	return (1);
}

int	out(t_cmd *cmd, t_red *red)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	red->fd = open(red->file, red->oflags, 0644);
	if (red->fd == -1)
	{
		_error("open", strerror(errno), 1);
		return (0);
	}
	cmd->fd_out = red->fd;
	return (1);
}

int	do_redirect(t_cmd *cmd, t_red *red)
{
	if (red->type == IN)
		return (in(cmd, red));
	return (out(cmd, red));
}

void	redirection(t_cmd *cmd)
{
	t_red	*tmp_r;

	tmp_r = cmd->red;
	while (tmp_r)
	{
		if (tmp_r->is_heredoc)
			cmd->fd_in = tmp_r->fd;
		else
		{
			if (!do_redirect(cmd, tmp_r))
			{
				cmd->exec = NULL;
				return ;
			}
		}
		tmp_r = tmp_r->next;
	}
}
