/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/23 14:30:04 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sdraw(t_all *s, int n)
{
	int		i;

	i = 0;
	printf("X diff : %f\n", s->pos.x - s->spr[n].x);
	printf("Y diff : %f\n", s->pos.y - s->spr[n].y);
	printf("X divided : %f\n", (s->pos.x - s->spr[n].x) / s->spr[n].d);
	printf("Y divided : %f\n", (s->pos.y - s->spr[n].y) / s->spr[n].d);
}

void	ft_sorder(t_all *s)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < s->map.spr - 1)
	{
		j = i + 1;
		while (j < s->map.spr)
		{
			if (s->spr[i].d < s->spr[j].d)
			{
				tmp = s->spr[i];
				s->spr[i] = s->spr[j];
				s->spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_slist(t_all *s)
{
	int		i;
	int		j;
	int		k;

	s->spr = malloc(sizeof(t_spr) * s->map.spr);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				s->spr[i].y = (double)j + 0.5;
				s->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
}

void	ft_sprite(t_all *s)
{
	int	i;

	i = -1;
	while (++i < s->map.spr)
		s->spr[i].d = hypot(s->spr[i].x - s->pos.x, s->spr[i].y - s->pos.y);
	ft_sorder(s);
	i = -1;
	while (++i < s->map.spr)
		ft_sdraw(s, i);
	printf("\n");
	free(s->stk);
}
