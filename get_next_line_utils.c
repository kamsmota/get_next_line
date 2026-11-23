/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmota <kmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:52:00 by kmota             #+#    #+#             */
/*   Updated: 2026/11/23 18:06:29 by kmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	unsigned char	*dst;
	unsigned char	*sr;
	
	dst = (unsigned char *)dest;
	sr = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
	{
		return (0);
	}
	if (n == 0 || (dest == src))
	{
		return (dest);
	}
	while (i < n)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dst);
}