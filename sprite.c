/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/23 17:24:51 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sdraw(t_all *s, double dirx, double diry, double dist)
{
	double	diff;
	int		ret;
	int		i;

	dirx = (dirx - s->pos.x) / dist;
	diry = (diry - s->pos.y) / dist;
	diff = 10;
	ret = -1;
	i = 0;
	while(i < s->win.x)
	{
		if (diff > fabs(dirx - s->stk[i].x) + fabs(diry - s->stk[i].y))
			ret = i;
		diff = fabs(dirx - s->stk[i].x) + fabs(diry - s->stk[i].y);
		// printf("I %4d ; Diff %f\n", i, diff);
		i++;
	}
	printf("Ret : %d\n", ret);
	if (s->stk[ret].d < dist || ret == 0 || ret == s->win.x - 1)
		return ;
	while (ret < s->win.x * s->win.y)
	{
		s->img.adr[ret] = mlx_get_color_value(s->mlx.ptr, MAGENTA);
		ret += s->win.x;
	}
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
		ft_sdraw(s, s->spr[i].x, s->spr[i].y, s->spr[i].d);
	printf("\n");
	free(s->stk);
}
