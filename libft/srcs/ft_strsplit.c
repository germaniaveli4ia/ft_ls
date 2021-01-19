/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:33:15 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:45:06 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_next_start(char const *s, size_t pos, char delim)
{
	while (s[pos] && s[pos] == delim)
		pos++;
	return (pos);
}

static size_t	ft_next_len(char const *s, size_t start, char delim)
{
	size_t len;

	len = 1;
	while (s[start + len] && s[start + len] != delim)
		len++;
	return (len);
}

size_t			ft_count_words(char const *s, char delim)
{
	size_t count;
	size_t i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\0')
			break ;
		i = ft_next_start(s, i, delim);
		if (s[i] == '\0')
			break ;
		i += ft_next_len(s, i, delim);
		count++;
	}
	return (count);
}

static char		**ft_clean_words(char ***words, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		free(*words[i]);
		i++;
	}
	free(*words);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**words;
	size_t	words_count;
	size_t	i;
	size_t	pos;

	if (s == NULL)
		return (NULL);
	words_count = ft_count_words(s, c);
	if (!(words = (char**)ft_memalloc((words_count + 1) * sizeof(char**))))
		return (NULL);
	words[words_count] = NULL;
	pos = 0;
	i = 0;
	while (i < words_count)
	{
		pos = ft_next_start(s, pos, c);
		if (s[pos] == '\0')
			break ;
		words[i] = ft_strsub(s, pos, ft_next_len(s, pos, c));
		if (words[i] == NULL)
			return (ft_clean_words(&words, words_count));
		pos += ft_next_len(s, pos, c);
		i++;
	}
	return (words);
}
