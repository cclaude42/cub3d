/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:43:00 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/07 18:16:40 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_lifebar(t_all *s)
{
	unsigned int	color;
	int				i;
	int				j;

	i = 0;
	while (i < 72)
	{
		j = 0;
		while (j < 256)
		{
			color = s->hud.l[i / 4 * 64 + j / 4];
			if (color != NONE)
				s->img.adr[s->win.x * (i + 20) + (j + 20)] = color;
			j++;
		}
		i++;
	}
}

void	ft_hud(t_all *s)
{
	ft_lifebar(s);
}

void	ft_hudparse(t_all *s)
{
	ft_xpm(s, &s->hud.l, "./textures/lifebar.xpm");
	ft_xpm(s, &s->hud.s, "./textures/numbers.xpm")
}
