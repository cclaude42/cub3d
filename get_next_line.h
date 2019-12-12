/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:56:13 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/25 16:51:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
char	*error(char *stock);
int		newline_check(char *stock, int read_size);
char	*buf_join(char *stock, char *buf);
char	*stock_trim(char *stock);
char	*get_line(char *stock);
#endif
