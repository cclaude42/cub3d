#include "cub3d.h"

// gcc -lmlx -framework OpenGL -framework AppKit main.c && ./a.out

void	ft_column(t_all *s, int index, int size)
{
	while (index < s->win.x * s->win.y / 2 - size * s->win.x)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, SKY);
		index += s->win.x;
	}
	while (index < s->win.x * s->win.y / 2 + size * s->win.x)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, WALL);
		index += s->win.x;
	}
	while (index < s->win.x * s->win.y)
	{
		s->img.adr[index] = mlx_get_color_value(s->mlx.ptr, DIRT);
		index += s->win.x;
	}
}

void	ft_wall(t_all s)
{
	int		index;
	int		size;

	index = 0;
	size = 40;
	s.img.adr = (unsigned int *)mlx_get_data_addr(s.img.ptr, &s.img.bpp, &s.img.sl, &s.img.end);
	while (index < s.win.x)
	{
		ft_column(&s, index, size);
		index++;
	}
	mlx_put_image_to_window(s.mlx.ptr, s.win.ptr, s.img.ptr, 0, 0);
}

void	close_window(t_all *s)
{
	mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	exit(0);
}

int		deal_key(int key, void *arg)
{
	if (key == 53)
		close_window(arg);
	return (1);
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.mlx.ptr = mlx_init();
	s.win.x = 720;
	s.win.y = 480;
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3d");
	s.img.ptr = mlx_new_image(s.mlx.ptr, s.win.x, s.win.y);
	ft_wall(s);
	mlx_key_hook(s.win.ptr, deal_key, &s);
	mlx_loop(s.mlx.ptr);
	return (0);
}
