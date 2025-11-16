/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:14 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/15 23:35:56 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H  
# define   GET_NEXT_LINE_H
/*------- buffer zise ----*/
# ifndef BUFFER_SIZE
#  define   BUFFER_SIZE 1024
# endif

/* ---LIBERIES---*/
#include <stddef.h>
//#include <limits.h> /* for OPEN_MAX, fallback if not defined */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
/*-- --- --- ---  --*/

char    *ft_strchr(const char *s, int c);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_strlen(const char *str);
#endif