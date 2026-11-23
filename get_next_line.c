/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/23 18:21:35 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"
#include <unistd.h>

char	ft_start(char *buffer, int end_word)
{
	char	*line;
	// int		end_word;
	size_t	i;
	
	if (!buffer || buffer[0] == '\0')
	{
		line = malloc(1);
		if (line)
			line[0] = '\0';
		return (line);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i);
	line[i] = '\0';
	if (line[i - 1] == '\n')
		end_word = i - 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			end_word;
	char		line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	line = ft_start(buffer, end_word);
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