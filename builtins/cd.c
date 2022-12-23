/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:00:39 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:30:39 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_path(char **args)
{
	if (!*args)
		return (ft_getenv("HOME"));
	else if (ft_strcmp(*args, "-") == 0)
		return (ft_getenv("OLDPWD"));
	return (*args);
}

void	cd(char **args)
{
	char	*old;
	char	*new;

	args++;
	new = cd_path(args);
	if (!new)
	{
		_error("cd", "path error", 1);
		return ;
	}
	old = getcwd(NULL, 0);
	if (chdir(new) == -1)
	{
		_error("chdir", strerror(errno), 1);
		return ;
	}
	modify_var("OLDPWD", old);
	modify_var("PWD", getcwd(NULL, 0));
	set_status(0);
}
