/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:47:09 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:44:24 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_clean_memory(char **str, size_t index)
{
	size_t		i;

	i = 0;
	while (i < index)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t		i;
	size_t		res;

	i = 0;
	res = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		res++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (res);
}

static size_t	ft_word_size(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*ft_next_word(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

char			**ft_split(char *s, char c)
{
	size_t		count;
	size_t		i;
	char		**str;

	count = ft_count_words((char *)s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < count)
	{
		s = ft_next_word(s, c);
		str[i] = ft_substr(s, 0, ft_word_size(s, c));
		if (str[i] == NULL)
		{
			ft_clean_memory(str, i);
			return (NULL);
		}
		i++;
		s = s + ft_word_size(s, c);
	}
	str[count] = NULL;
	return (str);
}
