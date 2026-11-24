/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kams <kams@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/24 23:11:16 by kams             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_start(char **buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || !*buffer || (*buffer)[0] != '\0')
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (*(buffer)[i] == '\n')
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
		if (j == 0)
			return (NULL);
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
	char		*buffer;
	char		*temp;
	size_t		byts;
	
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

//#include <fcntl.h>
//int main(void)
//{
//    int fd;
//    char *line;

//    fd = open("test.txt", O_RDONLY);
//    line = get_next_line(fd);
//    while (line)
//    {
//        printf("%s", line);
//        free(line);
//        line = get_next_line(fd);
//    }
//    close(fd);
//    return (0);
//}