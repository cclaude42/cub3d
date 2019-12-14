/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/14 17:29:26 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_all *s, char *cub)
{
	s->mlx.ptr = mlx_init();
	ft_parse(s, cub);
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3d");
	ft_screen(s);
}

void	ft_cubed(t_all s, char *cub)
{
	t_tex	tex;
	t_map	map;
	t_pos	pos;
	t_dir	dir;

	s.tex = tex;
	s.map = map;
	s.pos = pos;
	s.dir = dir;
	ft_init(&s, cub);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
}

int		main(int ac, char **av)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	(void)ac;
	ft_cubed(s, av[1]);
	return (0);
}
