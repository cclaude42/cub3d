#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define MAGENTA 0x00FF00FF
#define YELLOW 0x00FFFF00
#define CYAN 0x0000FFFF
#define SKY 0x00CDF9FF
#define WALL 0x00666666
#define DIRT 0x00E0AC69

typedef struct	s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}				t_param;

typedef struct	s_image
{
	unsigned int	*addr;
	int				bpp;
	int				sl;
	int				end;
}				t_image;

// gcc -lmlx -framework OpenGL -framework AppKit main.c && ./a.out

void	ft_column(t_param *param, t_image image, int index, int x, int y)
{
	while (index < (x * y / 2 - 20 * x))
	{
		image.addr[index] = mlx_get_color_value(param->mlx_ptr, SKY);
		index += x;
	}
	while (index < (x * y / 2 + 20 * x))
	{
		image.addr[index] = mlx_get_color_value(param->mlx_ptr, WALL);
		index += x;
	}
	while (index < x * y)
	{
		image.addr[index] = mlx_get_color_value(param->mlx_ptr, DIRT);
		index += x;
	}
}

void	ft_wall(t_param *param, int x, int y)
{
	t_image	image;
	int		col;

	image.addr = (unsigned int *)mlx_get_data_addr(param->img_ptr, &image.bpp, &image.sl, &image.end);
	col = 0;
	while (col < x)
	{
		ft_column(param, image, col, x, y);
		col++;
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0);
}

void	close_window(t_param *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
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
	t_param	*param;
	int		x;
	int		y;

	x = 720;
	y = 480;
	param->mlx_ptr = mlx_init();
	param->win_ptr = mlx_new_window(param->mlx_ptr, 720, 480, "cub3d");
	param->img_ptr = mlx_new_image(param->mlx_ptr, 720, 480);
	ft_wall(param, x, y);
	mlx_key_hook(param->win_ptr, deal_key, param);
	mlx_loop(param->mlx_ptr);
	return (0);
}
