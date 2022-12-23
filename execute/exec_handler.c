/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <hel-ayac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:30:55 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/27 01:39:29 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isbuiltins(char *head)
{
	if (!ft_strcmp(head, "echo"))
		return (ECHO);
	else if (!ft_strcmp(head, "pwd"))
		return (PWD);
	else if (!ft_strcmp(head, "cd"))
		return (CD);
	else if (!ft_strcmp(head, "exit"))
		return (EXIT);
	else if (!ft_strcmp(head, "unset"))
		return (UNSET);
	else if (!ft_strcmp(head, "export"))
		return (EXPORT);
	else if (!ft_strcmp(head, "env"))
		return (ENV);
	return (0);
}

char	*get_path(char **para)
{
	char			*tmp[2];
	char			**spliter;
	int				i;
	struct stat		st;
	char			*flag;

	flag = NULL;
	if (!**para || ft_strchr(*para, '/'))
		return (NULL);
	i = 0;
	tmp[0] = ft_getenv("PATH");
	if (!tmp[0])
		return (NULL);
	spliter = gc_filter(ft_split(tmp[0], ':'), GC_TMP);
	while (spliter[i])
	{
		gc_filter(spliter[i], GC_TMP);
		tmp[0] = gc_filter(ft_strjoin(spliter[i], "/"), GC_TMP);
		tmp[1] = gc_filter(ft_strjoin(tmp[0], para[0]), GC_TMP);
		if (!stat(tmp[1], &st))
			flag = tmp[1];
		i++;
	}
	return (flag);
}

void	ft_dup2(int dest, int src)
{
	if (dest != src)
	{
		dup2(dest, src);
		close(dest);
	}
}

void	close_file(int *fd1, int std)
{
	if (*fd1 != std)
		close(*fd1);
}
