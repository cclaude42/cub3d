/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:43:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/17 17:15:09 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_lifebar(t_all *s)
{
	unsigned int	color;
	unsigned int	index;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < 72)
	{
		j = 0;
		while (j < 260)
		{
			color = s->hud.l[i / 4 * 65 + j / 4];
			index = s->win.x * (i + 20) + (j + 20);
			if (color == 2147483648)
			{
				color = (s->img.adr[index] / (256 * 256) % 256) / 2 * 256 * 256;
				color += (s->img.adr[index] / 256 % 256) / 2 * 256;
				color += (s->img.adr[index] % 256) / 2;
			}
			if (color < NONE)
				s->img.adr[index] = color;
			j++;
		}
		i++;
	}
}

void	ft_health(t_all *s)
{
	unsigned int	color;
	unsigned int	index;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < 72)
	{
		j = 0;
		while (j < 260)
		{
			color = s->hud.l[(i / 4 + 18) * 65 + j / 4];
			index = s->win.x * (i + 20) + (j + 20);
			if (color != NONE && j - 56 < (unsigned int)s->hud.h * 2)
				s->img.adr[index] = color;
			j++;
		}
		i++;
	}
}

void	ft_hudloop(t_all *s)
{
	int	loc;
	int	num;

	loc = 100;
	num = s->hud.s;
	(s->hud.h > 100) ? s->hud.h = 100 : 0;
	ft_lifebar(s);
	ft_health(s);
	ft_score(s, loc, num % 10);
	while (num > 0)
	{
		ft_score(s, loc, num % 10);
		num /= 10;
		loc += 37;
	}
	loc = 60;
	num = s->hud.a;
	while (num > 0)
	{
		ft_ammo(s, loc);
		num--;
		loc += 23;
	}
}

void	ft_hud(t_all *s)
{
	int	pid;

	if (s->hud.h <= 0)
	{
		write(1, "Game Over!\n", 11);
		ft_close(s, 1);
	}
	if (s->hud.a > 8)
		s->hud.a = 8;
	if (s->hud.f == 1 && s->hud.a > 0)
	{
		pid = fork();
		(pid == 0) ? system("afplay ./bonus/sound/pistol.mp3") : 0;
		(pid == 0) ? ft_close(s, 1) : 0;
	}
	if (s->hud.f == 11)
		ft_attack(s, s->hud.a / 1);
	if (s->hud.a > 0)
		ft_pistol(s, s->hud.f);
	else
		ft_knife(s, s->hud.f);
	s->hud.f > 0 ? s->hud.f++ : 0;
	s->hud.f == 12 && s->hud.a > 0 ? s->hud.a-- : 0;
	s->hud.f >= 18 ? s->hud.f = 0 : 0;
	ft_hudloop(s);
}

void	ft_hudparse(t_all *s)
{
	ft_xpm(s, &s->hud.l, "./bonus/textures/lifebar.xpm");
	ft_xpm(s, &s->hud.n, "./bonus/textures/numbers.xpm");
	ft_xpm(s, &s->hud.k, "./bonus/textures/knife.xpm");
	ft_xpm(s, &s->hud.p, "./bonus/textures/pistol.xpm");
	ft_xpm(s, &s->hud.b, "./bonus/textures/bullet.xpm");
	ft_xpm(s, &s->tex.k, "./bonus/textures/beer.xpm");
	ft_xpm(s, &s->tex.g, "./bonus/textures/enemy.xpm");
}
