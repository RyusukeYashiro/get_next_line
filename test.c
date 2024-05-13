#include "get_next_line.h"

static char *get_line(char *str)
{
    char *line;
    int i = 0;

    if (!str || !*str)
        return NULL;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        line = (char *)malloc(sizeof(char) * (i + 2));
    else
        line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
        return NULL;
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if (str[i] == '\n')
    {
        line[i] = '\n';
        i++;
    }
    line[i] = '\0';
    return line;
}

static char *update_str(char *str)
{
    char *new_str;
    int i = 0, j = 0;

    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
    {
        free(str);
        return NULL;
    }
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    if (!new_str)
        return NULL;
    i++;
    while (str[i])
        new_str[j++] = str[i++];
    new_str[j] = '\0';
    free(str);
    return new_str;
}

char *get_next_line(int fd)
{
    static char *str;
    char buf[BUFFER_SIZE + 1];
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    bytes_read = 1;
    while (!ft_strchr(str, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, buf, BUFFER_SIZE);
        if (bytes_read == -1)
            return NULL;
        buf[bytes_read] = '\0';
        str = ft_strjoin(str, buf);
    }
    if (!str)
        return NULL;
    line = get_line(str);
    str = update_str(str);
    return line;
}

// __attribute__((destructor))
// static void	a(void)
// {
// 	system("leaks -q a.out");
// }   

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("./test.txt", O_RDONLY);

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
//         {
//             printf("this is end\n");
//             break;
//         }  
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }