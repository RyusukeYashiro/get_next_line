#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

char *get_next_line(int fd);

int ft_strlen(char *s);
char *ft_strchr(char *s, int c);
size_t ft_strlcpy(char *dst, char *src, size_t dstsize);
char *ft_strjoin(char *s1, char *s2);

#endif
