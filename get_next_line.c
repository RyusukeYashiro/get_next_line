/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryyashir <ryyashir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:11:34 by ryusukeyash       #+#    #+#             */
/*   Updated: 2024/05/14 05:07:38 by ryyashir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *hold)
{
	int		byte_num;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!temp)
		return (NULL);
	byte_num = 1;
	while (/*!ft_strchr(hold, '\n') &&*/ byte_num != 0)
	{
		byte_num = read(fd, temp, BUFFER_SIZE);
		if (byte_num == -1)
		{
			free(hold);
			return (free(temp), NULL);
		}
		temp[byte_num] = '\0';
		hold = ft_strjoin(hold, temp);
	}
	free(temp);
	return (hold);
}

char	*ft_set_line(char *hold)
{
	char	*buf;
	int		i;

	if (!hold || !hold[0])
		return (NULL);
	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	buf = (char *)malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, hold, i + 1);
	return (buf);
}

char	*ft_next_line(char *hold)
{
	char	*new_hold;
	int		i;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (!hold[i])
		return (NULL);
	i++;
	new_hold = (char *)malloc(sizeof(char) * (ft_strlen(hold + i) + 1));
	if (!new_hold)
		return (NULL);
	ft_strlcpy(new_hold, hold + i, ft_strlen(hold + i) + 1);
	free(hold);
	return (new_hold);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	hold = ft_read_line(fd, hold);
	printf("hold: %s\n", hold);
	if (!hold)
    {
        hold = NULL;
        return(NULL);
    }
	output = ft_set_line(hold);
	if (!output)
	{
        free(hold);
        hold = NULL;
        return (NULL);
    }
	hold = ft_next_line(hold);
	return (output);
}

__attribute__((destructor))
static void	a(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);

	int i = 1;
	while (1)
	{
		printf("%d 回目の呼び出し", i);
		i++;
		line = get_next_line(fd);
		if (!line)
        {
            printf("this is end\n");
            break;
        }  
		printf("line is >>%s<<\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
