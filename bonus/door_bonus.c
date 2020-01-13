/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:20:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/13 19:10:00 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_vdoor(t_all *s, double x, double y)
{
	char	c;

	x += s->ray.v - 0.5;
	y += (s->ray.v - 0.5) * (s->ray.y / s->ray.x);
	c = s->map.tab[(int)floor(y)][(int)floor(x)];
	if (ft_is(DOOR, c))
	{
		s->hit.x = x;
		s->hit.y = y;
		s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
		s->hit.c = c;
		return ;
	}
	s->hit.x = s->pos.x;
	s->hit.y = s->pos.y;
	s->hit.d = 1000000000;
	s->hit.c = 0;
}

void	ft_hdoor(t_all *s, double x, double y)
{
	char	c;

	y += s->ray.w - 0.5;
	x += (s->ray.w - 0.5) * (s->ray.x / s->ray.y);
	c = s->map.tab[(int)floor(y)][(int)floor(x)];
	if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y) || ft_is(DOOR, c))
	{
		s->hit.x = x;
		s->hit.y = y;
		s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
		s->hit.c = c;
		return ;
	}
}
