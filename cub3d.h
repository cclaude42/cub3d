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

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
	unsigned int	index;
	int				bpp;
	int				sl;
	int				end;
}				t_img;

typedef struct	s_map
{
	int				**tab;
	int				x;
	int				y;
}				t_map;

typedef struct	s_pos
{
	int				x;
	int				y;
}				t_pos;

typedef struct	s_dir
{
	int				x;
	int				y;
}				t_dir;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_map			map;
	t_pos			pos;
	t_dir			dir;
}				t_all;
