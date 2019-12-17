/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/17 19:47:49 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sorder(t_all *s, t_spr **tab)
{
	t_spr	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < s->map.spr)
		tab[i]->d = hypot(tab[i]->x - s->pos.x, tab[i]->y - s->pos.y);
	i = 0;
	while (i < s->map.spr - 1)
	{
		j = i + 1;
		while (j < s->map.spr)
		{
			if (tab[i]->d > tab[j]->d)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_spr	*ft_slist(t_all *s)
{
	int		i;
	int		j;
	int		k;
	t_spr	*tab;

	tab = malloc(sizeof(t_spr) * s->map.spr);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				tab[i].y = (double)j + 0.5;
				tab[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	// ft_sorder(s, &tab);
	return (tab);
}

void	ft_sprite(t_all *s)
{
	t_spr	*tab;

	tab = ft_slist(s);
}
