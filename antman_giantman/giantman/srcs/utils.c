#include "../includes/giantman.h"

size_t	ft_strlen(char * str) {
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_ustrlen(unsigned char * str) {
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char *	ft_strdup(char * str) {
	char *	ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i]) {
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char *	ft_append_char(char * str, char c) {
	char *	ret;
	int		i;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	i = 0;
	while (str[i]) {
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return ret;
}

unsigned char *	ft_append_uchar(unsigned char * str, unsigned char c) {
	unsigned char *	ret;
	int		i;

	ret = malloc(sizeof(char) * (ft_ustrlen(str) + 2));
	i = 0;
	while (str[i]) {
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return ret;
}
