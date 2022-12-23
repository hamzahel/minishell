/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:13:30 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/27 00:32:06 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_option(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

void	echo(char **para)
{
	bool	endl;

	endl = 1;
	para++;
	while (*para && is_n_option(*para))
	{
		endl = 0;
		para++;
	}
	while (*para)
	{
		ft_putstr_fd(*para, 1);
		para++;
		if (*para)
			write(1, " ", 1);
	}
	if (endl)
		write(1, "\n", 1);
	set_status(0);
}
