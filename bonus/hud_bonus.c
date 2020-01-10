/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:43:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/10 17:36:08 by cclaude          ###   ########.fr       */
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
			if (color != NONE && j - 56 < s->hud.h * 2)
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
		ft_ammo(s, loc, num);
		num--;
		loc += 23;
	}
}

void	ft_hud(t_all *s)
{
	if (s->hud.a > 0)
		ft_pistol(s, s->hud.f);
	else
		ft_knife(s, s->hud.f);
	s->hud.f > 0 ? s->hud.f++ : 0;
	s->hud.f >= 20 && s->hud.a > 0 ? s->hud.a-- : 0;
	s->hud.f >= 20 ? s->hud.f = 0 : 0;
	ft_hudloop(s);
}

void	ft_hudparse(t_all *s)
{
	ft_xpm(s, &s->hud.l, "./textures/lifebar.xpm");
	ft_xpm(s, &s->hud.n, "./textures/numbers.xpm");
	ft_xpm(s, &s->hud.k, "./textures/knife.xpm");
	ft_xpm(s, &s->hud.p, "./textures/pistol.xpm");
	ft_xpm(s, &s->hud.b, "./textures/bullet.xpm");
}
