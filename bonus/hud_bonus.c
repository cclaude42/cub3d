/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:43:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/08 19:16:54 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_lifebar(t_all *s)
{
	unsigned int	color;
	int				index;
	int				i;
	int				j;

	i = 0;
	while (i < 72)
	{
		j = 0;
		while (j < 256)
		{
			color = s->hud.l[i / 4 * 64 + j / 4];
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

void	ft_score(t_all *s, int loc, int num)
{
	unsigned int	color;
	int				i;
	int				j;

	i = 0;
	while (i < 35)
	{
		j = 0;
		while (j < 40)
		{
			color = s->hud.n[i / 5 * 80 + j / 5 + num * 8];
			if (color != NONE)
				s->img.adr[s->win.x * (i + 37) + (j + s->win.x - loc)] = color;
			j++;
		}
		i++;
	}
}

void	ft_hud(t_all *s)
{
	int	loc;
	int	score;

	loc = 100;
	score = s->hud.s;
	ft_lifebar(s);
	ft_score(s, loc, score % 10);
	while (score > 0)
	{
		ft_score(s, loc, score % 10);
		score /= 10;
		loc += 37;
	}
}

void	ft_hudparse(t_all *s)
{
	ft_xpm(s, &s->hud.l, "./textures/lifebar.xpm");
	ft_xpm(s, &s->hud.n, "./textures/numbers.xpm");
}
