/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:38:47 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/30 19:26:21 by cclaude          ###   ########.fr       */
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
	while (i < s->win.x * s->win.y)
	{
		write(fd, "00 FF 00 00 ", 12);
		i++;
	}
}

void	ft_bheader(t_all *s, int fd)
{
	// s->pos.x = 1;
	write(fd, "42 4D ", 6);
	ft_putbyte(s->win.x * s->win.y * 4 + 54, fd);
	// ft_putbyte(154, fd);
	write(fd, "00 00 00 00 36 00 00 00 28 00 00 00 ", 36);
	ft_putbyte(s->win.x, fd);
	ft_putbyte(s->win.y, fd);
	// ft_putbyte(5, fd);
	// ft_putbyte(5, fd);
	write(fd, "01 00 20 00 00 00 00 00 00 00 00 00 00 00 00 00 ", 48);
	write(fd, "00 00 00 00 00 00 00 00 00 00 00 00 ", 36);
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
	fd = open("screenshot.bmp", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	ft_bheader(s, fd);
	ft_bdata(s, fd);
	close(fd);
	free(s->img.ptr);
	free(s->img.adr);
	printf("success\n");
}
