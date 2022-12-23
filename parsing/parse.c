/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:13:27 by omoussao          #+#    #+#             */
/*   Updated: 2022/03/27 02:01:15 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	_check(char **line, int quote[2])
{
	t_tok	nxt;

	if (**line == '|')
	{
		(*line)++;
		nxt = lookahead(*line);
		if (nxt == PIPE || nxt == END)
			return (0);
	}
	else if (**line == '<' || **line == '>')
	{
		(*line) += 1 + (*(*line) == (*line)[1]);
		nxt = lookahead((*line));
		if (nxt == PIPE || nxt == END)
			return (0);
	}
	else if (**line == '\'' || **line == '\"')
		handle_quotes(line, quote);
	else
		(*line)++;
	return (1);
}

bool	check_syntax(char *line)
{
	int		quote[2];

	quote[0] = 0;
	quote[1] = 0;
	if (*line == '|')
		return (0);
	while (*line)
	{
		if (!_check(&line, quote))
			return (0);
	}
	return (((quote[0] % 2 == 0) && (quote[1] % 2 == 0)));
}

char	*parse_arg(char *line, t_arg **arg)
{
	char	*word;

	line = skip_ws(line);
	if (!*line)
		return (line);
	if (*line == '\'')
		push_arg(arg, new_arg(sq_mode(&line)));
	else if (*line == '\"')
		push_arg(arg, new_arg(dq_mode(&line)));
	else if (*line == '$')
		push_arg(arg, new_arg(dollar_mode(&line)));
	else
	{
		word = word_mode(&line);
		if (word)
			push_arg(arg, new_arg(word));
	}
	return (line);
}

bool	make_mini(char *line, t_mini *mini)
{
	t_arg	*args;
	t_red	*red;

	args = NULL;
	red = NULL;
	reset_mini(mini);
	while (*line)
	{
		line = skip_ws(line);
		if (*line == '|')
		{
			(mini->pipes)++;
			push_cmd(&(mini->cmd), new_cmd(args, red));
			args = NULL;
			red = NULL;
			line++;
		}
		if ((*line == '>' || *line == '<') && !parse_red(&line, &red))
			return (0);
		else
			line = parse_arg(line, &args);
	}
	(mini->pipes)++;
	push_cmd(&(mini->cmd), new_cmd(args, red));
	return (1);
}

bool	parse(char *line, t_mini *mini)
{
	reset_mini(mini);
	if (!line)
		return (0);
	line = skip_ws(line);
	if (!*line)
		return (0);
	if (!check_syntax(line))
	{
		_error("parser", "syntax error!", 1);
		return (0);
	}
	if (!make_mini(line, mini))
	{
		reset_mini(mini);
		_error("parser", "parse error!", 1);
		return (0);
	}
	add_history(line);
	return (1);
}
