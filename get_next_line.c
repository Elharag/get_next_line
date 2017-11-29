/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:20:55 by elbenkri          #+#    #+#             */
/*   Updated: 2017/11/29 19:26:50 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

static void    *ft_memcdcpy(void *dst, const void *src, int c, size_t n)
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
	static char	*tmp = NULL;

	if (BUFF_SIZE <= 0)
		return (0);
	if (fd < 0)
		return (-1);
	buf = ft_strnew(BUFF_SIZE + 1);
	*line = ft_strnew(BUFF_SIZE + 1);
	if (tmp != 0 && !ft_strchr(tmp, '\n'))
		*line = ft_strjoin(tmp, "");
	else if (tmp != 0 && ft_strchr(tmp, '\n'))
	{
		tmp = (char *)ft_memcdcpy(*line, tmp, '\n', ft_strlen(tmp));
		*line = ft_strdup(*line);
		return (1);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ft_strchr(buf, '\n'))
		{
			tmp = (char *)ft_memcdcpy(*line, buf, '\n', ft_strlen(buf));
//			*line = ft_strdup(*line);
			return (1);
		}
		else
			*line = ft_strjoin(*line, buf);
	}
	if (tmp != 0 && ret == 0)
	{
		tmp = 0;
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*ok;

//	ok = (char*)malloc(sizeof(char) * 20);
	if (argc < 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
/*	printf("%d\n", get_next_line(fd, &ok));
	printf("fin :%s\n", ok);
	printf("%d\n", get_next_line(fd, &ok));
	printf("fin :%s\n", ok);
	printf("%d\n", get_next_line(fd, &ok));
	printf("fin :%s\n", ok);*/
	while (get_next_line(fd, &ok) > 0)
	{
		printf("fin :%s\n", ok);
	}
//		printf("fin :%s\n", ok);
	return (0);
}
