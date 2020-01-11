/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/11 18:06:46 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_texline(t_all *s, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, i);
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && line[*i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, i);
	else if (line[*i] == 'W' && line[*i + 1] == 'E' && line[*i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, i);
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && line[*i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, i);
	else if (line[*i] == 'D' && line[*i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.d, line, i);
	else if (line[*i] == 'E' && line[*i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.x, line, i);
	else if (line[*i] == 'S' && line[*i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.i, line, i);
	else if (line[*i] == 'T' && line[*i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.j, line, i);
	return (s->err.n);
}

int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if ((line[i] == '1' && line[i + 1] == ' ') || s->err.m == 1)
		s->err.n = ft_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.c, line, &i);
	else if (ft_is(POS, line[i]) || line[i] == 'D' || line[i] == 'T')
		s->err.n = ft_texline(s, line, &i);
	if (s->err.n == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0 || (read(fd, buf, 0) < 0))
		return (-3);
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-3);
		buf[read_size] = '\0';
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-3);
	}
	if ((*line = get_line(stock)) == NULL)
		return (-3);
	if ((stock = stock_trim(stock)) == NULL)
		return (-3);
	if (read_size != 0)
		return (1);
	free(stock);
	stock = NULL;
	return (0);
}

int		ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	line = NULL;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((ret = ft_line(s, line)) == -1)
			break ;
		free(line);
	}
	free(line);
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	ft_pos(s);
	s->spr = NULL;
	ft_slist(s);
	return (ft_parcheck(s));
}
