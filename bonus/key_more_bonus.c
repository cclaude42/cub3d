/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_more_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:09:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/14 15:03:43 by cclaude          ###   ########.fr       */
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
	s->tex.k = NULL;
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
	free(s->tex.k);
}

int		ft_close(t_all *s, int win)
{
	ft_free(s);
	free(s->hud.l);
	free(s->hud.n);
	free(s->hud.k);
	free(s->hud.p);
	free(s->hud.b);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

void	ft_level(t_all *s)
{
	ft_free(s);
	ft_reset(s);
	s->map.f++;
	if (s->map.f == 2)
		ft_parse(s, "bonus/maps/second.cubonus");
	else if (s->map.f == 3)
		ft_parse(s, "bonus/maps/third.cubonus");
}

void	ft_action(t_all *s)
{
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == 'X')
		ft_level(s);
	else if (ft_opendoor(s) == 1)
		return ;
	else if (s->hud.f == 0)
		s->hud.f++;
}
