/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/11 23:55:26 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(s);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_north(s);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_south(s);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		ft_west(s);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		ft_east(s);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		ft_sprite(s);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_floor(s);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_ceiling(s);
	else if (line[i] == '1' && line[i + 1] == ' ')
		ft_map(s);
}

void	ft_parse(t_all *s)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		ft_line(line);
		free(line);
	}
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
