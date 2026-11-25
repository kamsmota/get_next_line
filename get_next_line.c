/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/25 17:44:39 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_start(char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		return (ft_substr(buffer, 0, i + 1));
	else
		return (ft_substr(buffer, 0, i));
}

static char	*ft_update(char *buffer)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	stash = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
	free(buffer);
	if (!stash || stash[0] == '\0')
		return (free(stash), NULL);
	return (stash);
}

static char	*ft_read_file(int fd, char *stash)
{
	char		*buffer;
	size_t		byts;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	if (!stash)
		stash = ft_strdup("");
	byts = 1;
	while (byts > 0 && !ft_strchr(stash, '\n'))
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts < 0)
			break ;
		buffer[byts] = '\0';
		if (byts > 0)
			stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (free(buffer), free(stash), NULL);
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_start(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = ft_update(stash);
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