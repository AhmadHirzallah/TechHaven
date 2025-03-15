/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:31:56 by ahirzall          #+#    #+#             */
/*   Updated: 2024/09/07 14:34:20 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	words_count;

	words_count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words_count++;
		while (*s && (*s != c))
			s++;
	}
	return (words_count);
}

static int	ft_get_word_of_sentence_length(char const *s, char c)
{
	int	word_len;

	word_len = 0;
	while (s[word_len] && (s[word_len] != c))
		word_len++;
	return (word_len);
}

static void	*ft_free_ultimate(char **s, int n)
{
	while (n >= 0)
		free(s[n--]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words_count;
	int		any_word_size;
	int		i;
	char	**created_words;

	words_count = ft_count_words(s, c);
	created_words = ft_calloc(sizeof(char *), (words_count + 1));
	if (!s || !created_words)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		if (*s != c)
		{
			any_word_size = (ft_get_word_of_sentence_length(s, c) + 1);
			created_words[i] = (char *)(ft_calloc(sizeof(char), any_word_size));
			if (!created_words[i])
				return (ft_free_ultimate(created_words, i));
			ft_strlcpy(created_words[i], s, any_word_size);
			s += (any_word_size - 1);
			i++;
		}
		s++;
	}
	return (created_words);
}
