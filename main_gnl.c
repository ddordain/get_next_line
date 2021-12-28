/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:54:07 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/22 18:25:29 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
