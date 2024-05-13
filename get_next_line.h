/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusukeyashiro <ryusukeyashiro@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:42:10 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/13 22:29:31 by ryusukeyash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 256
#endif

char *get_next_line(int fd);
char *ft_set_line(char *hold);
char *ft_next_line(char *hold);
char *ft_read_line(int fd , char *line);

char *ft_strjoin(char *s1, char *s2);
void ft_cat(char *hold, const char *string);
int ft_strlen(char *s);
char *ft_strchr(char *s , int c);
size_t  ft_strlcpy(char *dst , char *src , size_t dstsize);

#endif
