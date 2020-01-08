/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_row_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:34:47 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/08 17:13:16 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	ft_shadow(t_all *s, unsigned int col)
{
	double	shadow;
	int		r;
	int		g;
	int		b;

	if (SHADOW == 0)
		return (col);
	shadow = 1 - hypot(s->pos.x - s->hit.x, s->pos.y - s->hit.y) / SHADOW;
	if (shadow < 0)
		shadow = 0;
	r = (col / (256 * 256) % 256) * shadow;
	g = (col / 256 % 256) * shadow;
	b = (col % 256) * shadow;
	col = r * 256 * 256 + g * 256 + b;
	return (col);
}

void			ft_sky(t_all *s)
{
	unsigned int	col;
	int				shift;
	int				i;
	int				j;

	i = 0;
	shift = (360 - s->dir.a) / 360 * 1024;
	while (i < s->win.x)
	{
		j = 0;
		if ((int)((double)i / ((s->win.y / 2) / 66)) + shift >= 1024)
			shift -= 1024;
		while (j < s->win.y / 2)
		{
			col = (int)((double)j / (s->win.y / 2) * 64) * 1024;
			col += (int)((double)i / ((s->win.y / 2) / 66)) + shift;
			s->img.adr[j * s->win.x + i] = s->tex.c[col];
			j++;
		}
		i++;
	}
}

void			ft_floor(t_all *s)
{
	double	dist;
	int		index;
	int		color;
	int		i;

	dist = ((double)s->ray.i / (s->win.y / 2)) * 26.565 + 63.435;
	dist = dist * M_PI / 180;
	dist = tan(dist) * 0.5;
	s->ray.x = s->pos.x + (s->dir.x * cos(-ANG) - s->dir.y * sin(-ANG)) * dist;
	s->ray.y = s->pos.y + (s->dir.y * cos(-ANG) + s->dir.x * sin(-ANG)) * dist;
	s->ray.v = s->pos.x + (s->dir.x * cos(ANG) - s->dir.y * sin(ANG)) * dist;
	s->ray.w = s->pos.y + (s->dir.y * cos(ANG) + s->dir.x * sin(ANG)) * dist;
	i = 0;
	while (i < s->win.x)
	{
		s->hit.x = s->ray.x + (s->ray.v - s->ray.x) * i / s->win.x;
		s->hit.y = s->ray.y + (s->ray.w - s->ray.y) * i / s->win.x;
		color = (int)(fabs(s->hit.x - floor(s->hit.x)) * 64) * 64;
		color += (int)(fabs(s->hit.y - floor(s->hit.y)) * 64);
		index = (s->win.y - s->ray.i - 1) * s->win.x + i;
		if (color >= 0 && color < 4096)
			s->img.adr[index] = ft_shadow(s, s->tex.f[color]);
		i++;
	}
	s->ray.i++;
}
