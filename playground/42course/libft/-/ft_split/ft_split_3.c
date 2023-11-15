#include <stdlib.h>
#include <stdio.h>
static int	count(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
	{
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	int		index;
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	s_len = ft_strlen(s);
	while (++i <= s_len)
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == s_len) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
	}
	split[j] = 0;
	return (split);
}

int main() {
    const char* str = "abc__def";
    char delimiter = '_';
    
    char** words = ft_split(str, delimiter);
    for (int i = 0; words[i] != NULL; i++) {
        printf("%s\n", words[i]);
    }
    return 0;
}