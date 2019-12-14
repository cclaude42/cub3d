/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/14 11:11:39 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_texture(&s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_texture(&s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		ft_texture(&s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		ft_texture(&s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		ft_texture(&s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_colors(&s->tex.c, line, &i);
	else if (line[i] == '1' && line[i + 1] == ' ')
		ft_map(s, line, &i);
}

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0)
		return (-1);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-1);
		buf[read_size] = '\0';
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-1);
	}
	if ((*line = get_line(stock)) == NULL)
		return (-1);
	if (read_size == 0)
		free(stock);
	if (read_size == 0)
		return (0);
	if ((stock = stock_trim(stock)) == NULL)
		return (-1);
	return (1);
}

void	ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	s->map.x = 0;
	s->map.y = 0;
	fd = open(cub, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_line(s, line);
		free(line);
	}
	free(line);
	close(fd);
	ft_pos(s);

	int	i = 0;
	printf("\n");
	printf("Resolution : %dx%d\n\n", s->win.x, s->win.y);
	printf("Floor color : #%X\n\n", s->tex.f);
	printf("Ceiling color #%X\n\n", s->tex.c);
	printf("Map size : %d by %d\n\n", s->map.x, s->map.y);
	while (i < s->map.y)
		printf("%s\n", s->map.tab[i]);
	printf("\n");
}

// int		main(int ac, char **av)
// {
// 	t_all	s;
// 	t_mlx	mlx;
// 	t_win	win;
// 	t_img	img;
// 	t_tex	tex;
// 	t_map	map;
// 	t_pos	pos;
// 	t_dir	dir;
//
// 	s.mlx = mlx;
// 	s.win = win;
// 	s.img = img;
// 	s.tex = tex;
// 	s.map = map;
// 	s.pos = pos;
// 	s.dir = dir;
// 	(void)ac;
// 	// s.mlx.ptr = mlx_init();
// 	ft_parse(&s, av[1]);
// 	return (0);
// }
