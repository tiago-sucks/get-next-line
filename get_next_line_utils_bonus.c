/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimao-g <tsimao-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:57:25 by tsimao-g          #+#    #+#             */
/*   Updated: 2026/01/15 15:36:05 by tsimao-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *text)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	if (!text)
		text = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(text), free(buffer), NULL);
		buffer[bytes_read] = 0;
		text = join_and_free(text, buffer);
		tmp = text;
		while (*tmp && *tmp != '\n')
			tmp++;
		if (*tmp == '\n')
			break ;
	}
	return (free(buffer), text);
}

char	*ft_get_line(char *text)
{
	int		i;
	char	*str;

	i = 0;
	if (!text[i])
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		str[i] = text[i];
		i++;
	}
	if (text[i] && text[i] == '\n')
		str[i++] = '\n';
	return (str);
}

char	*clean_line(char *text)
{
	int		i;
	int		j;
	int		n;
	char	*str;

	i = 0;
	j = 0;
	n = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
		return (free (text), NULL);
	while (text[n])
		n++;
	str = ft_calloc((n - i + 1), sizeof(*text));
	if (!str)
		return (NULL);
	while (text[++i])
		str[j++] = text[i];
	str[j] = '\0';
	return (free (text), str);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*start;
	char	*str;
	char	*temp;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = 0;
	temp = s1;
	while (*temp++)
		len++;
	temp = s2;
	while (*temp++)
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	temp = s1;
	while (*temp)
		*str++ = *temp++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (free(s1), start);
}

void	*ft_calloc(unsigned int count, unsigned int size)
{
	unsigned char	*pointer;
	unsigned char	*temp;
	unsigned int	total;

	if (count == 0 || size == 0)
		return (malloc(1));
	if (count > (unsigned int)-1 / size)
		return (NULL);
	total = count * size;
	pointer = malloc(total);
	if (!pointer)
		return (NULL);
	temp = pointer;
	while (total--)
		*temp++ = '\0';
	return (pointer);
}
