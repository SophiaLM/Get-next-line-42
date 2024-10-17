/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soluna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:29:03 by soluna            #+#    #+#             */
/*   Updated: 2024/10/15 20:34:04 by soluna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *str_buff)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0 && !ft_strchr(str_buff, '\n'))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= -1)
			return (free(buffer), free(str_buff), NULL);
		if (bytes_read == 0)
		{
			if (str_buff)
				return (free(buffer), str_buff);
			else
				return (free(buffer), NULL);
		}
		str_buff = ft_str_append(str_buff, buffer);
	}
	return (str_buff);
}

char	*ft_get_line(char *str_line)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (str_line[i] != '\0' && str_line[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = str_line[j];
		j++;
	}
	return (line);
}

char	*ft_next(char *buffer)
{
	char	*extra;
	int		j;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	if (ft_strlen(buffer) == i)
		return (free(buffer), NULL);
	extra = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!extra)
		return (NULL);
	j = 0;
	while (buffer[i])
		extra[j++] = buffer[i++];
	free(buffer);
	return (extra);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
/*
int	main()
{
	int	fd = open("only_nl.txt", O_RDONLY);
	char	*result;
	int	i;

//	printf("%s", result);
	i = 0;
	while (i < 2)
	{
		result = get_next_line(fd);
		printf("'%s'\n", result);
		free(result);
		i++;
	}
	return (0);
}*/
