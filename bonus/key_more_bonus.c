/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_more_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:09:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/10 19:49:13 by cclaude          ###   ########.fr       */
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

void	ft_reset(t_all *s)
{
	s->map.tab = NULL;
	s->tex.n = NULL;
	s->tex.s = NULL;
	s->tex.e = NULL;
	s->tex.w = NULL;
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

void	ft_level(t_all *s)
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
	free(s->tex.f);
	free(s->tex.c);
	free(s->tex.i);
	free(s->tex.j);
	ft_reset(s);
	ft_parse(s, "maps/second.cubonus");
}

void	ft_action(t_all *s)
{
	if (s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == 'X')
		ft_level(s);
	else if (s->hud.f == 0)
		s->hud.f++;
}
