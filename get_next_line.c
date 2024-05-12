/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusukeyashiro <ryusukeyashiro@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:11:34 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/12 17:25:25 by ryyashir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read_line(int fd , char*line)
{
    int byte_num;
    char *temp;

    byte_num = 1;
    temp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if(!temp)
        return (NULL);
    while(!ft_strchr(line , '\n'))
    {
        byte_num = read(fd , temp  , BUFFER_SIZE);
        if(byte_num == -1)
            return (free(temp), NULL);
        else if(byte_num == 0)
            break;
        line = ft_strjoin(line, temp);
        if(!line)
            return (free(line),NULL);
    }
    free(temp);
    return (line);
}

char *ft_set_line(char *hold)
{
    char *buf;
    int i;

    i = 0;
    while(hold[i] &&  hold[i] != '\n')
        i++;
    buf = (char *)malloc(sizeof(char)*(i + 1));
    if(!buf)
        return (free(hold) , NULL);
    ft_strlcpy(buf, hold,i + 1);
    return (buf);
}

char *ft_next_line(char *hold)
{
    char *left;
    int i;
    int len;

    len = ft_strlen(hold);
    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(!hold[i+1])
        return (free(hold),NULL);
    left = (char *)malloc(sizeof(char) * (len - i));
    if(!left)
        return (free(hold) , NULL);
    i++;
    ft_strlcpy(left , hold , (len - i));
    free(hold);
    return (left);
}

char *get_next_line(int fd)
{
    //bufferサイズの超過分を保持する変数。次に見るとこをはここになる
    static char *hold;
    //出力する文字列を保持する変数
    char *line;

    line = NULL;
    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    hold  = ft_read_line(fd , line);
    if(!hold)
        return (NULL);
    line = ft_set_line(hold);
    if(!line)
        return (NULL);
    hold = ft_next_line(hold);
    return (line);
}

int main (void)
{
    int fd;
    char *line;
    fd = open("./test.txt", O_RDONLY);
    if(fd == -1)
    {
        printf("%s\n","opeing file is error");
        return (1);
    }
    while(1)
    {
        line = get_next_line(fd);
        if(!line)
        {
            printf("%s\n" , "this is end");
            break;
        }
        printf("%s" , line);
    }
    close(fd);
    return (0);
}
