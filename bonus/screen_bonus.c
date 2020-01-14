/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:32:10 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/14 16:51:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_ray(t_all *s)
{
	double	angle;
	double	dist;

	angle = ((double)s->ray.i - (s->win.x / 2)) * ANG / (s->win.x / 2);
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	dist = hypot(s->ray.x, s->ray.y);
	s->ray.x /= dist;
	s->ray.y /= dist;
}

void	ft_dir(t_all *s)
{
	if (s->ray.x >= 0)
		s->ray.v = 1;
	else
		s->ray.v = 0;
	if (s->ray.y >= 0)
		s->ray.w = 1;
	else
		s->ray.w = 0;
}

void	ft_ver(t_all *s)
{
	double	x;
	double	y;
	char	c;

	x = floor(s->pos.x) + s->ray.v;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
		c = s->map.tab[(int)floor(y)][(int)floor(x - 1 + s->ray.v)];
		if (ft_is(WALL, c) || ft_is(DOOR, c))
		{
			s->hit.x = x;
			s->hit.y = y;
			s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			s->hit.c = c;
			ft_is(DOOR, c) ? ft_verdoor(s, x, y) : 0;
			return ;
		}
		x += (2 * s->ray.v - 1);
		y += (2 * s->ray.v - 1) * s->ray.y / s->ray.x;
	}
	s->hit.x = s->pos.x;
	s->hit.y = s->pos.y;
	s->hit.d = 1000000000;
	s->hit.c = 0;
}

void	ft_hor(t_all *s)
{
	double	y;
	double	x;
	char	c;

	y = floor(s->pos.y) + s->ray.w;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
	{
		c = s->map.tab[(int)floor(y - 1 + s->ray.w)][(int)floor(x)];
		if (ft_is(WALL, c) || ft_is(DOOR, c))
		{
			if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y) && ft_is(WALL, c))
			{
				s->hit.x = x;
				s->hit.y = y;
				s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
				s->hit.c = c;
			}
			else if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y))
				ft_hordoor(s, x, y);
			return ;
		}
		y += (2 * s->ray.w - 1);
		x += (2 * s->ray.w - 1) * s->ray.x / s->ray.y;
	}
}

void	ft_screen(t_all *s)
{
	int		bpp;
	int		sl;
	int		end;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	ft_sky(s);
	s->ray.i = 0;
	while (s->ray.i < s->win.y / 2)
		ft_floor(s);
	s->stk = malloc(sizeof(t_stk) * s->win.x);
	s->ray.i = 0;
	while (s->ray.i < s->win.x)
	{
		ft_ray(s);
		ft_dir(s);
		ft_ver(s);
		ft_hor(s);
		ft_stock(s);
		ft_column(s, ft_size(s));
		s->ray.i++;
	}
	ft_sprite(s);
	ft_hud(s);
}
