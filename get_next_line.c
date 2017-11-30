/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:20:55 by elbenkri          #+#    #+#             */
/*   Updated: 2017/11/30 10:56:31 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

static void    *ft_memccat(void *dst, const void *src, int c, size_t n)
{
    size_t  i;
	size_t	j;

    i = 0;
	j = ft_strlen((const char *)dst);
    while (i < n)
    {
        if (((unsigned char *)src)[i] != (unsigned char)c)
			((unsigned char *)dst)[j] = ((unsigned char *)src)[i];
        if (((unsigned char *)src)[i] == (unsigned char)c)
		{
			((unsigned char *)dst)[j] = 0;
			return ((void *)src + i + 1);
		}
		i++;
		j++;
    }
    return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*tmp[4096];

	if (fd < 0)
		return (EOF);
	buf = ft_strnew(BUFF_SIZE + 1);
	*line = ft_strnew(BUFF_SIZE + 1);
	if (tmp[fd] != 0 && !ft_strchr(tmp[fd], '\n'))
		*line = ft_strjoin(tmp[fd], "");
	else if (tmp[fd] != 0 && ft_strchr(tmp[fd], '\n'))
	{
//		ft_putstr("olololo\n");
		tmp[fd] = (char *)ft_memccat(*line, tmp[fd], '\n', ft_strlen(tmp[fd]));
//		*line = ft_strdup(*line);
		return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ft_strchr(buf, '\n'))
		{
//			ft_putstr("okokok\n");
			tmp[fd] = (char *)ft_memccat(*line, buf, '\n', ft_strlen(buf));
//			*line = ft_strdup(*line);
			return (1);
		}
		else
			*line = ft_strjoin(*line, buf);
	}
	if (ret == 0)
	{
//		ft_putstr("okokoddfgfdk\n");
		if (tmp[fd] == 0)
		{
			tmp[fd] = *line;
			return (0);
		}
		else
			tmp[fd] = 0;
//		ft_putstr("odssdfkokosdfdssk\n");
	}
	return (1);
}
/*
int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*ok;

//	ok = (char*)malloc(sizeof(char) * 20);
	if (argc < 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &ok)) > 0)
	{
		printf("fin : %d %s\n", ret, ok);
	}
//		printf("fin :%s\n", ok);
	return (0);
}
*/
