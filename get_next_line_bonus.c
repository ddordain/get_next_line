/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:51:52 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/22 18:43:18 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		i++;
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
	static char	*save[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_the_buffer(save[fd], fd);
	if (save[fd] == NULL)
		return (NULL);
	next_line = check_the_line(save[fd]);
	save[fd] = clean_save(save[fd]);
	return (next_line);
}

#include "get_next_line_bonus.h"
#include <stdio.h>

int	main(int ac, char **av)
{	
	int		fd;
	// int		fd2;
	char	*line;
	// char	*line2;

	fd = open(av[1], O_RDONLY);
	// fd2 = open(av[1], O_RDONLY);
	while (42)
	{
		line = get_next_line(fd);
		// line2 = get_next_line(fd2);
		if (line == NULL)
			break ;
		printf("%s", line);
		// printf("%s", line2);
		free(line);
	}
	return (0);
}
