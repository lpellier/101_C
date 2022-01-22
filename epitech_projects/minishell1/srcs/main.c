#include "../includes/minishell1.h"

/**
 * @brief // ? minishell1 : recreate a UNIX command interpreter
 // ? reference shell is TCSH
 * 
 * @details // ! Display a prompt : "$>" or current directory
 * @details // ! Validated by a newline
 * @details // ! no pipes or redirections
 * @details // ! handle signals (^C, ^D (display "exit"))
 * @details // ! executables are those found in PATH (get env)
 * @details // ! errors must display appropriate message (refer to tcsh) in stderr
 * @details // ? built-ins : 
 // ! 			- cd : 0-1 argument
 	// !			- if used with no arguments : go to $HOME, if $HOME unset then don't change directory
 	// !			- if used with one argument : absolute path name (starts with "/") otherwise relative path 
 	// !			- if used with argument "-" : changes to previous directory ($PWD, $OLDPWD)
 	// !			- return codes : 0 (success) ; 1 (no $HOME, no $OLDPWD, search failed) ; 2 (incorrect option, too many arguments)
 
 // !			- setenv : 0-2 arguments
 	// !			- if used with no arguments : prints the name and values of all environment variables
 	// !			- if used with one argument : sets environment variable to the null string
 	// !			- if used with two arguments : sets environment variable to value
 	// !			- return codes : 0 (success) ; 1 (too many arguments)
 // !			- unsetenv : 1 argument
 	// !			- if used with one argument : removes all environment variables whose names match pattern
 	// !			- return codes : 0 (success) ; 1 (too few arguments)
 // !			- env : 0 argument
 	// !			- if used with no arguments : prints the name and values of all environment variables
 	// !			- return codes : 0 (success) ; 1 (too many arguments)
 // !			- exit : 0-1 argument
 	// !			- is used with no arguments : exits shell with exit status of last command run
 	// !			- if used with one argument : exits shell with exit status (exit_status % 255)
 	// !			- return codes : see above

 // ? Authorized functions
 // ? malloc, free, exit, opendir
 // ? readdir, closedir, getcwd, chdir
 // ? fork, stat, lstat, fstat
 // ? open, close, getline, strtok
 // ? strtok_r, read, write, execve
 // ? access, isatty, wait, waitpid
 // ? wait3, wait4, signal, kill
 // ? getpid, strerror, perror, strsignal
 * 
 * @return // ? appropriate exit status
 */

void	display_prompt(t_info * info) {
	ft_putstr(STDOUT, info->prompt);
}

void	handle_signal(int signal) {
	if (signal == SIGINT || signal == SIGQUIT)
		g_signal = 1;
}

int 	main(int argc, char ** argv, char ** envp) {
	t_info *	info;
	bool		error;

	(void)argv;
	info = NULL;
	error = false;
	// ? Check for errors
	if ((error |= check_errors(argc)))
		exit(print_error(error, false));

	// ? Init info struct
	init_info(&info, envp);

	// signal(SIGINT, handle_signal);
	// signal(SIGQUIT, handle_signal);

	// ? Infinite loop
	while (info->error_code == SUCCESS && info->exit_status == RUNNING) {
		// ? Display prompt
		display_prompt(info);
		// ? Wait for user input
		error |= read_input(info);
		if (info->cmd) {
			// ? Execute command
			// if ((error |= execute_cmd(info)))
				// print_error(error);
			// ? Free command
			for (int i = 0; info->cmd[i]; i++)
				secure_free((void **)&info->cmd[i]);
			secure_free((void **)&info->cmd);
		}
		if (error)
			info->error_code = EXIT_FAILURE;
	}
	// ? Free info struct
	ft_putstr(1, "exit\n");
	error = info->exit_status;
	free_info(info);

	exit(error);
}