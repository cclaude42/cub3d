/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:31:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/11 18:09:54 by cclaude          ###   ########.fr       */
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

void	ft_move(t_all *s, double c)
{
	s->pos.x += c * (s->dir.x * SPEED / 100);
	if (ft_is(WALL, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]) ||
	ft_is(DECOR, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
		s->pos.x -= c * (s->dir.x * SPEED / 100);
	s->pos.y += c * (s->dir.y * SPEED / 100);
	if (ft_is(WALL, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]) ||
	ft_is(DECOR, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
		s->pos.y -= c * (s->dir.y * SPEED / 100);
	if (ft_is(PICK, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
	{
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.spr--;
		s->hud.s += 1000;
		ft_slist(s);
	}
}

void	ft_strafe(t_all *s, double c)
{
	s->pos.x -= c * (s->dir.y * SPEED / 100);
	if (ft_is(WALL, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]) ||
	ft_is(DECOR, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
		s->pos.x += c * (s->dir.y * SPEED / 100);
	s->pos.y += c * (s->dir.x * SPEED / 100);
	if (ft_is(WALL, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]) ||
	ft_is(DECOR, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
		s->pos.y -= c * (s->dir.x * SPEED / 100);
	if (ft_is(PICK, s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)]))
	{
		s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
		s->map.spr--;
		s->hud.s += 1000;
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
	else if (key == SPACE)
		ft_action(arg);
	ft_draw(arg);
	return (1);
}
