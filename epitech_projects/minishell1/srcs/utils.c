#include "../includes/minishell1.h"

void	ft_putstr(int fd, const char * str) {
	for (int i = 0; str[i]; i++)
		write(fd, &str[i], 1);
}

/**
 * @brief prints the appropriate error message and returns appropriate error code
 * 
 * @param error_code 
 * @param error_override allows to return 2 instead of 1 in the case of cd failure 
 * @return appropriate error
 */
int		print_error(int error_code, bool error_override) {
	switch (error_code) {
		case SEARCH_FAILED:
			ft_putstr(STDERR, "no such file or directory\n");
		case NO_OLDPWD:
			ft_putstr(STDERR, "environment variable $OLD_PWD is not set\n");
		case NO_HOME:
			ft_putstr(STDERR, "environment variable $HOME is not set\n");
		case TOO_MANY_ARGUMENTS:
			ft_putstr(STDERR, "too many arguments\n");
		case TOO_FEW_ARGUMENTS:
			ft_putstr(STDERR, "too few arguments\n");
		case START_FAILURE:
			ft_putstr(STDERR, "./minishell1 does not take any arguments\n");
		default:
			break;
	}

	if (error_override)
		return (2);
	return (1);
}

int		check_errors(int argc) {
	if (argc > 1)
		return (START_FAILURE);
	return (SUCCESS);
}

size_t  ft_strlen(const char *str)
{
        size_t  i;

        i = 0;
        while (str[i])
                i++;
        return (i);
}

int     count_words(const char *str, char c)
{
        int     i;
        int     trigger;

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

char    *word_dup(const char *str, int start, int finish)
{
        char    *word;
        int             i;

        i = 0;
        word = malloc((finish - start + 1) * sizeof(char));
        while (start < finish)
                word[i++] = str[start++];
        word[i] = '\0';
        return (word);
}

char    **ft_split(char const *s, char c)
{
        size_t  i;
        size_t  j;
        int             index;
        char    **split;

        split = malloc((count_words(s, c) + 1) * sizeof(char *));
        if (!s || !split)
                return (0);
        i = 0;
        j = 0;
        index = -1;
        while (i <= ft_strlen(s))
        {
                if (s[i] != c && index < 0)
                        index = i;
                else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
                {
                        split[j++] = word_dup(s, index, i);
                        index = -1;
                }
                i++;
        }
        split[j] = 0;
        return (split);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
