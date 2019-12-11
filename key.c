/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:31:08 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/11 18:29:08 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_window(t_all *s)
{
	mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	exit(0);
	return (1);
}

void	ft_move(t_all *s, double c)
{
	s->pos.x += c * (s->dir.x * SPEED / 100);
	s->pos.y += c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
	{
		s->pos.x -= c * (s->dir.x * SPEED / 100);
		s->pos.y -= c * (s->dir.y * SPEED / 100);
	}
	ft_screen(s);
}

void	ft_strafe(t_all *s, double c)
{
	s->pos.x -= c * (s->dir.y * SPEED / 100);
	s->pos.y += c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
	{
		s->pos.x += c * (s->dir.y * SPEED / 100);
		s->pos.y -= c * (s->dir.x * SPEED / 100);
	}
	ft_screen(s);
}

void	ft_rotate(t_all *s, double c)
{
	s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
	s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
	ft_screen(s);
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		close_window(arg);
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
	return (1);
}
