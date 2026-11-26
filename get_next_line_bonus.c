/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kams <kams@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:52:11 by kmota             #+#    #+#             */
/*   Updated: 2026/11/26 22:27:06 by kams             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	char	*buffer;
	char	*temp;
	int		byts;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	if (!stash)
		stash = ft_strdup("");
	byts = 1;
	while (byts > 0 && !ft_strchr(stash, '\n'))
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts < 0)
			return (free(buffer), free(stash), NULL);
		buffer[byts] = '\0';
		if (byts > 0)
		{
			temp = ft_strjoin(stash, buffer);
			free(stash);
			stash = temp;
		}
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_file(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_start(stash[fd]);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = ft_update(stash[fd]);
	return (line);
}

//#include <fcntl.h>

//int	main (void)
//{
//	int		fd;
//	char	*line;

//	fd = open("test.txt", O_RDONLY);
//	line = get_next_line(fd);
//	while (line)
//	{
//		printf("%s", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	close(fd);
//	return (0);
//}