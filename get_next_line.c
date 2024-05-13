/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusukeyashiro <ryusukeyashiro@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:11:34 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/13 14:31:52 by ryyashir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_read_line(int fd , char *hold)
{
    int byte_num;
    char *temp;
    char *new_hold;

    byte_num = 1;
    temp = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if(!temp)
        return (NULL);
    while(!ft_strchr(hold , '\n'))
    {
        byte_num = read(fd , temp, BUFFER_SIZE);
        if(byte_num == -1)
            return (free(temp), NULL);
        else if(byte_num == 0)
            break;
        temp[byte_num] = '\0';
        new_hold = ft_strjoin(hold, temp);
        free(hold);
        hold = new_hold;
        if(!hold)
            return (free(temp),NULL);
    }
    free(temp);
    return (hold);
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

    i = 0;
    while(hold[i] && hold[i] != '\n')
        i++;
    if(!hold[i] || !hold[i+1])
        return (free(hold),NULL);
    len = ft_strlen(hold + i + 1);
    left = (char *)malloc(sizeof(char) * (len + 1));
    if(!left)
        return (free(hold) , NULL);
    i++;
    ft_strlcpy(left , hold + i + 1 , (len + 1));
    free(hold);
    return (left);
}

char *get_next_line(int fd)
{
    //bufferサイズの超過分を保持する変数。次に見るとこをはここになる
    static char *hold;
    //文字列を一行分出力する関数
    char *output;
    //メモリーリークを防ぐために一度static holdを入れておくための箱
    char *new_hold;
    
    output = NULL;
    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    hold  = ft_read_line(fd , hold);
    if(!hold)
        return (NULL);
    output = ft_set_line(hold);
    if(!output)
        return (free(hold),NULL);
    new_hold = ft_next_line(hold);
    if(!new_hold)
        return(free(hold),NULL);
    hold = new_hold;
    return (output);
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
