/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 05:38:55 by elbenkri          #+#    #+#             */
/*   Updated: 2017/12/04 19:40:09 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

char			*ft_strdup(char *s1)
{
  int		i;
  char		*str;

  i = 0;
  if (s1 == 0)
    {
      if ((str = (char*)malloc(sizeof(*str) * 0 + 1)) == NULL)
	return (0);
    }
  else
    {
      if ((str = (char*)malloc(sizeof(*str) * ft_strlen(s1) + 1)) == NULL)
	return (0);
      while (s1[i])
	{
	  str[i] = s1[i];
	  i++;
	}
      if (s1[0] != 0)
	free(s1);
    }
  str[i] = 0;
  return (str);
}

static int		ft_norm(char **line, char **tab, char **rst, int flags)
{
  if (flags == 1)
    {
      if (*tab != 0 && (*rst = ft_strcdup(ft_strchr(*tab, '\n'), 0)))
	{
	  *line = ft_strjoin_free(ft_strcdup(*tab, '\n'), 0);
	  *tab = *rst + 1;
	  return (1);
	}
    }
  else if (flags == 2)
    {
      if (*tab != 0 && ft_strlen(*tab) != 0)
	{
	  tab[0][ft_strlen(*tab)] = 0;
	  *line = ft_strjoin_free(*tab = ft_strdup(*tab), 0);
	  *tab = 0;
	  return (1);
	}
    }
  return (0);
}

int				get_next_line(const int fd, char **line)
{
  int			ret;
  char			*buf;
  static char		*tab[4096];
  char			*rst;

  rst = NULL;
  buf = ft_strnew(BUFF_SIZE + 1);
  if (fd < 0 || fd > 4096 || (read(fd, "", 0) < 0))
    return (-1);
  if (ft_norm(line, &tab[fd], &rst, 1))
    return (1);
  while ((ret = read(fd, buf, BUFF_SIZE)))
    {
      buf[ret] = '\0';
      if (!(rst = ft_strchr(buf, '\n')))
	  tab[fd] = ft_strjoin_free(tab[fd] = ft_strdup(tab[fd]), buf);
      if ((rst = ft_strchr(buf, '\n')))
	{
	  *line = ft_strjoin_free(tab[fd] = ft_strdup(tab[fd]), ft_strcdup(buf, '\n'));
	  tab[fd] = rst + 1;
	  return (1);
	}
      buf = ft_strnew(BUFF_SIZE + 1);
    }
  return (ft_norm(line, &tab[fd], &rst, 2));
}
