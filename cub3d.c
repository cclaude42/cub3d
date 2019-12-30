/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/30 18:14:38 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	s->ray = ray;
	s->hit = hit;
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

void	ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;
	t_dir	dir;
	t_spr	*spr;
	t_stk	*stk;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	spr = NULL;
	stk = NULL;
	s.pos = pos;
	s.dir = dir;
	s.spr = spr;
	s.mlx.ptr = mlx_init();
	ft_parse(&s, cub);
	if (bmp == 1)
		return (ft_bitmap(&s));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_map	map;
	t_tex	tex;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	tex.c = 0;
	tex.f = 0;
	s.map = map;
	s.tex = tex;
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	win.x = 0;
	win.y = 0;
	img.fsh = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	ft_declare(s, cub, bmp);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_savecheck(av[2], "--save"))
		ft_init(av[1], 1);
	else if (ac == 2)
		ft_init(av[1], 0);
	else
		printf("invalid arg num\n");
	return (0);
}
