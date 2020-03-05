/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2020/03/05 12:37:45 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_draw(t_all *s)
{
	if (ft_endflag(s))
		ft_close(s, 1);
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
	return (0);
}

int		ft_cubed(t_all s, char *cub, int bmp)
{
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	ft_hudparse(&s);
	if (bmp == 1)
		return (ft_bitmap(&s));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");\
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_press, &s);
	mlx_hook(s.win.ptr, 3, 0, ft_release, &s);
	mlx_hook(s.win.ptr, 6, 0, ft_mouse, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop_hook(s.mlx.ptr, ft_key, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_spr	*spr;
	t_stk	*stk;
	t_key	key;
	t_ray	ray;
	t_hit	hit;

	ft_bzero(&spr, sizeof(spr));
	ft_bzero(&stk, sizeof(stk));
	ft_bzero(&key, sizeof(key));
	ft_bzero(&ray, sizeof(ray));
	ft_bzero(&hit, sizeof(hit));
	s.spr = spr;
	s.stk = stk;
	s.key = key;
	s.ray = ray;
	s.hit = hit;
	ft_cubed(s, cub, bmp);
}

void	ft_init(t_all s, char *cub, int bmp)
{
	t_tex	tex;
	t_hud	hud;
	t_err	err;
	t_pos	pos;
	t_dir	dir;

	ft_bzero(&tex, sizeof(tex));
	ft_bzero(&hud, sizeof(hud));
	ft_bzero(&err, sizeof(err));
	ft_bzero(&pos, sizeof(pos));
	ft_bzero(&dir, sizeof(dir));
	hud.h = 100;
	hud.a = 5;
	s.tex = tex;
	s.hud = hud;
	s.err = err;
	s.pos = pos;
	s.dir = dir;
	ft_declare(s, cub, bmp);
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_map	map;

	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&win, sizeof(win));
	ft_bzero(&img, sizeof(img));
	ft_bzero(&map, sizeof(map));
	mlx.pid = -1;
	win.m = 10000;
	map.f = 1;
	mlx.pid = fork();
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.map = map;
	(mlx.pid == 0) ? system("afplay ./bonus/sound/music.mp3") : 0;
	(mlx.pid != 0) ? ft_init(s, "bonus/maps/first.cubonus", 0) : 0;
	return (0);
}
