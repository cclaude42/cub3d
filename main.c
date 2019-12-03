#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_param
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
}				t_param;

// gcc -lmlx -framework OpenGL -framework AppKit main.c && ./a.out

int	main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				bpp;
	int				sl;
	int				end = 42;
	unsigned int	*addr;
	t_param			*param;
	int				x;
	int				y;
	int				index;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 720, 480, "cub3d");
	param = malloc(sizeof(t_param) * 3);
	param->mlx_ptr = mlx_ptr;
	param->win_ptr = win_ptr;
	param->img_ptr = img_ptr;
	x = 250;
	y = 250;
	img_ptr = mlx_new_image(mlx_ptr, x, y);
	addr = (unsigned int *)mlx_get_data_addr(img_ptr, &bpp, &sl, &end);
	index = 0;
	while (index < x * y)
	{
		while (sqrt(pow(x/2 - index%y, 2) + pow(y/2 - index/y, 2)) > x/2)
			index++;
		addr[index] = mlx_get_color_value(mlx_ptr, 0x00FF00FF);
		index++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 125, 125);
	mlx_loop(mlx_ptr);
	return (0);
}
