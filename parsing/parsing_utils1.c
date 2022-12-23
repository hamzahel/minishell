/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:13:42 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/26 23:20:19 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_mini(t_mini *mini)
{
	mini->cmd = NULL;
	mini->pipes = -1;
}

char	*skip_ws(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

char	*skip_quote(char *line, char qt)
{
	while (*line && *line != qt)
		line++;
	return (line);
}

t_tok	lookahead(char *line)
{
	line = skip_ws(line);
	if (!*line)
		return (END);
	else if (*line == '|')
		return (PIPE);
	else if (*line == '>' || *line == '<')
		return (RED);
	else if (*line == '$' && (ft_isalpha(line[1]) || line[1] == '?'))
		return (VAR);
	else
		return (WORD);
}

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret == -1)
		_error("pipe", strerror(errno), 1);
	return (ret);
}
