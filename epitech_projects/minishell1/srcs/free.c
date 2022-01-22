#include "../includes/minishell1.h"

void	secure_free(void ** ptr) {
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	free_info(t_info * info) {
	secure_free((void **)&info->prompt);

	if (info->path) {
		for (int i = 0; info->path[i]; i++)
			secure_free((void **)&info->path[i]);
		secure_free((void **)&info->path);
	}

	if (info->cmd) {
		for (int i = 0; info->cmd; i++)
			secure_free((void **)&info->cmd);
		secure_free((void **)&info->cmd);
	}

	secure_free((void **)&info);
}
