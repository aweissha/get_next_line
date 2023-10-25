/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/24 17:45:20 by aweissha         ###   ########.fr       */
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



char *append_str(int fd, char *str)
{
	char	*buffer;
	int		a;

	buffer = calloc(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);
	a = 1;
	while (ft_strchr(buffer, '\n') == NULL && a != 0)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 0)
		{
			free(buffer);
			return (NULL);			
		}

		buffer[a] = '\0';
		str = ft_strjoin(str, buffer);
		// ft_strjoin function has to be adjusted, so that it handles a NULL pointer//
	}
	free(buffer);
	return (str);
}

char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = calloc(i + 2, 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n');
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}


char	*update_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	j = 0;
	while (str[i + j] != '\0')
		j++;
	new_str = calloc(j + 1, 1);
	if (new_str == NULL)
		return (NULL);
	j = 0;
	while (str[i + j] != '\0')
	{
		new_str[j] = str[i + j];
		j++;		
	}
	free(str);
	return (new_str);
}




char *get_next_line(int fd)
{
	static char	*str;
	char *return_str;



	str = append_str(fd, str);




	return_str = extract_line(str);

	str = update_str(str);

	return (return_str);
}
	


#include <stdio.h>
int main(void)
{
/*declaring file descriptor and defining it by opening the file. In case smth goes wrong (open returns -1) an error message is printed*/
	int fd;
	
	fd = open("textfile.txt", O_RDONLY);

	printf("fd: %i\n", fd);

	if (fd == -1)
		printf("Error opening the file");

	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
		
/*Closing the file using file descriptor*/
	if (close(fd) == -1)
		printf("Error closing the file");
	else
		printf("file closed");
		
}