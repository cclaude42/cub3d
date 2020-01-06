/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_row_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:34:47 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/06 23:40:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_sky(t_all *s)
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

void	ft_floor(t_all *s)
{
	double	ang;
	double	dist;
	int		index;
	int		i;

	dist = ((double)s->ray.i / (s->win.y / 2)) * 26.565 + 63.435;
	dist = dist * M_PI / 180;
	dist = tan(dist) * 0.5;
	ang = 33 * M_PI / 180;
	s->ray.x = s->pos.x + (s->dir.x * cos(-ang) - s->dir.y * sin(-ang)) * dist;
	s->ray.y = s->pos.y + (s->dir.y * cos(-ang) + s->dir.x * sin(-ang)) * dist;
	s->ray.v = s->pos.x + (s->dir.x * cos(ang) - s->dir.y * sin(ang)) * dist;
	s->ray.w = s->pos.y + (s->dir.y * cos(ang) + s->dir.x * sin(ang)) * dist;
	i = 0;
	while (i < s->win.x)
	{
		s->hit.x = s->ray.x + (s->ray.v - s->ray.x) * s->win.x / i;
		s->hit.y = s->ray.y + (s->ray.w - s->ray.y) * s->win.x / i;
		printf("%f %f\n", s->hit.x, s->hit.y);
		index = (int)(fabs(s->hit.x - floor(s->hit.x)) * 64) * 64;
		// printf("X : %d\n", (int)(fabs(s->hit.x - floor(s->hit.x)) * 64));
		index += (int)(fabs(s->hit.y - floor(s->hit.y)) * 64);
		// printf("Y : %d\n", (int)(fabs(s->hit.y - floor(s->hit.y)) * 64));
		if (index >= 0 && index < 4096)
			s->img.adr[s->ray.i * s->win.x + i] = s->tex.f[index];
		i++;
	}
	s->ray.i--;
}
