/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_row_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:34:47 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/06 22:26:35 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_sky(t_all *s)
{
	unsigned int	col;
	int				shift;
	int				i;
	int				j;

	i = 0;
	shift = (360 - s->dir.a) / 360 * 1024;
	while (i < s->win.x)
	{
		j = 0;
		if ((int)((double)i / ((s->win.y / 2) / 66)) + shift >= 1024)
			shift -= 1024;
		while (j < s->win.y / 2)
		{
			col = (int)((double)j / (s->win.y / 2) * 64) * 1024;
			col += (int)((double)i / ((s->win.y / 2) / 66)) + shift;
			s->img.adr[j * s->win.x + i] = s->tex.f[col];
			j++;
		}
		i++;
	}
}

// void	ft_sky(t_all *s)
// {
// 	int				index;
// 	int				i;
// 	int				j;
//
// 	i = 0;
// 	index = 0;
// 	while (i < 360)
// 	{
// 		j = 0;
// 		while (j < 1080)
// 		{
// 			s->img.adr[index] = WHITE;
// 			index++;
// 			j++;
// 		}
// 		i++;
// 	}
// }
