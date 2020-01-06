/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:37:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/06 13:21:47 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_pixel(t_all *s, double i)
{
	int	index;

	if (floor(s->hit.y) == s->hit.y)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x));
		if (s->ray.w == 1)
			return (s->tex.s[index]);
		else if (s->ray.w == 0)
			return (s->tex.n[index]);
	}
	else if (floor(s->hit.x) == s->hit.x)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
		if (s->ray.v == 1)
			return (s->tex.e[index]);
		else if (s->ray.v == 0)
			return (s->tex.w[index]);
	}
	return (BLACK);
}

void			ft_column(t_all *s, int size)
{
	unsigned int	color;
	int				start;
	int				count;

	start = s->win.x * (s->win.y - size) / 2;
	if (size > s->win.y)
		count = (size - s->win.y) / 2;
	else
		count = 0;
	color = s->tex.c;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i >= start && count < size)
		{
			color = ft_pixel(s, (double)count / size);
			count++;
		}
		else if (count == size)
			color = s->tex.f;
		s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color);
		s->ray.i += s->win.x;
	}
	s->ray.i -= s->win.x * s->win.y;
}

int				ft_size(t_all *s)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((double)s->ray.i / (s->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	correc = (double)s->hit.d * cos(fisheye);
	return (round(s->win.y / correc));
}

void			ft_stock(t_all *s)
{
	s->stk[s->ray.i].x = s->ray.x;
	s->stk[s->ray.i].y = s->ray.y;
	s->stk[s->ray.i].d = s->hit.d;
}
