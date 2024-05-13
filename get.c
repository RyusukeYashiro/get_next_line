#include "get_next_line.h"

char *ft_read_line(int fd, char *hold)
{
    int byte_num;
    char *temp;

    temp = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!temp)
        return (NULL);
    byte_num = 1;
    while (!ft_strchr(hold, '\n') && byte_num != 0) {
        byte_num = read(fd, temp, BUFFER_SIZE);
        if (byte_num == -1) {
            free(temp);
            free(hold);
            return (NULL);
        }
        temp[byte_num] = '\0';
        hold = ft_strjoin(hold, temp);
    }
    free(temp);
    return (hold);
}

char *ft_set_line(char *hold)
{
    char *line;
    int i;

    // if(!hold)
    //     return (NULL);
    if (!hold || !hold[0])
        return (NULL);
    // ファイルの内容がすべて読み取られ、これ以上読み取るデータがない場合、
    // 多くの読み取り関数は空の文字列を返します。この場合、関数は通常、
    // 0バイト読み取ったことを示す値（たとえば read() 関数では0）を返し、
    // 返されたバッファは空（""）になります。
    // この状況はファイルの末尾に達したことを意味します。
    i = 0;
    while (hold[i] && hold[i] != '\n')
        i++;
    if (hold[i] == '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
    {
        return (NULL);
        //free(hold);
    }
    ft_strlcpy(line, hold, i + 1);
    //free
    return (line);
}

char *ft_next_line(char *hold)
{
    char *next;
    int i;

    i = 0;
    while (hold[i] && hold[i] != '\n')
        i++;
    // if(!hold[i])
    //     return (free(hold),NULL);
    if (!hold[i])
        return (NULL);
    i++;
    next = (char *)malloc(sizeof(char) * (ft_strlen(hold + i) + 1));
    if (!next)
        return (NULL);
    // if(!left)
    //     return (free(hold) , NULL);
    ft_strlcpy(next, hold + i, ft_strlen(hold + i) + 1);
    free(hold);
    return (next);
}

char *get_next_line(int fd)
{
    static char *hold;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    hold = ft_read_line(fd, hold);
    if (!hold)
        return (NULL);
    line = ft_set_line(hold);
    if (!line) {
        free(hold);
        return (NULL);
    }
    hold = ft_next_line(hold);
    return (line);
}
 #include <fcntl.h>
int main (void)
{
    int fd;
    char *line;
    fd = open("./test.txt", O_RDONLY);
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
        {
            printf("%s\n" , "this is end");
            break;
        }
        printf("%s" , line);
        free(line);
    }
    close(fd);
    return (0);
}