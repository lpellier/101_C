#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

enum _boolean {
	false,
	true
};

// utils
size_t	ft_strlen(char * str);
int		ft_strcmp(char *s1, char *s2);
char *	ft_strdup(char * str);
char *	ft_append_char(char * str, char c);
