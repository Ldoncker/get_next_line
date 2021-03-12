/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoncker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:17:35 by ldoncker          #+#    #+#             */
/*   Updated: 2020/08/31 12:33:28 by ldoncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	checkmalloc(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (-1);
}

static void	checkfree(char **s)
{
	if (s)
	{
		free(*s);
		*s = NULL;
	}
	return ;
}

static int	output(char **s, char **line, int fd, int r)
{
	int		cpt;
	char	*temp;

	if (r < 0)
		return (-1);
	cpt = 0;
	while (s[fd] != 0 && s[fd][cpt] != '\n' && s[fd][cpt] != '\0')
		cpt++;
	if (r == 0 && (s[fd] == 0 || s[fd][cpt] == '\0'))
	{
		if (!(*line = ft_strdup(s[fd])))
			return (checkmalloc(&s[fd]));
		checkfree(&s[fd]);
		return (0);
	}
	else if (s[fd] != 0 && s[fd][cpt] == '\n')
	{
		if (!(*line = ft_substr(s[fd], 0, cpt)))
			return (checkmalloc(&s[fd]));
		if (!(temp = ft_strdup(&s[fd][cpt + 1])))
			return (checkmalloc(&s[fd]));
		free(s[fd]);
		s[fd] = temp;
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	int			r;
	static char	*s[OPEN_MAX];
	char		*temp;

	if (BUFFER_SIZE < 1 || fd > OPEN_MAX || fd < 0 || !line)
		return (-1);
	while ((!(ft_strchr(s[fd], '\n'))) &&
			(r = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r] = '\0';
		if (!s[fd])
		{
			if (!(s[fd] = ft_strdup(buffer)))
				return (-1);
		}
		else
		{
			if (!(temp = ft_strjoin(s[fd], buffer)))
				return (checkmalloc(&s[fd]));
			free(s[fd]);
			s[fd] = temp;
		}
	}
	return (output(s, line, fd, r));
}
