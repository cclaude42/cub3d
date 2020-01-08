/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:09:58 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/08 18:41:33 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_mouse(int x, int y, t_all *s)
{
	(void)y;
	printf("%d\n", x - s->win.m);
	printf("%d\n", s->win.m);
	if (MOUSE && s->win.m != 10000)
		ft_rotate(s, 1, (x - s->win.m) / 5);
	s->win.m = x;
	return (0);
}
