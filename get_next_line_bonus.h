/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimao-g <tsimao-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:38:02 by tsimao-g          #+#    #+#             */
/*   Updated: 2026/01/15 15:40:16 by tsimao-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>

char	*get_next_line(int fd);

char	*read_line(int fd, char *text);
char	*ft_get_line(char *text);
char	*clean_line(char *text);

char	*join_and_free(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(unsigned int count, unsigned int size);

#endif