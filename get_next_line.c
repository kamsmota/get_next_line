/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/25 15:37:06 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_start(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i);
	line[i] = '\0';
	return (line);
}

static char	*ft_update(char *buffer)
{
	size_t	i;
	char	*stash;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		if (!buffer[i])
			return (NULL);
		stash = ft_substr(buffer, i, ft_strlen(buffer) - i - 1);
		return (stash);
	}
	return (NULL);
}

static char	*ft_read_file(int fd, char *stash)
{
	char		*buffer;
	size_t		byts;

	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	byts = 1;
	while (byts > 0)
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts < 0)
			break ;
		buffer[byts] = '\0';
		if (byts > 0)
			stash = ft_strjoin(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	if (byts < 0)
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_start(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	temp = ft_update(stash);
	free(stash);
	stash = temp;
	return (line);
}

#include <fcntl.h>

int	main (void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
