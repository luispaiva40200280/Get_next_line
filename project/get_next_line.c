/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:09 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/18 01:45:58 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_new_line(char *s)
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
		return (NULL);
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

static char	*ft_update_buff(char *buff)
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
	if (!buff[i + 1])
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

static char	*read_file(int fd, char *result)
{
	char		*buff;
	ssize_t		bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(result), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buff), free(result), NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		result = ft_strjoin_free(result, buff);
		if (!result)
			return (free(buff), NULL);
	}
	free(buff);
	return (result);
}


char	*get_next_line(int fd)
{
	static char	*buffer[MAX_BUFF];
	char		*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_BUFF)
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
	if (!line_read)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_update_buff(buffer[fd]);
	return (line_read);
}
 