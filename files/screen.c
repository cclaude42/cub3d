/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:32:10 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/24 17:00:13 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray(t_all *s)
{
	double	angle;
	double	dist;

	angle = ((double)s->ray.i - (s->win.x / 2)) * 33 / (s->win.x / 2);
	angle = angle * M_PI / 180;
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

	x = floor(s->pos.x) + s->ray.v;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
		if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.v)] == '1')
		{
			s->hit.x = x;
			s->hit.y = y;
			s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			return ;
		}
		x += (2 * s->ray.v - 1);
		y += (2 * s->ray.v - 1) * s->ray.y / s->ray.x;
	}
	s->hit.x = s->pos.x;
	s->hit.y = s->pos.y;
	s->hit.d = 1000000000;
}

void	ft_hor(t_all *s)
{
	double	y;
	double	x;

	y = floor(s->pos.y) + s->ray.w;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
	{
		if (s->map.tab[(int)(y - 1 + s->ray.w)][(int)floor(x)] == '1')
		{
			if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y))
			{
				s->hit.x = x;
				s->hit.y = y;
				s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			}
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
	s->stk = malloc(sizeof(t_stk) * s->win.x);
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
}
