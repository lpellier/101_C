/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpellier <lpellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:21:11 by lpellier          #+#    #+#             */
/*   Updated: 2022/01/22 00:23:33 by lpellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define STDIN	0
# define STDOUT	1
# define STDERR	2

# define bool char
# define false 0
# define true 1

int		g_signal;

enum	error_codes {
	SUCCESS,
	START_FAILURE,
	TOO_FEW_ARGUMENTS,
	TOO_MANY_ARGUMENTS,
	NO_HOME,
	NO_OLDPWD,
	SEARCH_FAILED,
	EXIT_PROGRAM
};

enum	program_state {
	RUNNING,
	STOPPED
};

typedef struct	s_info {
	char **		env_variables;
	char **		path;
	char **		cmd;
	char *		prompt;

	int			error_code;
	int			exit_status;
	bool		shell_running;
}				t_info;

int		check_errors(int argc);
int		print_error(int error_code, bool error_override);
int		init_info(t_info ** info, char ** envp);
void	secure_free(void ** ptr);
void	free_info(t_info * info);

char	**ft_split(char const *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *str);
void	ft_putstr(int fd, const char * str);

int		read_input(t_info * info);
