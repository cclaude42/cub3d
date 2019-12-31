/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 21:41:46 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/31 18:33:30 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_xpm(t_all *s, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];

	if (ft_namecheck(file, "xpm") == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		ft_texture(t_all *s, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	ft_spaceskip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	if (ft_xpm(s, adr, file) == -1)
	{
		free(file);
		return (-9);
	}
	return (0);
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

char	*ft_slab(t_all *s, char *line, int *i)
{
	char	*slab;
	int		j;

	slab = malloc(sizeof(char) * (ft_slablen(line) + 1));
	j = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			slab[j++] = line[*i];
		else if (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W')
			slab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			slab[j++] = line[*i];
			s->map.spr++;
		}
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
	tmp[s->map.y] = ft_slab(s, line, i);
	tmp[s->map.y + 1] = NULL;
	if (s->map.y > 0)
		free(s->map.tab);
	s->map.tab = tmp;
	s->map.x = ft_slablen(line);
	s->map.y++;
}
