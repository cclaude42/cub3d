/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/23 19:22:31 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_sdraw(t_all *s, int loc)
// {
// 	printf("loc %d\n", loc);
// 	while (loc < s->win.x * s->win.y)
// 	{
// 		s->img.adr[loc] = mlx_get_color_value(s->mlx.ptr, MAGENTA);
// 		loc += s->win.x;
// 	}
// }

void	ft_sdraw(t_all *s, int loc, double ver, int size)
{
	unsigned int	color;
	int				start;
	int				count;
	int				index;

	start = s->win.x * (s->win.y - size) / 2;
	if (size > s->win.y)
		count = (size - s->win.y) / 2;
	else
		count = 0;
	color = NONE;
	while (loc < s->win.x * s->win.y)
	{
		if (loc >= start && count < size)
		{
			index = 64 * floor(64 * (double)count / size);
			index += 64 * ver;
			color = s->tex.i[index];
			count++;
			//
			// ver = 0;
			// color = GREEN;
		}
		else if (count == size)
			color = NONE;
		if (color != NONE)
			s->img.adr[loc] = mlx_get_color_value(s->mlx.ptr, color);
		loc += s->win.x;
	}
}

void	ft_slocate(t_all *s, double dirx, double diry, double dist)
{
	double	diff;
	double	prev;
	int		loc;
	int		i;

	dirx = (dirx - s->pos.x) / dist;
	diry = (diry - s->pos.y) / dist;
	prev = 10;
	loc = -1;
	i = 0;
	while (i < s->win.x)
	{
		diff = fabs(dirx - s->stk[i].x) + fabs(diry - s->stk[i].y);
		if (prev > diff && diff < 0.5)
			loc = i;
		prev = diff;
		i++;
	}
	if (loc <= 0 || loc >= s->win.x - 1)
		return ;
	i = 0;
	while (i < 100)
	{
		ft_sdraw(s, loc + i - 50, (double)i / 100, 100);
		i++;
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
		ft_slocate(s, s->spr[i].x, s->spr[i].y, s->spr[i].d);
	printf("\n");
	free(s->stk);
}
