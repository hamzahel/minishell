/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:02:34 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/26 23:02:43 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **args)
{
	int	i;

	args++;
	if (*args)
	{
		i = 0;
		while ((*args)[i])
			if (!ft_isdigit((*args)[i++]))
				_error_exit("exit", "numeric argument required", 1);
		if (args[1])
		{
			_error("exit", "too many arguments", 1);
			return ;
		}
		exit(ft_atoi(*args));
	}
	else
		exit(0);
}
