/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:20:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/17 18:08:39 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_verdoor(t_all *s, double x, double y)
{
	char	c;

	x += s->ray.v - 0.5;
	y += (s->ray.v - 0.5) * (s->ray.y / s->ray.x);
	if ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
		c = s->map.tab[(int)floor(y)][(int)floor(x)];
	else
		c = 0;
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
	if ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
		c = s->map.tab[(int)floor(y)][(int)floor(x)];
	else
		c = 0;
	if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y) || ft_is(DOOR, c))
	{
		s->hit.x = x;
		s->hit.y = y;
		s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
		s->hit.c = c;
		return ;
	}
}

int		ft_opendoor(t_all *s)
{
	int	x;
	int	y;
	int	pid;

	x = (int)floor(s->pos.x + s->dir.x);
	y = (int)floor(s->pos.y + s->dir.y);
	if (x == (int)floor(s->pos.x) && y == (int)floor(s->pos.y))
		return (0);
	if (s->map.tab[y][x] == 'D')
	{
		s->map.tab[y][x] = 'O';
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/open.mp3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		return (1);
	}
	if (s->map.tab[y][x] == 'O')
	{
		s->map.tab[y][x] = 'D';
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/close.mp3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		return (1);
	}
	return (0);
}

int		ft_secretdoor(t_all *s)
{
	int	x;
	int	y;
	int	pid;

	x = (int)floor(s->pos.x + s->dir.x);
	y = (int)floor(s->pos.y + s->dir.y);
	if (s->map.tab[y][x] == '6')
	{
		s->map.tab[y][x] = '0';
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/secret.wav -v 3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		return (1);
	}
	return (0);
}

void	ft_open(t_all *s)
{
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == 'X')
	{
		ft_free(s);
		ft_reset(s);
		s->map.f++;
		if (s->map.f == 2)
			ft_parse(s, "bonus/maps/second.cubonus");
		else if (s->map.f == 3)
			ft_parse(s, "bonus/maps/third.cubonus");
		return ;
	}
	else if (ft_secretdoor(s) == 1)
		return ;
	else if (ft_opendoor(s) == 1)
		return ;
}
