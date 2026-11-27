/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 14:20:45 by kmota             #+#    #+#             */
/*   Updated: 2026/11/27 15:51:33 by kmota            ###   ########.fr       */
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
	int		byts;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	byts = 1;
	while (byts > 0 && !ft_strchr(stash, '\n'))
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts < 0)
			return (free(buffer), free(stash), stash = NULL, NULL);
		buffer[byts] = '\0';
		if (byts > 0)
			stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
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
