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
size_t	ft_ustrlen(unsigned char * str);
int		ft_strcmp(unsigned char *s1, unsigned char *s2);
unsigned char *	ft_strdup(unsigned char * str);
char *	ft_append_char(char * str, char c);
unsigned char *	ft_append_uchar(unsigned char * str, unsigned char c);
