/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:37:22 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/12 18:24:27 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_color(t_all *s)
{
	if (floor(s->hit.x) == s->hit.x && floor(s->hit.y) == s->hit.y)
	{
		if (s->ray.x == 0)
			return (s->ray.y == 1 ? SOUTH : NORTH);
		if (s->ray.y == 0)
			return (s->ray.x == 1 ? EAST : WEST);
	}
	else if (floor(s->hit.x) == s->hit.x)
		return (s->ray.v == 1 ? EAST : WEST);
	else if (floor(s->hit.y) == s->hit.y)
		return (s->ray.w == 1 ? SOUTH : NORTH);
	return (BLACK);
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

void	ft_column(t_all *s, int size)
{
	int	color;
	int	start;
	int	end;

	color = s->tex.c;
	start = s->win.x * (s->win.y - size) / 2;
	end = s->win.x * (s->win.y + size) / 2;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i >= start && s->ray.i <= end)
			color = ft_color(s);
		if (s->ray.i = end + 1)
			color = s->tex.f;
		s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color);
		s->ray.i += s->win.x;
	}
	s->ray.i -= s->win.x * s->win.y;
}
