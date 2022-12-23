/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:19:19 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:19:32 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_mode(char **line)
{
	int		len;
	char	*value;
	char	save;

	(*line)++;
	if (**line != '?' && !ft_isalpha(**line))
		return (gc_filter(ft_chardup('$'), GC_TMP));
	len = 0;
	while ((*line)[len] && ft_isalnum((*line)[len]))
		len++;
	if (!len && (*line)[len] == '?')
		len++;
	save = (*line)[len];
	(*line)[len] = 0;
	value = ft_getenv((*line));
	(*line)[len] = save;
	if (!value)
		value = "";
	(*line) += len;
	return (value);
}
