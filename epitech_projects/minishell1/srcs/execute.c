#include "../includes/minishell1.h"

char * append_to(char * str, char c) {
	char *	ret;
	int		i;

	if (!str) {
		ret = malloc(sizeof(char) * 2);
		ret[0] = c;
		ret[1] = '\0';
	}
	else {
		i = 0;
		while (str[i])
			i++;
		ret = malloc(sizeof(char) * (i + 1 + 1));
		i = 0;
		while (str[i]) {
			ret[i] = str[i];
			i++;
		}
		ret[i] = c;
		ret[i + 1] = '\0';
	}
	return (ret);
}

int		read_input(t_info * info) {
	char	*buf;
	char	*tmp;
	size_t	n;

	(void)info;
	n = 0;
	tmp = NULL;
	buf = NULL;
	if (getline(&buf, &n, stdin) == -1) {
		secure_free((void **)&buf);
		return (EXIT_FAILURE);
	}
	info->cmd = ft_split(buf, ' ');
	secure_free((void **)&buf);
	return (SUCCESS);
}