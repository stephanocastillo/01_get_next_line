/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcastil <axcastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:23:09 by axcastil          #+#    #+#             */
/*   Updated: 2023/12/30 18:27:23 by axcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char	*buffer)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i ++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	next[j] = '\0';
	free(buffer);
	return (next);
}

//This function handles the return of the "reader" function, 
//filtering the characters found until the line break (\n) is found.

char	*liner(char	*buffer)
{
	char	*new_line;
	int		len;

	len = 0;
	if (buffer[len] == 0)
		return (NULL);
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len ++;
	len ++;
	new_line = ft_substr(buffer, 0, len);
	return (new_line);
}

//This function reads the file, having the "BUFFER_SIZE" that we set 
//as the reading pattern, and stops when it encounters a line break (\n)

char	*reader(int fd, char *result)
{
	int		byte_read;
	char	*buffer;

	result = ft_calloc(1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), NULL);
		buffer[BUFFER_SIZE] = 0;
		result = ft_strjoin(result, buffer);
		free(buffer);
		if (ft_strchr(result, '\n'))
			break ;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (result)
		{
			free(result);
			result = NULL;
		}
		return (NULL);
	}
	result = reader(fd, result);
	if (!result)
		return (NULL);
	new_line = liner(result);
	result = next_line(result);
	return (new_line);
}

/*int main()
{
    int fd;
    char *result;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        return (0);
    result = get_next_line(fd);
    while (result != NULL)
    {
        printf("%s",result);
        free(result);
        result = get_next_line(fd);
    }
    close(fd);
    return(0);
}*/
