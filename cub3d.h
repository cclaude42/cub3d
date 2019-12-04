/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:09 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/04 18:47:33 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				bpp;
	int				sl;
	int				end;
}				t_img;

typedef struct	s_map
{
	int				tab[10][10];
	int				x;
	int				y;
}				t_map;

typedef struct	s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct	s_dir
{
	double			x;
	double			y;
}				t_dir;

typedef struct	s_ray
{
	int				i;
	double			x;
	double			y;
}				t_ray;

typedef struct	s_hit
{
	double			x;
	double			y;
}				t_hit;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_map			map;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
}				t_all;
