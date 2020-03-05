/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:31:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/03/05 12:50:57 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_mouse(int x, int y, t_all *s)
{
	(void)y;
	if (MOUSE && s->win.m != 10000)
		ft_rotate(s, (x - s->win.m) / 5);
	s->win.m = x;
	ft_key(s);
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
			s->hud.h += 35;
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
			s->hud.h += 35;
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

int		ft_key(t_all *s)
{
	if (s->key.e)
		ft_close(s, 1);
	if (s->key.w)
		ft_move(s, 1);
	if (s->key.a)
		ft_strafe(s, -1);
	if (s->key.s)
		ft_move(s, -1);
	if (s->key.d)
		ft_strafe(s, 1);
	if (s->key.l)
		ft_rotate(s, -1);
	if (s->key.r)
		ft_rotate(s, 1);
	if (s->key.x)
	{
		if (s->hud.f == 0)
			s->hud.f++;
	}
	ft_draw(s);
	return (1);
}
