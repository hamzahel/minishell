/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:21:23 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/27 02:01:26 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delim)
{
	int		hfd[2];
	int		len;
	char	*buff;

	if (!delim || ft_pipe(hfd) == -1)
		return (-1);
	len = ft_strlen(delim);
	while (true)
	{
		buff = readline("> ");
		if (!buff || ft_memcmp(delim, buff, len + 1) == 0)
			break ;
		gc_append(g_glob.gc, buff, GC_TMP);
		write(hfd[OUT], buff, ft_strlen(buff));
		write(hfd[OUT], "\n", 1);
	}
	return (close(hfd[OUT]), hfd[IN]);
}

t_red	*init_red(char **line)
{
	int		type;
	int		oflags;
	bool	is_heredoc;

	type = IN;
	oflags = O_RDONLY;
	if (**line == '>')
	{
		type = OUT;
		oflags = O_CREAT | O_WRONLY | O_TRUNC;
		if (**line == (*line)[1])
			oflags = O_CREAT | O_WRONLY | O_APPEND;
	}
	is_heredoc = (**line == '<' && (*line)[1] == '<');
	(*line) += 1 + ((*line)[1] == **line);
	(*line) = skip_ws(*line);
	return (new_red(NULL, type, oflags, is_heredoc));
}

bool	parse_red(char **line, t_red **red)
{
	t_red	*red_node;
	char	save;
	int		len;

	red_node = init_red(line);
	red_node->file = *line;
	len = 0;
	while ((*line)[len] && !ft_strchr(" |<>\'\"", (*line)[len]))
		len++;
	save = (*line)[len];
	(*line)[len] = 0;
	if (!red_node->is_heredoc && *(red_node->file) == '$')
	{
		red_node->file = ft_getenv((*line) + 1);
		if (!(red_node->file))
			return (0);
	}
	else if (!red_node->is_heredoc)
		red_node->file = gc_filter(ft_strdup(*line), GC_TMP);
	else
		red_node->fd = heredoc(red_node->file);
	(*line)[len] = save;
	(*line) += len;
	push_red(red, red_node);
	return (1);
}

void	handle_quotes(char **line, int quote[2])
{
	(quote[(**line == '\"')])++;
	*line = skip_quote((*line) + 1, **line);
	if ((**line == '\'' || **line == '\"'))
	{
		(quote[(**line == '\"')])++;
		(*line)++;
	}
}
