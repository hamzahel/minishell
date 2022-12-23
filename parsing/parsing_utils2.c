/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:15:55 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:19:09 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sq_mode(char **line)
{
	int		len;
	char	*word;

	(*line)++;
	len = 0;
	while ((*line)[len] && (*line)[len] != '\'')
		len++;
	word = gc_filter(ft_strndup((*line), len + 1), GC_TMP);
	(*line) += len + 1;
	return (word);
}

char	*word_mode(char **line)
{
	char	*word;
	int		len;

	word = NULL;
	len = 0;
	while ((*line)[len] && !ft_strchr(" |$<>\'\"", (*line)[len]))
		len++;
	if (len)
		word = gc_filter(ft_strndup((*line), len + 1), GC_TMP);
	(*line) += len;
	return (word);
}

char	*word_inside_dq(char *line, char **word_arr, int *size)
{
	int		len;

	len = 0;
	while (line[len] && line[len] != '\"' && line[len] != '$')
		len++;
	if (len)
	{
		word_arr[*size] = gc_filter(ft_strndup(line, len + 1), GC_TMP);
		(*size)++;
	}
	return (line + len);
}

char	*var_inside_dq(char *line, char **word_arr, int *size)
{
	int		len;
	char	*value;
	char	save;

	line++;
	if (*line != '?' && !ft_isalpha(*line))
	{
		word_arr[*size] = gc_filter(ft_chardup('$'), GC_TMP);
		(*size)++;
		return (line);
	}
	len = (*line == '?');
	if (*line != '?')
	{
		while (line[len] && ft_isalnum(line[len]))
			len++;
	}
	save = line[len];
	line[len] = 0;
	value = ft_getenv(line);
	line[len] = save;
	if (!value)
		value = "";
	word_arr[(*size)++] = value;
	return (line + len);
}

char	*dq_mode(char **line)
{
	int		i;
	int		len;
	int		size;
	char	*word_arr[512];

	(*line)++;
	if (**line == '\"')
		return ((*line)++, "");
	size = 0;
	len = 0;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			*line = var_inside_dq(*line, word_arr, &size);
		*line = word_inside_dq(*line, word_arr, &size);
	}
	(*line)++;
	i = 1;
	while (i < size)
		word_arr[0] = gc_filter(ft_strjoin(word_arr[0], word_arr[i++]), \
		GC_TMP);
	return (word_arr[0]);
}
