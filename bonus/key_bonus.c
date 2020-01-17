/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:31:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/17 13:56:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_mouse(int x, int y, t_all *s)
{
	(void)y;
	if (MOUSE && s->win.m != 10000)
		ft_rotate(s, (x - s->win.m) / 5);
	s->win.m = x;
	ft_draw(s);
	return (0);
}

void	ft_move(t_all *s, double coeff)
{
	char	c;

	s->pos.x += coeff * (s->dir.x * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(WALL, c) || ft_is(DECOR, c) || ft_is(DOOR, c))
		s->pos.x -= coeff * (s->dir.x * SPEED / 100);
	s->pos.y += coeff * (s->dir.y * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(WALL, c) || ft_is(DECOR, c) || ft_is(DOOR, c))
		s->pos.y -= coeff * (s->dir.y * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(PICK, c))
	{
		if (c == '7')
			s->hud.h += 50;
		else if (c == '8')
			s->hud.s += 1000;
		else if (c == '-')
			s->hud.a += 3;
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.spr--;
		ft_slist(s);
	}
}

void	ft_strafe(t_all *s, double coeff)
{
	char	c;

	s->pos.x -= coeff * (s->dir.y * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(WALL, c) || ft_is(DECOR, c) || ft_is(DOOR, c))
		s->pos.x += coeff * (s->dir.y * SPEED / 100);
	s->pos.y += coeff * (s->dir.x * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(WALL, c) || ft_is(DECOR, c) || ft_is(DOOR, c))
		s->pos.y -= coeff * (s->dir.x * SPEED / 100);
	c = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (ft_is(PICK, c))
	{
		if (c == '7')
			s->hud.h += 50;
		else if (c == '8')
			s->hud.s += 1000;
		else if (c == '-')
			s->hud.a += 3;
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.spr--;
		ft_slist(s);
	}
}

void	ft_rotate(t_all *s, double c)
{
	double	dist;

	s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
	s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
	dist = hypot(s->dir.x, s->dir.y);
	s->dir.x /= dist;
	s->dir.y /= dist;
	dist = hypot(s->dir.x, s->dir.y);
	if (s->dir.y <= 0)
		s->dir.a = acos(s->dir.x / dist) * 180 / M_PI;
	else
		s->dir.a = 360 - acos(s->dir.x / dist) * 180 / M_PI;
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		ft_close(arg, 1);
	else if (key == W)
		ft_move(arg, 1);
	else if (key == A)
		ft_strafe(arg, -1);
	else if (key == S)
		ft_move(arg, -1);
	else if (key == D)
		ft_strafe(arg, 1);
	else if (key == LEFT)
		ft_rotate(arg, -1);
	else if (key == RIGHT)
		ft_rotate(arg, 1);
	else if (key == UP)
		ft_open(arg);
	else if (key == SPACE)
		ft_action(arg);
	ft_draw(arg);
	return (1);
}
