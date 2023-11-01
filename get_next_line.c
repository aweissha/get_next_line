/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/11/01 11:36:57 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char			*str_joined;
	unsigned int	i;
	unsigned int	j;

	str_joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str_joined == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			str_joined[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str_joined[i + j] = s2[j];
		j++;
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}

static char	*append_str(int fd, char *str)
{
	char	*buffer;
	int		a;
	char	*tmp;

	buffer = calloc(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(buffer, '\n') == NULL)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 0)
			return (NULL);
		else if (a == 0)
			break ;
		buffer[a] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	free(buffer);
	return (str);
}

static char	*update_str(char *line)
{
	char	*new_str;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new_str = ft_strdup(line + i + 1);
	if (*new_str == '\0')
	{
		free(new_str);
		new_str = NULL;
	}
	line[i + 1] = '\0';
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = append_str(fd, str);
	if (line == NULL)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = update_str(line);
	return (line);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*line;
// 	int		i = 1;
// 	// int		fd;

// 	fd = open("otherfile.txt", O_RDONLY);
// 	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
// 	while (i < 5)
// 	{
// 		line = get_next_line(fd);
// 		printf("line3-%d: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	// close(fd);
// 	return (0);
// }
