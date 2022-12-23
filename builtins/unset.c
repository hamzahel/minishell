/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:02:51 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:32:45 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

void	unset_var(t_env **env, char *arg)
{
	t_env	*tmp_env;
	t_env	*prev;

	tmp_env = *env;
	prev = NULL;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, arg) == 0)
		{
			if (prev)
				prev->next = tmp_env->next;
			else
				*env = tmp_env->next;
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}

void	unset(char **args)
{
	int	i;
	int	status;

	status = 0;
	args++;
	if (!g_glob.venv || !*args)
		return ;
	while (*args)
	{
		i = 0;
		while ((*args)[i] && (ft_isalnum((*args)[i]) || (*args)[i] == '_'))
			i++;
		if ((*args)[i])
		{
			_error("unset", "invalid identifier", 1);
			status = 1;
			args++;
			continue ;
		}
		unset_var(&g_glob.venv, *args);
		args++;
	}
	set_status(status);
}
