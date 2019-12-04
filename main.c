/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/04 16:05:05 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// gcc -lmlx -framework OpenGL -framework AppKit main.c && ./a.out

void	close_window(t_all *s)
{
	mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	exit(0);
}

int		deal_key(int key, void *arg)
{
	if (key == 53)
		close_window(arg);
	return (1);
}

void	ft_column(t_all *s, int index, int size)
{
	while (index < s->win.x * s->win.y / 2 - size * s->win.x)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, SKY);
		index += s->win.x;
	}
	while (index < s->win.x * s->win.y / 2 + size * s->win.x)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, WALL);
		index += s->win.x;
	}
	while (index < s->win.x * s->win.y)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, DIRT);
		index += s->win.x;
	}
}

void	ft_screen(t_all *s)
{
	int		index;
	int		size;

	index = 0;
	size = 40;
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.sl, &s->img.end);
	while (index < s->win.x)
	{
		ft_column(s, index, size);
		index++;
	}
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
}

void	map_fill(t_all *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		while (j < 10)
		{
			if (i == 0 || i == 9 || j == 0 || j == 9)
				s->map.tab[i][j] = 1;
			else
				s->map.tab[i][j] = 0;
			j++;
		}
		i++;
		j = 0;
	}
}

void	ft_init(t_all *s)
{
	s->mlx.ptr = mlx_init();
	s->win.x = 720;
	s->win.y = 480;
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3d");
	s->pos.x = 5.12;
	s->pos.y = 3.80;
	s->dir.x = cos(68 * M_PI / 180);
	s->dir.y = sin(68 * M_PI / 180);
	map_fill(s);
}

void	ft_cubed(t_all s)
{
	t_map	map;
	t_pos	pos;
	t_dir	dir;

	s.map = map;
	s.pos = pos;
	s.dir = dir;
	ft_init(&s);
	ft_screen(&s);
	mlx_key_hook(s.win.ptr, deal_key, &s);
	mlx_loop(s.mlx.ptr);
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	ft_cubed(s);
	return (0);
}
