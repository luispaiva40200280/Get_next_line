/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:09 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/17 23:27:00 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_new_line(char *s)
{
	char	*line;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(i + (s[i] == '\n') + 1);
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_update_buff(char *buff)
{
	char	*new_buff;
	int		i;
	int		j;

	if (!buff)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
		return (free(buff), NULL);
	new_buff = malloc(ft_strlen(buff + i + 1) + 1);
	if (!new_buff)
		return (free(buff), NULL);
	i++;
	j = 0;
	while (buff[i])
		new_buff[j++] = buff[i++];
	new_buff[j] = '\0';
	free(buff);
	return (new_buff);
}

char	*read_file(int fd, char *result)
{
	char	*buff;
	int		bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(result), free(buff), NULL);
	while (!ft_strchr((const char *)result, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buff), NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		result = ft_strjoin_free(result, buff);
		if (!result)
			return (free(buff), NULL);
	}
	return (free(buff), result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_BUFF];
	char		*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line_read = ft_new_line(buffer[fd]);
	buffer[fd] = ft_update_buff(buffer[fd]);
	return (line_read);
}
