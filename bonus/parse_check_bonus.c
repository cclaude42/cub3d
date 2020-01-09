/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:16:06 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/09 15:10:05 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_savecheck(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_namecheck(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (ft_is(WALL, s->map.tab[i][j]) == 0 && i == 0)
				return (-1);
			else if (ft_is(WALL, s->map.tab[i][j]) == 0 && i == s->map.y - 1)
				return (-1);
			else if (ft_is(WALL, s->map.tab[i][j]) == 0 && j == 0)
				return (-1);
			else if (ft_is(WALL, s->map.tab[i][j]) == 0 && j == s->map.x - 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	ft_rotate(s, 1);
	ft_move(s, 1);
	ft_rotate(s, -1);
	ft_move(s, -1);
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NULL || s->tex.f == NULL)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}
