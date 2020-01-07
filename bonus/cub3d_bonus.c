/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/07 17:31:56 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_draw(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	hit.c = 0;
	s->ray = ray;
	s->hit = hit;
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int		ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;
	t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	s.pos = pos;
	s.dir = dir;
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	ft_hudparse(&s);
	if (bmp == 1)
		return (ft_bitmap(&s));
	ft_rotate(&s, 2);
	ft_rotate(&s, -2);
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_map	map;
	t_spr	*spr;
	t_stk	*stk;
	t_hud	hud;
	t_err	err;

	hud.l = NULL;
	hud.k = NULL;
	hud.g = NULL;
	hud.s = NULL;
	map.tab = NULL;
	spr = NULL;
	stk = NULL;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	s.map = map;
	s.spr = spr;
	s.stk = stk;
	s.hud = hud;
	s.err = err;
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_tex	tex;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	tex.c = NULL;
	tex.f = NULL;
	win.x = 0;
	win.y = 0;
	img.fsh = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.tex = tex;
	ft_declare(s, cub, bmp);
}

int		main(void)
{
	ft_init("maps/first.cub", 0);
	return (0);
}
