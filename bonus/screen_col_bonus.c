/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_col_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:37:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/14 17:55:49 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	ft_pixel(t_all *s, double i)
{
	int	index;

	if (floor(s->hit.y) == s->hit.y || floor(s->hit.y) + 0.5 == s->hit.y)
		index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x));
	else if (floor(s->hit.x) == s->hit.x || floor(s->hit.x) + 0.5 == s->hit.x)
		index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
	if (s->hit.c == '1')
		return (s->tex.n[index]);
	else if (s->hit.c == '2')
		return (s->tex.s[index]);
	else if (s->hit.c == '3')
		return (s->tex.e[index]);
	else if (s->hit.c == '4' || s->hit.c == '6')
		return (s->tex.w[index]);
	else if (s->hit.c == '5')
		return (s->tex.x[index]);
	else if (s->hit.c == 'D')
		return (s->tex.d[index]);
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
	color = NONE;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i >= start && count < size)
		{
			color = ft_pixel(s, (double)count / size);
			count++;
		}
		else if (count == size)
			color = NONE;
		if (color != NONE)
			s->img.adr[s->ray.i] = ft_shadow(s, color);
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
