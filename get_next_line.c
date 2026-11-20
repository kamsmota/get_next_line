/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:52:26 by kmota             #+#    #+#             */
/*   Updated: 2026/11/20 18:26:04 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	int	line;
	char	str;
	
	
	line = read(fd, buffer, sizeof(buffer));
}

// works the same when reading a file and when reading from the standard input
// must include the \n character and it is also the terminating to get the line

// read function to read the line, so line (variable) receives read with fd, buffer and buffersize
// if !line, return null and free the line, also the string that was read
// if read == 0 that means its the end of the file