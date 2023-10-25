/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/25 19:36:41 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// char *get_next_line(int fd)
// {
// 	static char	*str;
// 	char		*return_string;
// 	static int	a;
// 	if (str == NULL)
// 	{
// 		str = malloc(BUFFER_SIZE);
// 		if (str == NULL)
// 			return (NULL);
// 		a = 1;
// 	}
// 	if (fd < 0 || BUFFER_SIZE <= 0 || a <= 0)
// 		return (NULL);	
// 	return_string = str;
// 	while (a > 0)
// 	{
// 		if (*(str - 1) == '\n')
// 			break ;		
// 		a = read(fd, str++, 1);
// 	}
// 	*str++ = '\0';
// 	return (return_string);
// }

// int	ft_strlen(const char *s)
// {
// 	unsigned int	i;

// 	if (s == NULL)
// 		return (0);
// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	unsigned char	uc;
// 	unsigned char	*p;
// 	size_t			i;

// 	uc = (unsigned char)c;
// 	p = (unsigned char *)b;
// 	i = 0;
// 	while (i < len)
// 	{
// 		p[i] = uc;
// 		i++;
// 	}
// 	return (b);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	ft_memset(s, 0, n);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;
// 	size_t	total;

// 	total = count * size;
// 	ptr = malloc(total);
// 	if (ptr == NULL)
// 		return (NULL);
// 	ft_bzero(ptr, total);
// 	return (ptr);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

static char	*ft_strjoin(char const *s1, char const *s2)
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
	char	buffer[BUFFER_SIZE + 1];
	int		a;
	char	*tmp;
	
	a = 1;
	while (ft_strchr(buffer, '\n') == NULL && a > 0)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 0)
			return (NULL);
		buffer[a] = '\0';
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;	
	}
	return (str);
}

static char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = calloc(i + 1, 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	i++;
	new_str = calloc((ft_strlen(str) - i) + 1, 1);
	if (new_str == NULL)
		return (free(str), NULL);
	j = 0;
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*return_str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = append_str(fd, str);
	if (str == NULL)
		return (NULL);
	return_str = extract_line(str);
	str = update_str(str);
	return (return_str);
}

// #include <stdio.h>
// int main(void)
// {
// 	int fd;
// 	fd = open("textfile.txt", O_RDONLY);
// 	printf("fd: %i\n", fd);
// 	if (fd == -1)
// 		printf("Error opening the file");
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	if (close(fd) == -1)
// 		printf("Error closing the file");
// 	else
// 		printf("file closed");
// }