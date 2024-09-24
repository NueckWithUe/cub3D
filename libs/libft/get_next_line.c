/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:55:34 by nnagel            #+#    #+#             */
/*   Updated: 2024/04/05 09:06:27 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static char	*ft_free(char *of, char *buffer, char *string)
{
	if (of)
	{
		free(of);
		of = NULL;
	}
	free(buffer);
	if (string)
		free(string);
	return (NULL);
}

static char	*ft_get_of(char *str)
{
	char	*ovf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	ovf = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	while (str[++i])
	{
		ovf[j] = str[i];
		j++;
	}
	ovf[j] = '\0';
	if (ovf[0] == '\0')
	{
		free(ovf);
		ovf = NULL;
	}
	return (ovf);
}

static char	*ft_reading(int fd, char *string)
{
	int		rb;
	char	*buffer;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(buffer), NULL);
	rb = 1;
	while (rb > 0)
	{
		rb = read(fd, buffer, BUFFER_SIZE);
		if (rb < 0)
			return (ft_free(NULL, buffer, string));
		if (rb < BUFFER_SIZE)
			buffer[rb] = '\0';
		if (buffer[0] != '\0')
		{
			string = ft_gnl_strjoin(string, buffer);
			if (ft_gnl_strchr(string, '\n'))
				break ;
		}
	}
	free(buffer);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str;
	static char	*of;

	str = NULL;
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(of, buffer, str));
	if (of && of[0] != '\0')
	{
		str = ft_gnl_strjoin(str, of);
		free(of);
		of = NULL;
	}
	str = ft_reading(fd, str);
	if (ft_gnl_strchr(str, '\n'))
		of = ft_get_of(str);
	str = ft_cut_str(str);
	if (!str)
		return (ft_free(of, buffer, str));
	free(buffer);
	return (str);
}
