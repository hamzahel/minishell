/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:42:30 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/25 18:56:39 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*new_mini(t_cmd *cmd, int pipes)
{
	t_mini	*ret;

	ret = gc_filter(malloc(sizeof(t_mini)), GC_TMP);
	ret->cmd = cmd;
	ret->pipes = pipes;
	save_io(ret);
	return (ret);
}

t_cmd	*new_cmd(t_arg *args, t_red *red)
{
	t_cmd	*new;

	new = gc_filter(malloc(sizeof(t_cmd)), GC_TMP);
	new->exec = args;
	new->red = red;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

t_red	*new_red(char *file, int type, int oflags, int is_heredoc)
{
	t_red	*new;

	new = gc_filter(malloc(sizeof(t_red)), GC_TMP);
	new->file = file;
	new->type = type;
	new->oflags = oflags;
	new->is_heredoc = is_heredoc;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

t_arg	*new_arg(char *arg)
{
	t_arg	*new;

	new = gc_filter(malloc(sizeof(t_arg)), GC_TMP);
	new->arg = arg;
	new->next = NULL;
	return (new);
}
