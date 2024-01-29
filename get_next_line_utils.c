/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoudek <shoudek@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:05:09 by shoudek           #+#    #+#             */
/*   Updated: 2024/01/29 13:22:27 by shoudek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned int	max_int;
	size_t			i;

	max_int = 2147483647;
	if (nmemb > max_int && size > max_int)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (0);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (s[0] != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (s[0] == (unsigned char)c)
	{
		return ((char *)s);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		size++;
		s++;
	}
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if ((size_t)start + len > ft_strlen(s))
		len = ft_strlen(s) - (size_t)start;
	if ((size_t)start >= ft_strlen(s))
	{
		substr = malloc(sizeof(char));
		if (!substr)
			return (0);
		substr[0] = 0;
		return (substr);
	}
	substr = ft_calloc(sizeof(char), len + 1);
	if (!substr)
		return (0);
	i = 0;
	while (s[i + start] != '\0' && i < (unsigned int)len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
