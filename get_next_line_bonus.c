/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaougao <agaougao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:10:39 by agaougao          #+#    #+#             */
/*   Updated: 2023/12/21 11:29:09 by agaougao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_rest(char *buffer)
{
	int		i;
	int		len;
	char	*rest;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	len = ft_strlen(buffer) - i + 1;
	rest = malloc(len);
	if (!rest)
		return (NULL);
	i++;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_the_line(char *buffer)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (!buffer)
		return (NULL);
	while (buffer[len] != '\n' && buffer[len])
		len++;
	line = (char *)malloc(len + 2);
	if (!line)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	char	*line;
	int		read_byte;

	read_byte = 1;
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (read_byte > 0 && !ft_strchr(buffer, '\n'))
	{
		read_byte = read(fd, line, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		line[read_byte] = '\0';
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_the_line(buffer[fd]);
	buffer[fd] = get_rest(buffer[fd]);
	if (line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
