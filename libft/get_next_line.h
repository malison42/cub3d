/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzots <vzots@student.42yerevan.am>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:59:18 by vzots             #+#    #+#             */
/*   Updated: 2026/01/15 21:16:37 by vzots            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr2(const char *s, int c);
// size_t	ft_strlen(const char *str);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup(const char *src);
char	*get_next_line(int fd);
#endif
