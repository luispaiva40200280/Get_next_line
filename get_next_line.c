/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:15:09 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/16 00:24:07 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_new_line(char *s)
{
    int		i; // for s
	int		j; // for line
	char	*line;
	
	if (!s)
		return NULL;
	i = 0;
	j = -1;
	while (s[i] != '\n' && s[i])
		i++;
	line = malloc(i + 2);
	if (!line)
		return (free(line), NULL);
	while (++j < i)
		line[j] = s[j];
	if (s[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*ft_update_buff(char *buff)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i]) // end of the file;
		return (free(buff), NULL);
	new_buff = malloc(ft_strlen(buff) - i + 1);
	if (!new_buff)
		return (free(new_buff), NULL);
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
	char	*buff; // store the value read of the file 
	int		bytes; //bytes read 

	if (!result)
	{
		result = malloc(1);
		if (!result)
			return (free(result), NULL);
		result[0] = '\0';
	}
	buff = malloc(BUFFER_SIZE + 1);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buff), free(result), NULL);
		buff[bytes] = '\0';
		result = ft_strjoin(result, buff);
		if (ft_strchr(buff, '\n'))
			break;
	}
	free(buff);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024]; //result of reading the file
	char		*line_read; // line that is goind to be return
	
	//error handler :: if fd does not exist or is empty;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	// handle to error 
	if (!buffer[fd])
		return (NULL);
	line_read = ft_new_line(buffer[fd]);
	buffer[fd] = ft_update_buff(buffer[fd]);
	return (line_read);		
}


int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_count = 0;
    
    if (argc > 2)
        return (printf("Usage: %s <file>\n", argv[0]), 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (printf("Error opening file\n"), 1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);  // CRITICAL: Free each line
    }
    
    close(fd);
    return (0);
} 