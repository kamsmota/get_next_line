/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kams <kams@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:52:08 by kmota             #+#    #+#             */
/*   Updated: 2026/11/26 21:59:59 by kams             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char		*get_next_line(int fd);
size_t		ft_strlen(char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char *s, size_t start, size_t len);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);

#endif