/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:50:44 by nnagel            #+#    #+#             */
/*   Updated: 2024/04/05 07:27:53 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

char	*ft_gnl_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (s[0] == '\0' && c == '\0')
		return ((char *)&s[0]);
	while (s[i])
	{
		if (s[0] == (char)c)
			return ((char *)&s[i]);
		if (s[i + 1] == (char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	return (NULL);
}

int	ft_gnl_strlen(char *s)
{
	int	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = (char *)ft_calloc(2, sizeof(char));
	i = ft_strlen(s1);
	s3 = (char *)ft_calloc(i + ft_strlen(s2) + 1, sizeof(char));
	if (!s1 || !s2 || !s3)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++j])
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*ft_cut_str(char *str)
{
	int		i;
	char	*o;
	char	*s;

	if (!str || str[0] == '\0')
		return (NULL);
	o = ft_gnl_strchr(str, '\n');
	if (o)
		s = (char *)ft_calloc(ft_strlen(str) - ft_strlen(o) + 2, sizeof(char));
	else
		s = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (o)
		s[i++] = '\n';
	s[i] = '\0';
	free(str);
	return (s);
}

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	size_t	i;
// 	char	*str;

// 	i = 0;
// 	str = (char *)b;
// 	while (i < len)
// 	{
// 		str[i] = c;
// 		i++;
// 	}
// 	return (b);
// }
