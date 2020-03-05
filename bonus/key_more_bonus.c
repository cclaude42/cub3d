/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_more_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:09:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/03/05 12:49:34 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_reset(t_all *s)
{
	s->map.tab = NULL;
	s->tex.n = NULL;
	s->tex.s = NULL;
	s->tex.e = NULL;
	s->tex.w = NULL;
	s->tex.d = NULL;
	s->tex.x = NULL;
	s->tex.f = NULL;
	s->tex.c = NULL;
	s->tex.i = NULL;
	s->tex.j = NULL;
	s->win.x = 0;
	s->win.y = 0;
	s->map.x = 0;
	s->map.y = 0;
	s->map.spr = 0;
	s->err.m = 0;
	s->err.n = 0;
	s->err.p = 0;
}

void	ft_free(t_all *s)
{
	int	i;

	i = 0;
	while (i < s->map.y)
		free(s->map.tab[i++]);
	free(s->map.tab);
	free(s->spr);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	free(s->tex.d);
	free(s->tex.x);
	free(s->tex.f);
	free(s->tex.c);
	free(s->tex.i);
	free(s->tex.j);
}

int		ft_close(t_all *s, int win)
{
	ft_free(s);
	free(s->hud.l);
	free(s->hud.n);
	free(s->hud.k);
	free(s->hud.p);
	free(s->hud.b);
	free(s->tex.k);
	free(s->tex.g);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	kill(s->mlx.pid + 1, SIGTERM);
	exit(0);
	return (1);
}

int		ft_set(t_all *s, int key, int set)
{
	if (key == ESC)
		s->key.e = set;
	else if (key == W)
		s->key.w = set;
	else if (key == A)
		s->key.a = set;
	else if (key == S)
		s->key.s = set;
	else if (key == D)
		s->key.d = set;
	else if (key == LEFT)
		s->key.l = set;
	else if (key == RIGHT)
		s->key.r = set;
	else if (key == SHIFT && set)
		ft_open(s);
	else if (key == SPACE)
		s->key.x = set;
	return (1);
}

int		ft_press(int key, void *arg)
{
	ft_set(arg, key, 1);
	return (1);
}

int		ft_release(int key, void *arg)
{
	ft_set(arg, key, 0);
	return (1);
}
