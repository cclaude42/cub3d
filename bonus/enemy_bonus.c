/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:18:45 by cclaude           #+#    #+#             */
/*   Updated: 2020/03/05 12:37:03 by cclaude          ###   ########.fr       */
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
			(pid == 0) ? system("afplay ./bonus/sound/death.wav -v 2") : 0;
			(pid == 0) ? ft_close(s, 1) : 0;
			ft_hit(s, &s->spr[i].c, floor(s->spr[i].x), floor(s->spr[i].y));
			ft_hit(s, &s->spr[i].c, floor(s->spr[i].x), floor(s->spr[i].y));
			break ;
		}
		i--;
	}
}

void	ft_getshot(t_all *s, t_spr *spr)
{
	int	pid;

	if (spr->v == 10)
	{
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/achtung.wav -v 2") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
	}
	if (spr->v % 100 >= 85)
		spr->f = 2;
	else if (spr->v % 100 >= 50)
		spr->f = 1;
	else
		spr->f = 0;
	if (spr->v % 100 == 90)
	{
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/shot.wav") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
		s->hud.h -= 15;
	}
}

void	ft_seen(t_all *s, t_spr *spr)
{
	int		i;
	double	x;
	double	y;
	char	c;

	i = 1;
	x = spr->x - s->pos.x;
	y = spr->y - s->pos.y;
	while (i < 100)
	{
		s->hit.x = s->pos.x + x * i / 100;
		s->hit.y = s->pos.y + y * i / 100;
		c = s->map.tab[(int)floor(s->hit.y)][(int)floor(s->hit.x)];
		if (ft_is(WALL, c) || ft_is(DOOR, c))
		{
			spr->v = 0;
			spr->f = 0;
			return ;
		}
		i++;
	}
	spr->v++;
	ft_getshot(s, spr);
}

int		ft_endflag(t_all *s)
{
	int	i;
	int	enemy;

	i = 0;
	enemy = 0;
	while (i < s->map.spr)
	{
		if (ft_is(ENEMY, s->spr[i].c))
			enemy++;
		i++;
	}
	if (enemy > 0)
		return (0);
	if (s->map.f < 3)
		return (0);
	write(1, "Congratulations !\n", 18);
	return (1);
}
