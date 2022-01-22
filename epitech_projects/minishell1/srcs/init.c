#include "../includes/minishell1.h"

void	init_envp(t_info * info, char ** envp) {
	info->env_variables = envp;
}

void	init_path(t_info * info, char ** envp) {
	char	**tmp;

	for (int i = 0; envp[i]; i++) {
		if (!ft_strncmp(envp[i], "PATH", 4)) {
			tmp = ft_split(envp[i], '=');
			if (tmp[1])
				info->path = ft_split(tmp[1], ':');
			if (tmp) {
				for (int j = 0; tmp[j]; j++) {
					secure_free((void **)&tmp[j]);
				}
				secure_free((void **)&tmp);
			}
		}
	}
}

int		init_info(t_info ** info, char ** envp) {
	*info = malloc(sizeof(t_info));

	(*info)->env_variables = NULL;
	(*info)->path = NULL;
	(*info)->cmd = NULL;
	(*info)->prompt = malloc(sizeof(char) * (3 + 1));
	(*info)->prompt[0] = '$';
	(*info)->prompt[1] = '>';
	(*info)->prompt[2] = ' ';
	(*info)->prompt[3] = '\0';

	(*info)->error_code = SUCCESS;
	(*info)->exit_status = 0;
	(*info)->shell_running = true;

	// ? Init envp variables
	init_envp((*info), envp);
	// ? Init path
	init_path((*info), envp);
	return (SUCCESS);
}
