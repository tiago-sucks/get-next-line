/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimao-g <tsimao-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:08:56 by tiago             #+#    #+#             */
/*   Updated: 2026/01/14 23:24:29 by tsimao-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	return (free(text), temp);
}

char	*read_line(int fd, char *text)
{
	char	*buffer;
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
			return (free (text), free (buffer), NULL);
		buffer[bytes_read] = 0;
		text = join_and_free(text, buffer);
		if (ft_strchr(text, '\n'))
			break ;
	}
	return (free (buffer), text);
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
	char	*str;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
		return (free (text), NULL);
	str = ft_calloc((ft_strlen(text) - i + 1), sizeof(*text));
	if (!str)
		return (NULL);
	while (text[++i])
		str[j++] = text[i];
	str[j] = '\0';
	return (free (text), str);
}

char	*get_next_line(int fd)
{
	char		*output_text;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = read_line(fd, text);
	if (!text)
		return (NULL);
	output_text = ft_get_line(text);
	text = clean_line(text);
	return (output_text);
}

// int	main(void)
// {
//     int		fd;
//     char	*line;

//     // test with a normal file
//     fd = open("teste.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Error opening file\n");
//         return (1);
//     }
//     printf("Reading teste.txt\n");
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);

//     // test with empty file
//     printf("\nReading empty.txt\n");
//     fd = open("empty.txt", O_RDONLY);
//     line = get_next_line(fd);
//     printf("First call: %s\n", line);  // should print (null)
//     line = get_next_line(fd);
//     printf("Second call: %s\n", line); // should print (null)
//     close(fd);

//     return (0);
// }