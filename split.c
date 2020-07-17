#include "cub3d.h"
#include <stdio.h>
#include <string.h>

static void		ft_clean_memory(char **str, size_t index)
{
	size_t i;

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


size_t		ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((int)((unsigned const char)s1[i] - (unsigned const char)s2[i]));
}

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	i;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > length)
		return (ft_strdup(""));
	if (length - start < len)
		len = length - start;
	string = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		string[i] = s[start];
		start++;
		i++;
	}
	string[i] = '\0';
	return (string);
}

char		*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;

	size = 0;
	while (s1[size] != '\0')
		size++;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	size = 0;
	while (s1[size] != '\0')
	{
		str[size] = s1[size];
		size++;
	}
	str[size] = '\0';
	return (str);
}

char		*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

int 		ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f'
		|| c == '\r'  );
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

int		main(void)
{
	char 		*s;
	char		c;
	char		**res;
	size_t		i;
	i = 0;
	s = "     R         1090        1891        ";
	c = ' ';
	res = ft_split(s, c);
	while (i < ft_count_words(s, c))
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (0);
}