/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:44:55 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/10 14:37:58 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_knife(t_all *s, int frame)
{
	unsigned int	color;
	unsigned int	index;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (frame >= 12)
		frame = 0;
	else
		frame = frame / 3;
	while (i < 96 * 4)
	{
		j = 0;
		while (j < 128 * 4)
		{
			color = s->hud.k[(i / 4 + frame * 96) * 128 + j / 4];
			index = s->win.x * (s->win.y - 96 * 4 + i);
			index += (s->win.x - 128 * 4) / 2 + j;
			if (color != NONE)
				s->img.adr[index] = color;
			j++;
		}
		i++;
	}
}

void	ft_pistol(t_all *s, int frame)
{
	unsigned int	color;
	unsigned int	index;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (frame >= 12)
		frame = 0;
	else
		frame = frame / 3;
	while (i < 96 * 4)
	{
		j = 0;
		while (j < 96 * 4)
		{
			color = s->hud.p[(i / 4 + frame * 96) * 96 + j / 4];
			index = s->win.x * (s->win.y - 96 * 4 + i);
			index += (s->win.x - 96 * 4) / 2 + j;
			if (color != NONE)
				s->img.adr[index] = color;
			j++;
		}
		i++;
	}
}
