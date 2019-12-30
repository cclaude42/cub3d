/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:38:47 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/30 20:18:19 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putbyte(unsigned int byte, int fd)
{
	char	*table;
	int		nb;

	table = "0123456789ABCDEF";
	nb = byte % 256;
	write(fd, &table[nb / 16], 1);
	write(fd, &table[nb % 16], 1);
	write(fd, " ", 1);
	nb = byte / 256 % 256;
	write(fd, &table[nb / 16], 1);
	write(fd, &table[nb % 16], 1);
	write(fd, " ", 1);
	nb = byte / 256 / 256 % 256;
	write(fd, &table[nb / 16], 1);
	write(fd, &table[nb % 16], 1);
	write(fd, " 00 ", 4);
}

void	ft_bdata(t_all *s, int fd)
{
	int	i;

	i = 0;
	while (i < 25)
	{
		write(fd, "\0", 1);
		write(fd, "\0", 1);
		write(fd, "\0", 1);
		write(fd, "\0", 1);
		i++;
	}
	s->pos.x = 1;
}

void	ft_bheader(t_all *s, int fd)
{
	int				i;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);

	// ft_putbyte(s->win.x * s->win.y * 4 + 54, fd);2
	header[2] = (unsigned char)(154);

	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);

	// ft_putbyte(s->win.x, fd);18
	// ft_putbyte(s->win.y, fd);22
	header[18] = (unsigned char)(5);
	header[22] = (unsigned char)(5);

	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
	s->pos.x = 1;
}

void	ft_bdraw(t_all *s)
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
}

void	ft_bitmap(t_all *s)
{
	int		fd;

	ft_bdraw(s);
	fd = open("bmp.bmp", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	ft_bheader(s, fd);
	ft_bdata(s, fd);
	close(fd);
	free(s->img.ptr);
	free(s->img.adr);
}
