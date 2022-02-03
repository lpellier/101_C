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

bool	binary_exists(t_info * info) {
	DIR *			current_directory;
	struct dirent *	current_file;

	for (int i = 0; info->path[i]; i++) {
		current_directory = opendir(info->path[i]);
		if (!current_directory)
			ft_putstr(STDERR, "path environment variable is incorrect\n");
		else {
			while ((current_file = readdir(current_directory))) {
				if (!ft_strcmp(current_file->d_name, info->cmd[0]) && !access(current_file->d_name, X_OK))
					return (true);
			}
		}
	}
	return (false);
}

int		exec_binary(t_info * info) {
	pid_t	cpid;

	t_ms * ms ;
	cpid = fork();
	// child commence la
	if (cpid == -1)
		return (84);
	else if (cpid == 0) {
		// in child
		execve();
		exit();
	}
	else {
		waitpid(cpid);
		// in parent
	}
}

int		execute_cmd(t_info * info) {
	if (!ft_strcmp(info->cmd[0], "cd"))
		return (cd_builtin(info));
	else if (!ft_strcmp(info->cmd[0], "setenv"))
		return (setenv_builtin(info));
	else if (!ft_strcmp(info->cmd[0], "unsetenv"))
		return (unsetenv_builtin(info));
	else if (!ft_strcmp(info->cmd[0], "env"))
		return (env_builtin(info));
	else if (!ft_strcmp(info->cmd[0], "exit"))
		return (exit_builtin(info));
	else if (binary_exists(info))
		return (exec_binary(info));
	else
		return (print_error(SEARCH_FAILED, false));
}
