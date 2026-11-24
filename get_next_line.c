/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kams <kams@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/24 22:53:24 by kams             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_start(char **buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || !*buffer || !(*buffer)[0] == '\0')
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, i);
	line[i] = '\0';
	return (line);
}

char	*ft_update(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*stash;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		j = 0;
		while (buffer[i + j])
			j++;
		stash = malloc(j + 1);
		if (!stash)
			return (NULL);
		ft_memcpy(stash, buffer + i, j); // &buffer[i]
		stash[j] = '\0';
	}
	else
		return (NULL);
	return (stash);
}

char	*ft_read_file(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	int		byts;
	
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);	
	}
	while (!(ft_strchr(stash, '\n')))
	{
		byts = read(fd, buffer, BUFFER_SIZE);
		if (byts == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (byts == 0)
			break;
		buffer[byts] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = temp;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	**buffer;
	int			end_word;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_start(buffer);
	end_word = -1; // palavra antes do \n
	if (!line)
		return (NULL);
}

// works the same when reading a file and when reading from the standard input
// must include the \n character and it is also the terminating to get the line

// read function to read the line, so line (variable) receives read with fd, buffer and buffersize
// if !line, return null and free the line, also the string that was read
// if read == 0 that means its the end of the file
// if read == -1 means an error occurred

// how to do it:
// on gnl function, check if the fd exists an dif the size of the buffer isnt 0 or minor
// its necessary to iniciate the line, so it can have malloc