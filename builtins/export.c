/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:02:25 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:31:28 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_print(t_env *env)
{
	if (!env)
		return ;
	ex_print(env->next);
	if (env->value != NULL)
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
	else
		printf("declare -x %s\n", env->key);
}

void	modify_var(char *key, char *value)
{
	t_env	*tmp;

	if (!key)
		return ;
	if (!ft_getenv(key))
		push_venv(key, value);
	else
	{
		tmp = g_glob.venv;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, key))
			{
				tmp->value = value;
				return ;
			}
			tmp = tmp->next;
		}
	}
}

int	check_export_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isdigit(arg[i]) && i == 0)
			return (0);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export(char **para)
{
	int	status;

	status = 0;
	para++;
	if (!*para)
		ex_print(g_glob.venv);
	while (*para)
	{
		if (!check_export_args(*para))
		{
			_error("export", "invalid identifier", 1);
			status = 1;
			para++;
			continue ;
		}
		modify_var(getkey(*para), getvalue(*para));
		para++;
	}
	set_status(status);
}
