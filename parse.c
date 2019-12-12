/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/12 22:58:49 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

int		ft_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	ft_spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

void	ft_res(t_all *s, char *line, int *i)
{
	(*i)++;
	s->win.x = ft_atoi(line, i);
	s->win.y = ft_atoi(line, i);
	ft_spaceskip(line, i);
}

unsigned int	**ft_table(void)
{
	unsigned int	**tab;

	tab = malloc(sizeof(unsigned int *) * 2);
	tab[0] = malloc(sizeof(unsigned int) * 2);
	tab[1] = malloc(sizeof(unsigned int *) * 2);
	tab[0][0] = 2;
	tab[0][1] = 3;
	tab[1][0] = 4;
	tab[1][1] = 6;
	return (tab);
}

void	ft_texture(unsigned int ***tab, char *line, int *i)
{
	*tab = ft_table();
}

void	ft_colors(unsigned int *color, char *line, int *i)
{
	(*i)++;
	*color = ft_atoi(line, i) * 256 * 256;
	(*i)++;
	*color += ft_atoi(line, i) * 256;
	(*i)++;
	*color += ft_atoi(line, i);
	ft_spaceskip(line, i);
}

int		ft_slablen(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
			count++;
		else if (line[i] == 'E')
			count++;
		i++;
	}
	return (count);
}

char	*ft_slab(char *line, int *i)
{
	char	*slab;
	char	j;

	slab = malloc(sizeof(char) * (ft_slablen(line) + 1));
	j = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == '2')
			slab[j++] = line[*i];
		else if (line[*i] == 'N' || line[*i] == 'S' || line[*i] == 'W')
			slab[j++] = line[*i];
		else if (line[*i] == 'E')
			slab[j++] = line[*i];
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

void	ft_map(t_all *s, char *line, int *i)
{
	char	**tmp;
	int		j;

	tmp = malloc(sizeof(char *) * (s->map.y + 2));
	j = 0;
	while (j < s->map.y)
	{
		tmp[j] = s->map.tab[j];
		j++;
	}
	tmp[s->map.y] = ft_slab(line, i);
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.x = ft_slablen(line);
	s->map.y++;
}

void	ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(s, line, &i);
	// else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		// ft_texture(&s->tex.n, line, &i);
	// else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.s, line, &i);
	// else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.w, line, &i);
	// else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
	// 	ft_texture(&s->tex.e, line, &i);
	// else if (line[i] == 'S' && line[i + 1] == ' ')
	// 	ft_texture(&s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_colors(&s->tex.c, line, &i);
	else if (line[i] == '1' && line[i + 1] == ' ')
		ft_map(s, line, &i);
}

void	ft_parse(t_all *s)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	s->map.x = 0;
	s->map.y = 0;
	fd = open("map.cub", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_line(s, line);
		free(line);
	}
	close(fd);

	//
	int	i = 0;
	printf("\n");
	printf("Resolution : %dx%d\n\n", s->win.x, s->win.y);
	printf("Floor color : #%X\n\n", s->tex.f);
	printf("Ceiling color #%X\n\n", s->tex.c);
	printf("Map size : %d by %d\n\n", s->map.x, s->map.y);
	while (i < s->map.y)
	{
		printf("%s\n", s->map.tab[i]);
		free(s->map.tab[i++]);
	}
	printf("\n");
	free(s->map.tab);
	//
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_tex	tex;
	t_map	map;
	t_pos	pos;
	t_dir	dir;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.tex = tex;
	s.map = map;
	s.pos = pos;
	s.dir = dir;
	ft_parse(&s);
	return (0);
}
