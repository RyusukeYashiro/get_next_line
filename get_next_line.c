/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusukeyashiro <ryusukeyashiro@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:11:34 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/13 22:35:30 by ryusukeyash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read_line(int fd , char *hold)
{
   int byte_num;
   char *temp;
   char *new_hold;

   temp = (char*)malloc(sizeof(char) * (BUFFER_SIZE) + 1);
   if(!temp)
        return (NULL);
    byte_num = 1;
    while(!ft_strchr(hold , '\n') && byte_num != 0)
    {
        byte_num = read(fd , temp , BUFFER_SIZE);
        if(byte_num < 0)
            return (free(temp) , NULL);
        temp[byte_num] = '\0';
        hold = ft_strjoin(hold , temp);
        if(!new_hold)
            return (free(temp) , NULL);
        free(hold);
        hold = new_hold;
    }
    free(temp);
    return (hold);
}

char *ft_set_line(char *hold)
{
    char *buf;
    int i;
    int len;

    if(!hold[0])
        return (NULL);
    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(hold[i] == '\n')
        i++;
    len = ft_strlen(hold) - i;
    buf = (char *)malloc(sizeof(int) * (len + 1));
    if(buf)
    {
        free(hold);
        return (NULL);
    }
    ft_strlcpy(buf , hold + i , len + 1);
    free(hold);
    return (buf);
}

char *ft_next_line(char *hold)
{
    char *left;
    int i;
    int len;

    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(!hold[i])
        return (free(hold),NULL);
    len = ft_strlen(hold + i);
    left = (char *)malloc(sizeof(char) * (len + 1));
    if(!left)
        return (free(hold) , NULL);
    i++;
    ft_strlcpy(left , hold + i , (len + 1));
    free(hold);
    return (left);
}

char *get_next_line(int fd)
{
    static char *hold;
    char *output;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (0);
    hold = ft_read_line(fd , hold);
    if(!hold)
        return (NULL);
    output = ft_set_line(hold);
    hold = ft_next_line(hold);
    return (output);
}
    //bufferサイズの超過分を保持する変数。次に見るとこをはここになる
    // static char *hold;
    // //文字列を一行分出力する関数
    // char *output;
    // //メモリーリークを防ぐために一度static holdを入れておくための箱
    // char *new_hold;
    
    // output = NULL;
    // if(fd < 0 || BUFFER_SIZE <= 0)
    //     return (NULL);
    // hold  = ft_read_line(fd , hold);
    // if(!hold)
    //     return (NULL);
    // output = ft_set_line(hold);
    // if(!output)
    //     return (free(hold),NULL);
    // new_hold = ft_next_line(hold);
    // if(!new_hold)
    //     return(free(hold),NULL);
    // hold = new_hold;
    // return (output);
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
