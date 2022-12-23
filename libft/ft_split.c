/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 05:42:37 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 00:05:20 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str == 0)
			break ;
		while (*str && *str != c)
			str++;
		len++;
	}
	return (len);
}

static int	countchars(char **str, char c)
{
	int	i;

	i = 0;
	while ((*str)[i] != c && (*str)[i])
		i++;
	*str = *str + i + 1;
	if (i == 0)
		return (countchars(str, c));
	return (i);
}

static int	fillarray(char const *s, char **str, char c, int lenstr)
{
	char	*tmpc;
	int		i;
	int		z;
	int		lenchars;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (i < lenstr)
	{
		z = 0;
		lenchars = countchars(&tmp, c);
		tmpc = (char *)malloc(sizeof(char) * lenchars + 1);
		if (!tmpc)
			return (0);
		while (z < lenchars)
			if (*s++ != c)
				tmpc[z++] = *(s - 1);
		tmpc[z] = 0;
		str[i++] = tmpc;
	}
	str[i] = 0;
	return (1);
}

static void	cleararray(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
	str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tmps;
	int		lenstr;

	lenstr = 0;
	if (!s)
		return (NULL);
	lenstr = countwords(s, c);
	tmps = (char **)malloc(sizeof(char *) * (lenstr + 1));
	if (!tmps)
		return (NULL);
	if (!fillarray(s, tmps, c, lenstr))
		cleararray(tmps);
	return (tmps);
}
