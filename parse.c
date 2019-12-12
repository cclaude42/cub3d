/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/12 18:25:55 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	ft_spaceskip(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int		ft_atoi(char *str, int *i)
{
	int	num;

	num = 0;
	ft_spaceskip(str, i);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		num = num * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (num);
}

void	ft_res(t_all *s, char *line, int *i)
{
	(*i)++;
	s->win.x = ft_atoi(line, i);
	s->win.y = ft_atoi(line, i);
	ft_spaceskip(line, i);
}

unsigned int	**ft_table(void)
{
	unsigned int	**tab;

	tab = malloc(sizeof(unsigned int *) * 2);
	tab[0] = malloc(sizeof(unsigned int) * 2);
	tab[1] = malloc(sizeof(unsigned int *) * 2);
	tab[0][0] = 2;
	tab[0][1] = 3;
	tab[1][0] = 4;
	tab[1][1] = 6;
	return (tab);
}

void	ft_texture(unsigned int ***tab, char *line, int *i)
{
	*tab = ft_table();
}

void	ft_colors(unsigned int *color, char *line, int *i)
{
	(*i)++;
	*color = ft_atoi(line, i) * 256 * 256;
	(*i)++;
	*color += ft_atoi(line, i) * 256;
	(*i)++;
	*color += ft_atoi(line, i);
	ft_spaceskip(line, i);
}

void	ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(s, line, &i);
	// else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		// ft_texture(&s->tex.n, line, &i);
	// else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.s, line, &i);
	// else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.w, line, &i);
	// else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.e, line, &i);
	// else if (line[i] == 'S' && line[i + 1] == ' ')
	// 	ft_texture(&s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_colors(&s->tex.c, line, &i);
	// else if (line[i] == '1' && line[i + 1] == ' ')
		// ft_map(s, line, &i);
}

void	ft_parse(t_all *s)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	s->win.x = 3;
	s->win.y = 5;
	s->pos.x = 4;
	fd = open("map.cub", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_line(s, line);
		free(line);
	}
	close(fd);
	printf("Res : %d %d\n", s->win.x, s->win.y);
	printf("%u\n", s->tex.c);
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_tex	tex;
	t_map	map;
	t_pos	pos;
	t_dir	dir;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.tex = tex;
	s.map = map;
	s.pos = pos;
	s.dir = dir;
	ft_parse(&s);
	return (0);
}
