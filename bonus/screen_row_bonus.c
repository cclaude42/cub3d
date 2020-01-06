/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_row_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:34:47 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/06 21:47:56 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_sky(t_all *s)
{
	unsigned int	col;
	int				index;
	int				i;
	int				j;

	i = 0;
	while (i < s->win.x)
	{
		j = 0;
		while (j < s->win.y / 2)
		{
			col = j * 1024 + i;
			index = i + j * s->win.x;
			s->img.adr[index] = s->tex.f[col];
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
