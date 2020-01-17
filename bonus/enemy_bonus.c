/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:18:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/17 14:46:21 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_hit(t_all *s, char *c, int x, int y)
{
	if (s->map.tab[y][x] == '+')
		s->map.tab[y][x] = '#';
	else if (s->map.tab[y][x] == '#')
		s->map.tab[y][x] = '&';
	else if (s->map.tab[y][x] == '&')
		s->map.tab[y][x] = '$';
	else if (s->map.tab[y][x] == '$')
		s->map.tab[y][x] = '*';
	else if (s->map.tab[y][x] == '*')
	{
		s->map.tab[y][x] = '-';
		s->hud.s += 500;
	}
	*c = s->map.tab[y][x];
}

void	ft_attack(t_all *s, int weapon)
{
	int	i;
	int	pid;

	i = s->map.spr - 1;
	while (i >= 0)
	{
		if (ft_is(ENEMY, s->spr[i].c) && s->spr[i].a > 28 && s->spr[i].a < 38)
		{
			if (weapon == 0 && s->spr[i].d > 1)
				break ;
			if (s->spr[i].d > s->stk[540].d)
				break ;
			pid = fork();
			(pid == 0) ? system("afplay ./bonus/sound/death.wav -v 4") : 0;
			(pid == 0) ? ft_close(s, 1) : 0;
			ft_hit(s, &s->spr[i].c, floor(s->spr[i].x), floor(s->spr[i].y));
			ft_hit(s, &s->spr[i].c, floor(s->spr[i].x), floor(s->spr[i].y));
			break ;
		}
		i--;
	}
}
