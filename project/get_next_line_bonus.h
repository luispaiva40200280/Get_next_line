/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:14 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/17 23:31:40 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/* ------- buffer size ----*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
/* ----- max buffer SIZE */
# ifndef MAX_BUFF
#  define MAX_BUFF 1024
# endif

/* ---LIBRARIES---*/
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ---FUNCTION DECLARATIONS---*/
char	*get_next_line(int fd);
char	*read_file(int fd, char *result);
char	*ft_new_line(char *s);
char	*ft_update_buff(char *buff);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_free(char *s1, const char *s2);
int		ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif