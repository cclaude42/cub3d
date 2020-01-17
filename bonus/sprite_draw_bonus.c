/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/17 12:35:42 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	ft_spixel(t_all *s, int index, unsigned int col)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (col >= NONE)
		return (s->img.adr[index]);
	else if (col < 256 * 256 * 256)
		return (ft_shadow(s, col));
	t = col / (256 * 256 * 256);
	r = (col / (256 * 256) % 256) * (1 - (double)t / 256);
	g = (col / 256 % 256) * (1 - (double)t / 256);
	b = (col % 256) * (1 - (double)t / 256);
	r += (s->img.adr[index] / (256 * 256) % 256) * ((double)t / 256);
	g += (s->img.adr[index] / 256 % 256) * ((double)t / 256);
	b += (s->img.adr[index] % 256) * ((double)t / 256);
	col = r * 256 * 256 + g * 256 + b;
	return (ft_shadow(s, col));
}

void			ft_idraw(t_all *s, int loc, double dist)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	size = s->win.y / dist / 2;
	loc = loc - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((loc + i >= 0 && loc + i < s->win.x) &&
				(j < size && s->stk[loc + i].d > dist))
		{
			col = 64 * floor(64 * (double)j / size) + (double)i / size * 64;
			col = s->tex.i[col];
			index = loc + i + (s->win.y / 2 + j) * s->win.x;
			if (index < s->win.x * s->win.y)
				s->img.adr[index] = ft_spixel(s, index, col);
			j++;
		}
		i++;
	}
}

void			ft_ddraw(t_all *s, int loc, double dist)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	size = s->win.y / dist;
	loc = loc - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((loc + i >= 0 && loc + i < s->win.x) &&
				(j < size && s->stk[loc + i].d > dist))
		{
			col = 64 * floor(64 * (double)j / size) + (double)i / size * 64;
			col = s->tex.j[col];
			index = loc + i + (s->win.y / 2 - (int)size / 2 + j) * s->win.x;
			if (index < s->win.x * s->win.y)
				s->img.adr[index] = ft_spixel(s, index, col);
			j++;
		}
		i++;
	}
}

void			ft_ldraw(t_all *s, int loc, double dist)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	size = s->win.y / dist / 2;
	loc = loc - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((loc + i >= 0 && loc + i < s->win.x) &&
				(j < size && s->stk[loc + i].d > dist))
		{
			col = 128 * floor(128 * (double)j / size) + (double)i / size * 128;
			col = s->tex.k[col];
			index = loc + i + (s->win.y / 2 + j) * s->win.x;
			if (index < s->win.x * s->win.y)
				s->img.adr[index] = ft_spixel(s, index, col);
			j++;
		}
		i++;
	}
}

void			ft_edraw(t_all *s, int loc, double dist, int frame)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	size = s->win.y / dist;
	loc = loc - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((loc + i >= 0 && loc + i < s->win.x) &&
				(j < size && s->stk[loc + i].d > dist))
		{
			col = 256 * floor(64 * (double)j / size) + (double)i / size * 64;
			col = s->tex.g[col + frame * 64];
			index = loc + i + (s->win.y / 2 - (int)size / 2 + j) * s->win.x;
			if (index < s->win.x * s->win.y)
				s->img.adr[index] = ft_spixel(s, index, col);
			j++;
		}
		i++;
	}
}
