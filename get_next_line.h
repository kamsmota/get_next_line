/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:51:32 by kmota             #+#    #+#             */
/*   Updated: 2026/11/23 18:06:45 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNLLIB_H
# define GNLLIB_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1

#include <unistd.h>

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
#endif