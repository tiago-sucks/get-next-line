/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimao-g <tsimao-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:53:53 by tsimao-g          #+#    #+#             */
/*   Updated: 2026/01/15 15:37:25 by tsimao-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*output_text;
	static char	*text[FOPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	text[fd] = read_line(fd, text[fd]);
	if (!text[fd])
		return (NULL);
	output_text = ft_get_line(text[fd]);
	text[fd] = clean_line(text[fd]);
	return (output_text);
}
