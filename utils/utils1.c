/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:26:51 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:00:06 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_venv(char *key, char *value)
{
	t_env	*new;

	new = gc_filter(malloc(sizeof(t_env)), GC_ALL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!g_glob.venv)
		g_glob.venv = new;
	else
	{
		new->next = g_glob.venv;
		g_glob.venv = new;
	}
}

void	venv_init(char **env)
{
	int		i;
	char	*key;

	if (!env || !*env)
		push_venv("PATH", _PATH_STDPATH);
	i = -1;
	while (env[++i])
	{
		key = getkey(env[i]);
		push_venv(key, getenv(key));
	}
}

char	**export_env_arr(void)
{
	char	**ret;
	int		len;
	t_env	*p;

	len = 0;
	p = g_glob.venv;
	while (p)
	{
		len++;
		p = p->next;
	}
	ret = gc_filter(malloc((len + 1) * sizeof(char *)), GC_TMP);
	ret[len] = NULL;
	p = g_glob.venv;
	while (p)
	{
		ret[--len] = gc_filter(ft_strjoin(p->key, \
		gc_filter(ft_strjoin("=", p->value), GC_TMP)), GC_TMP);
		p = p->next;
	}
	return (ret);
}

char	**export_args_arr(t_arg *arg)
{
	char	**ret;
	int		len[2];
	t_arg	*p;

	len[0] = 0;
	p = arg;
	while (p)
	{
		len[0]++;
		p = p->next;
	}
	ret = gc_filter(malloc((len[0] + 1) * sizeof(char *)), GC_TMP);
	p = arg;
	len[1] = 0;
	while (len[1] < len[0])
	{
		ret[len[1]] = p->arg;
		len[1]++;
		p = p->next;
	}
	ret[len[0]] = NULL;
	return (ret);
}

char	*ft_getenv(char *key)
{
	t_env	*venv;

	if (!key || !g_glob.venv)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		return (gc_filter(ft_itoa(get_status()), GC_TMP));
	venv = g_glob.venv;
	while (venv)
	{
		if (ft_strcmp(key, venv->key) == 0)
			return (venv->value);
		venv = venv->next;
	}
	return (NULL);
}
