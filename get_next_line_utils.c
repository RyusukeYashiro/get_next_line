#include "get_next_line.h"

int ft_strlen(char *s)
{
    int len;

    len = 0;
    if(!s)
        return 0;
    while(*s)
    {
        s++;
        len++;
    }
    return (len);
}

char *ft_strchr(char *s , int c)
{
    if(!s)
        return (NULL);
    while(*s)
    {
        if(*s == (char)c)
            return ((char *)s);
        s++;
    }
    if(c == '\0')
        return ((char*)s);
    return (NULL);
}

size_t  ft_strlcpy(char *dst , char *src , size_t dstsize)
{
    size_t i;
    size_t len;

    i = 0;
    len = 0;
    len = ft_strlen(src);
    if(dstsize != 0)
    {
        while(src[i] && i < dstsize - 1)
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (len);
}

void ft_cat(char *hold , const char *string)
{
    int i;

    i = 0;
    if(!string)
        return ;
    while(string[i])
    {
        hold[i] = string[i];
        i++;
    }
}

char *ft_strjoin(char *s1 , char *s2)
{
    char *hold;
    int len;

    if(!s2)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    hold = (char *)malloc(sizeof(char) *(len + 1));
    if(!hold)
        return (NULL);
    ft_cat(hold , s1);
    ft_cat(hold + ft_strlen(s1),s2);
    hold[len] = '\0';
    return (hold);
}
