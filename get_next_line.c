/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:38 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/23 18:41:41 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
char *get_next_line(int fd)
{
	static char	*str;
	char		*return_string;
	static int	a;
	
	if (str == NULL)
	{
		str = malloc(BUFFER_SIZE);
		if (str == NULL)
			return (NULL);
		a = 1;
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || a <= 0)
		return (NULL);	
	return_string = str;
	while (a > 0)
	{
		if (*(str - 1) == '\n')
			break ;		
		a = read(fd, str++, 1);

	}
	*str++ = '\0';
	return (return_string);
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