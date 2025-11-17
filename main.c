/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaiva <lpaiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:51:33 by lpaiva            #+#    #+#             */
/*   Updated: 2025/11/17 20:01:46 by lpaiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
/* 
if (ft_strchr(result, '\n'))  // Stop when newline found
static char	*buffer[1024]; //result of reading the file
char		*line_read; // line that is goind to be return
//error handler :: if fd does not exist or is empty;
if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
char	*buff; // store the value read of the file 
int		bytes; //bytes read 


	if (!buff[i]) // end of the file;
	int i; // for s
    	// handle to error
	if (!buffer[fd])
		return (NULL);
*/