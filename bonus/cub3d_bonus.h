/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:09 by cclaude           #+#    #+#             */
/*   Updated: 2020/03/05 12:52:03 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../mlxopengl/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define SPACE 49
# define SHIFT 257

# define WALL 1
# define POS 2
# define SPRITE 3
# define DECOR 4
# define PICK 5
# define DOOR 6
# define ENEMY 7

# define ANG 0.57595865315
# define SPEED 10
# define TURN 0.03
# define SHADOW 35
# define MOUSE 1

typedef struct	s_mlx
{
	void			*ptr;
	int				pid;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
	int				m;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
}				t_img;

typedef struct	s_err
{
	int				n;
	int				m;
	int				p;
}				t_err;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				spr;
	int				f;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*d;
	unsigned int	*x;
	unsigned int	*c;
	unsigned int	*f;
	unsigned int	*i;
	unsigned int	*j;
	unsigned int	*k;
	unsigned int	*g;
}				t_tex;

typedef struct	s_hud
{
	unsigned int	*l;
	unsigned int	*k;
	unsigned int	*p;
	unsigned int	*n;
	unsigned int	*b;
	unsigned int	s;
	int				h;
	unsigned int	a;
	unsigned int	f;
}				t_hud;

typedef struct	s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct	s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}				t_ray;

typedef struct	s_hit
{
	double			x;
	double			y;
	double			d;
	char			c;
}				t_hit;

typedef struct	s_key
{
	int				e;
	int				w;
	int				a;
	int				s;
	int				d;
	int				l;
	int				r;
	int				h;
	int				x;
}				t_key;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			d;
	double			a;
	char			c;
	unsigned int	v;
	unsigned int	f;
}				t_spr;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_hud			hud;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
	t_key			key;
	t_spr			*spr;
	t_stk			*stk;
}				t_all;

void			ft_init(t_all s, char *cub, int bmp);
void			ft_declare(t_all s, char *cub, int bmp);
int				ft_cubed(t_all s, char *cub, int bmp);
int				ft_draw(t_all *s);

int				ft_parse(t_all *s, char *cub);
int				get_next_line(int fd, char **line);
int				ft_line(t_all *s, char *line);

int				ft_map(t_all *s, char *line, int *i);
char			*ft_slab(t_all *s, char *line, int *i);
int				ft_slablen(t_all *s, char *line);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);
int				ft_xpm(t_all *s, unsigned int **adr, char *file);

void			ft_pos(t_all *s);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_res(t_all *s, char *line, int *i);

int				ft_parcheck(t_all *s);
int				ft_mapcheck(t_all *s);
int				ft_savecheck(char *arg, char *save);
int				ft_namecheck(char *arg, char *ext);

int				ft_key(t_all *s);
void			ft_rotate(t_all *s, double coeff);
void			ft_strafe(t_all *s, double coeff);
void			ft_move(t_all *s, double c);
int				ft_mouse(int x, int y, t_all *s);

void			ft_reset(t_all *s);
void			ft_free(t_all *s);
int				ft_close(t_all *s, int win);
int				ft_set(t_all *s, int key, int set);
int				ft_press(int key, void *arg);
int				ft_release(int key, void *arg);

void			ft_screen(t_all *s);
void			ft_ray(t_all *s);
void			ft_dir(t_all *s);
void			ft_ver(t_all *s);
void			ft_hor(t_all *s);

void			ft_verdoor(t_all *s, double x, double y);
void			ft_hordoor(t_all *s, double x, double y);
int				ft_opendoor(t_all *s);
int				ft_secretdoor(t_all *s);
void			ft_open(t_all *s);

void			ft_sky(t_all *s);
void			ft_floor(t_all *s);
unsigned int	ft_shadow(t_all *s, unsigned int col);

void			ft_stock(t_all *s);
int				ft_size(t_all *s);
void			ft_column(t_all *s, int start);
unsigned int	ft_pixel(t_all *s, double i);

void			ft_sprite(t_all *s);
int				ft_slist(t_all *s);
void			ft_sorder(t_all *s);
double			ft_slocate(t_all *s, t_spr spr);
void			ft_sdraw(t_all *s, t_spr spr);

void			ft_idraw(t_all *s, int loc, double dist);
void			ft_ddraw(t_all *s, int loc, double dist);
void			ft_ldraw(t_all *s, int loc, double dist);
void			ft_edraw(t_all *s, int loc, double dist, int frame);
unsigned int	ft_spixel(t_all *s, int index, unsigned int col);

void			ft_hudparse(t_all *s);
void			ft_hud(t_all *s);
void			ft_hudloop(t_all *s);
void			ft_lifebar(t_all *s);
void			ft_health(t_all *s);

void			ft_knife(t_all *s, int frame);
void			ft_pistol(t_all *s, int frame);
void			ft_ammo(t_all *s, int loc);
void			ft_score(t_all *s, int loc, int num);

void			ft_hit(t_all *s, char *c, int x, int y);
void			ft_attack(t_all *s, int weapon);
void			ft_seen(t_all *s, t_spr *spr);
void			ft_getshot(t_all *s, t_spr *spr);
int				ft_endflag(t_all *s);

int				ft_bitmap(t_all *s);
void			ft_bdraw(t_all *s);
void			ft_bfile(t_all *s, int fd);
void			ft_binfo(t_all *s, int fd);
void			ft_bdata(t_all *s, int fd);

char			*error(char *stock);
int				newline_check(char *stock, int read_size);
char			*buf_join(char *stock, char *buf);
char			*stock_trim(char *stock);
char			*get_line(char *stock);

void			ft_bzero(void *s, size_t n);
int				ft_atoi(char *line, int *i);
void			ft_spaceskip(char *line, int *i);
int				ft_is(int n, char c);
int				ft_strerror(int err);

#endif
