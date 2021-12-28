/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:16:13 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/22 18:42:42 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_save(char *save)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	buffer = ft_calloc(ft_strlen(save) - i + 1, sizeof(char));
	i++;
	while (save[i] != '\0')
	{
		buffer[j] = save[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	free(save);
	return (buffer);
}

char	*check_the_line(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	if (save[0] == '\0')
		return (NULL);
	while (save[i] != '\n' && save[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
	}
	return (line);
}

char	*read_the_buffer(char *save, int fd)
{
	char	*buffer;
	ssize_t	byte_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (ft_strchr(save, '\n') == NULL && byte_read != 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		if (save == NULL)
			save = ft_calloc(1, sizeof(char));
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_the_buffer(save, fd);
	if (save == NULL)
		return (NULL);
	next_line = check_the_line(save);
	save = clean_save(save);
	return (next_line);
}
