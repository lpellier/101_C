// https://www.cs.cmu.edu/~cil/lzw.and.gif.txt
// https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
// https://en.wikipedia.org/wiki/Lossless_compression

//     PSEUDOCODE
//     Initialize table with single character strings
//     P = first input character
//     WHILE not end of input stream
//          C = next input character
//          IF P + C is in the string table
//           P = P + C
//          ELSE
//            output the code for P
//          add P + C to the string table
//           P = C
//     END WHILE
//     output code for P 

#include "antman.h"

char *	get_file(char * file_path) {
	int	fd = open(file_path, O_RDONLY);
	char	buffer;
	char *	ret;
	char *	tmp;

	if (fd == -1)
		return NULL;
	ret = NULL;
	while (read(fd, &buffer, 1)) {
		if (!ret) {
			ret = malloc(sizeof(char) * 2);
			ret[0] = buffer;
			ret[1] = '\0';
		}
		else {
			tmp = ret;
			ret = ft_append_char(ret, buffer);
			free(tmp);
			tmp = NULL;
		}
	}
	return (ret);
}

void	init_dict(char *** dict) {
	(*dict) = malloc(sizeof(char *) * 4096);

	for (unsigned int i = 0; i < 128; i++) {
		(*dict)[i] = malloc(sizeof(char) * 2);
		(*dict)[i][0] = (char)i;
		(*dict)[i][1] = '\0';
		// printf("%.3d %3s\n", i, (*dict)[i]);
	}
	for (unsigned int i = 128; i < 4096; i++)
		(*dict)[i] = NULL;

}

int		content_in_dict(char ** dict, char * prefix) {
	int		i;

	if (!prefix)
		return true;
	i = 0;
	while (i < 4096) {
		if (!dict[i])
			return (false);
		else if (!ft_strcmp(dict[i], prefix))
			return (true);
		i++;
	}
}

char *	update_dict(char *** dict, char * file_content) {
	char *	encoded_content;
	char *	prefix;
	char *	tmp;
	int		i;
	int		dict_index;

	encoded_content = NULL;
	tmp = NULL;
	i = 0;
	dict_index = 128;
	while (file_content[i]) {
		if (content_in_dict(*dict, prefix)) {
			if (!prefix) {
				prefix = malloc(sizeof(char) * 2);
				prefix[0] = file_content[i];
				prefix[1] = '\0';
			}
			else {
				tmp = prefix;
				prefix = ft_append(prefix, file_content[i]);
				free(tmp);
				tmp = NULL;
			}
		}
		else {
			(*dict)[dict_index] = ft_strdup(prefix);
			dict_index++;
			free(prefix);
			prefix = NULL;
		}
		i++;
	}
	return (encoded_content);
}

int		main(int ac, char **av) {
	char *	file_content;
	char *	encoded_content;
	char **	dict;

	if (ac != 2 || !(file_content = get_file(av[1])))
		return (84);
	dict = NULL;
	init_dict(&dict);
	encoded_content = update_dict(&dict, file_content);
	for (unsigned int i = 0; i < 4096; i++) {
		if (!dict[i])
			break ;
		printf("%s\n", dict[i]);
		// printf("%.3d %3s\n", i, (*dict)[i]);
	}
	// printf("%s\n", file_content);

}