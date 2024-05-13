#include "get_next_line.h"

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
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

char *ft_strjoin(char *s1 , char *s2)
{
    char *hold;
    int len;

    if (!s1)
    {
        s1 = (char *)malloc(sizeof(char));
        s1[0] = '\0';
    }
    if(!s2)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2);
    hold = (char *)malloc(sizeof(char) *(len + 1));
    if(!hold)
        return (NULL);
    ft_strlcpy(hold, s1, ft_strlen(s1) + 1);
    ft_strlcpy(&hold[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
    hold[len] = '\0';
    free(s1);
    return (hold);
}
