/* CHATGPT VERSION WORKING FOR THE MANDATORY PART */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include <stdio.h>
#include <fcntl.h>
#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/* ===================== UTILS ===================== */

static size_t   ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

static char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (NULL);
}

static char *ft_strjoin(char *s1, char *s2)
{
    size_t  i = 0, j = 0;
    char    *new_str;

    if (!s1)
    {
        s1 = malloc(1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!new_str)
        return (free(s1), NULL);
    while (s1[i])
    {
        new_str[i] = s1[i];
        i++;
    }
    while (s2[j])
        new_str[i++] = s2[j++];
    new_str[i] = '\0';
    free(s1);
    return (new_str);
}

/* ===================== CORE ===================== */

static char *extract_line(char *buffer)
{
    int     i = 0;
    char    *line;

    if (!buffer || !buffer[0])
        return (NULL);

    while (buffer[i] && buffer[i] != '\n')
        i++;

    line = malloc(i + (buffer[i] == '\n') + 1);
    if (!line)
        return (NULL);

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

static char *trim_buffer(char *buffer)
{
    int     i = 0, j = 0;
    char    *next;

    while (buffer[i] && buffer[i] != '\n')
        i++;

    if (!buffer[i])
        return (free(buffer), NULL);

    i++;
    next = malloc(ft_strlen(buffer) - i + 1);
    if (!next)
        return (free(buffer), NULL);

    while (buffer[i])
        next[j++] = buffer[i++];
    next[j] = '\0';

    free(buffer);
    return (next);
}

static char *read_fd(int fd, char *buffer)
{
    char    *tmp = malloc(BUFFER_SIZE + 1);
    ssize_t bytes = 1;

    if (!tmp)
        return (buffer);

    while (!ft_strchr(buffer, '\n') && bytes > 0)
    {
        bytes = read(fd, tmp, BUFFER_SIZE);
        if (bytes < 0)
        {
            free(tmp);
            return (free(buffer), NULL);
        }
        tmp[bytes] = '\0';
        buffer = ft_strjoin(buffer, tmp);
        if (!buffer)
        {
            free(tmp);
            return (NULL);
        }
    }
    free(tmp);
    return (buffer);
}

/* ===================== MAIN FUNCTION ===================== */

char    *get_next_line(int fd)
{
    static char *buffer[OPEN_MAX];
    char        *line;

    if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
        return (NULL);

    buffer[fd] = read_fd(fd, buffer[fd]);
    if (!buffer[fd])
        return (NULL);

    line = extract_line(buffer[fd]);
    buffer[fd] = trim_buffer(buffer[fd]);

    return (line);
}

/* ===================== OPTIONAL TEST ===================== */

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *s;

    while ((s = get_next_line(fd)))
    {
        printf("%s", s);
        free(s);
    }
}
