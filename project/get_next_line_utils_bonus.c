/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:05 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/17 23:27:11 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*str_dest;
	const char	*str_src;

	if (!src && !dest)
		return (NULL);
	str_dest = (char *)dest;
	str_src = (const char *)src;
	while (n--)
		*str_dest++ = *str_src++;
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	car;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	car = (unsigned char)c;
	while (*str)
	{
		if (*str == car)
			return ((char *)str);
		str++;
	}
	if (car == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_str;

	if (!s1 || !s2)
		return (free(s1), NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!new_str)
		return (free(s1), NULL);
	ft_memcpy(new_str, s1, len_s1);
	ft_memcpy(new_str + len_s1, s2, len_s2);
	new_str[len_s1 + len_s2] = '\0';
	return (free(s1), new_str);
}
