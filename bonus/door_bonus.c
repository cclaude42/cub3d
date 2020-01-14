/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:20:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/14 15:11:14 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_verdoor(t_all *s, double x, double y)
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

void	ft_hordoor(t_all *s, double x, double y)
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

void	ft_posdoor(t_all *s, int *x, int *y)
{
	(void)s;
	*x = 1;
	*y = 0;
}

int		ft_opendoor(t_all *s)
{
	int	x;
	int	y;
	int	pid;

	ft_posdoor(s, &x, &y);
	if (s->map.tab[(int)floor(s->pos.y) + y][(int)floor(s->pos.x) + x] == 'D')
	{
		s->map.tab[(int)floor(s->pos.y) + y][(int)floor(s->pos.x) + x] = 'O';
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/pistol.mp3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		return (1);
	}
	if (s->map.tab[(int)floor(s->pos.y) + y][(int)floor(s->pos.x) + x] == 'O')
	{
		s->map.tab[(int)floor(s->pos.y) + y][(int)floor(s->pos.x) + x] = 'D';
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/pistol.mp3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		return (1);
	}
	return (0);
}
