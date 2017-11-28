/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:20:55 by elbenkri          #+#    #+#             */
/*   Updated: 2017/11/28 17:41:55 by elbenkri         ###   ########.fr       */
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

	buf = ft_strnew(BUFF_SIZE);
	printf("tmp :%s\n", tmp);
	if (tmp != 0)
		*line = ft_strjoin(tmp, "");
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		if (strchr(buf, '\n'))
		{
			tmp = (char *)ft_memcdcpy(*line, buf, '\n', ft_strlen(buf));
			*line = ft_strdup(*line);
			return (1);
		}
		else
			*line = ft_strjoin(*line, buf);
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*ok;

	ok = (char*)malloc(sizeof(char) * 20);
	if (argc < 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	printf("retour :%d\n", get_next_line(fd, &ok));
	printf("fin :%s\n", ok);
	printf("retour 2: %d\n", get_next_line(fd, &ok));
	printf("fin 2: %s\n", ok);
	printf("retour 2: %d\n", get_next_line(fd, &ok));
	printf("fin 2: %s\n", ok);
	return (0);
}
