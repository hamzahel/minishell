/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:30:04 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:01:42 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_filter(void *ptr, t_gc_flag append_flag)
{
	if (!ptr)
		_error_exit("malloc", strerror(errno), 1);
	if (!gc_append(g_glob.gc, ptr, append_flag))
		_error_exit("malloc", strerror(errno), 1);
	return (ptr);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, n);
	return (ret);
}

char	*ft_chardup(char c)
{
	char	*ret;

	ret = (char *)malloc(2);
	if (!ret)
		return (NULL);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
