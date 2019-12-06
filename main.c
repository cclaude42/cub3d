/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/06 17:36:32 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// gcc -lmlx -framework OpenGL -framework AppKit main.c && ./a.out

int		ft_color(t_all *s)
{
	if (floor(s->hit.x) == s->hit.x)
		return (DARK_WALL);
	else if
		(floor(s->hit.y) == s->hit.y)
		return (LIGHT_WALL);
	else
		return (WHITE);
}

void	ft_column(t_all *s, int size)
{
	int	color;
	int	start;
	int end;

	start = s->win.x * (s->win.y - size) / 2;
	end = s->win.x * (s->win.y + size) / 2;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i < start)
			color = SKY;
		else if (s->ray.i > end)
			color = DIRT;
		else
			color = ft_color(s);
		s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color);
		s->ray.i += s->win.x;
	}
	s->ray.i -= s->win.x * s->win.y;
}

int		ft_size(t_all *s)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((float)s->ray.i / (s->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	correc = s->hit.d * cos(fisheye);
	return (round(s->win.y / correc));
}

void	ft_ver(t_all *s)
{
	double	x;
	double	y;

	x = floor(s->pos.x) + 1;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
	while (s->map.tab[(int)floor(y)][(int)x] != 1)
	{
		x += 1;
		y += s->ray.y / s->ray.x;
		if ((int)floor(y) >= s->map.y)
		{
			s->hit.x = s->pos.x;
			s->hit.y = s->pos.y;
			s->hit.d = 1000000000;
			return ;
		}
	}
	s->hit.x = x;
	s->hit.y = y;
	s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
}

void	ft_hor(t_all *s)
{
	double	y;
	double	x;

	y = floor(s->pos.y) + 1;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while (s->map.tab[(int)y][(int)floor(x)] != 1)
	{
		y += 1;
		x += s->ray.x / s->ray.y;
		if ((int)floor(x) >= s->map.x)
			return ;
	}
	if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y))
	{
		s->hit.x = x;
		s->hit.y = y;
		s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
	}
}

void 	ft_ray(t_all *s)
{
	double	angle;

	angle = ((double)s->ray.i - (s->win.x / 2)) * 33 / (s->win.x / 2);
	angle = angle * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
}

void	ft_screen(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	s->ray = ray;
	s->hit = hit;
	s->ray.i = 0;
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp, &s->img.sl, &s->img.end);
	while (s->ray.i < s->win.x)
	{
		printf("Enter loop   ");
		ft_ray(s);
		printf("Ray : ( %f ; %f )   ", s->ray.x, s->ray.y);
		ft_ver(s);
		printf("Hit : ( %f ; %f )   ", s->hit.x, s->hit.y);
		ft_hor(s);
		printf("Hit : ( %f ; %f )   ", s->hit.x, s->hit.y);
		ft_column(s, ft_size(s));
		printf("Out of loop\n");
		s->ray.i++;
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
	s->map.x = 10;
	s->map.y = 10;
}

void	ft_init(t_all *s)
{
	s->mlx.ptr = mlx_init();
	s->win.x = 720;
	s->win.y = 480;
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3d");
	s->pos.x = 7.12;
	s->pos.y = 7.12;
	s->dir.x = cos(40 * M_PI / 180);
	s->dir.y = sin(40 * M_PI / 180);
	map_fill(s);
}

void	close_window(t_all *s)
{
	mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	exit(0);
}

void	move_up(t_all *s)
{
	s->pos.x += s->dir.x / 2;
	s->pos.y += s->dir.y / 2;
	ft_screen(s);
}

void	move_down(t_all *s)
{
	s->pos.x -= s->dir.x / 2;
	s->pos.y -= s->dir.y / 2;
	ft_screen(s);
}

void	move_left(t_all *s)
{
	s->pos.x += s->dir.y / 2;
	s->pos.y -= s->dir.x / 2;
	ft_screen(s);
}

void	move_right(t_all *s)
{
	s->pos.x -= s->dir.y / 2;
	s->pos.y += s->dir.x / 2;
	ft_screen(s);
}

void	counter(t_all *s)
{
	s->dir.x = s->dir.x * cos(-0.05) - s->dir.y * sin(-0.05);
	s->dir.y = s->dir.y * cos(-0.05) + s->dir.x * sin(-0.05);
	ft_screen(s);
}

void	clockwise(t_all *s)
{
	s->dir.x = s->dir.x * cos(0.05) - s->dir.y * sin(0.05);
	s->dir.y = s->dir.y * cos(0.05) + s->dir.x * sin(0.05);
	ft_screen(s);
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		close_window(arg);
	else if (key == W)
		move_up(arg);
	else if (key == A)
		move_left(arg);
	else if (key == S)
		move_down(arg);
	else if (key == D)
		move_right(arg);
	else if (key == LEFT)
		counter(arg);
	else if (key == RIGHT)
		clockwise(arg);
	return (1);
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
	mlx_key_hook(s.win.ptr, ft_key, &s);
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
