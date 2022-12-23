/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:53:34 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:03:37 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!*cmd)
	{
		new->cnt = 0;
		*cmd = new;
	}
	else
	{
		last = *cmd;
		while (last->next)
			last = last->next;
		last->next = new;
		new->cnt = last->cnt + 1;
	}
}

void	push_red(t_red **red, t_red *new)
{
	t_red	*last;

	if (!*red)
		*red = new;
	else
	{
		last = *red;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	push_arg(t_arg **arg, t_arg *new)
{
	t_arg	*last;

	if (!*arg)
		*arg = new;
	else
	{
		last = *arg;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
