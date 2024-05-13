/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusukeyashiro <ryusukeyashiro@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:11:34 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/14 02:09:38 by ryusukeyash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read_line(int fd , char *hold)
{
   int byte_num;
   char *temp;

   temp = (char*)malloc(sizeof(char) * (BUFFER_SIZE) + 1);
   if(!temp)
        return (NULL);
    byte_num = 1;
    while(!ft_strchr(hold , '\n') && byte_num != 0)
    {
        byte_num = read(fd , temp , BUFFER_SIZE);
        if(byte_num  == -1)
        {
            free(hold);
            return (free(temp) , NULL);
        }
        temp[byte_num] = '\0';
        hold = ft_strjoin(hold , temp);
    }
    free(temp);
    return (hold);
}

char *ft_set_line(char *hold)
{
    char *buf;
    int i;

    if(!hold || !hold[0])
        return (NULL);
    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(hold[i] == '\n')
        i++;
    buf = (char *)malloc(sizeof(char ) * (i + 1));
    if(!buf)
        return (NULL);
    ft_strlcpy(buf , hold  , i + 1);
    return (buf);
}

char *ft_next_line(char *hold)
{
    char *left;
    int i;

    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(!hold[i])
        return (NULL);
    i++;
    left = (char *)malloc(sizeof(char) * (ft_strlen(hold + i)+ 1));
    if(!left)
        return(NULL);
    ft_strlcpy(left , hold + i , ft_strlen(hold + i) + 1);
    free(hold);
    return (left);
}

char *get_next_line(int fd)
{
    static char *hold;
    char *output;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    hold = ft_read_line(fd , hold);
    if(!hold)
        return (NULL);
    output = ft_set_line(hold);
    if(!output)
        return (free(hold),NULL);
    hold = ft_next_line(hold);
    return (output);
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
