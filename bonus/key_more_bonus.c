/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_more_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:09:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/09 17:24:32 by cclaude          ###   ########.fr       */
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

void	ft_action(t_all *s)
{
	s->hud.f++;
	if (s->hud.f >= 4)
		s->hud.f = 0;
}
