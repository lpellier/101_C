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
//            add P + C to the string table
//          P = C
//     END WHILE
//     output code for P 

#include "../includes/antman.h"

unsigned char *	get_file(char * file_path) {
	int	fd = open(file_path, O_RDONLY);
	unsigned char	buffer;
	unsigned char *	ret;
	unsigned char *	tmp;

	if (fd == -1)
		return NULL;
	ret = NULL;
	while (read(fd, &buffer, 1)) {
		if (!ret) {
			ret = malloc(sizeof(unsigned char) * 2);
			ret[0] = buffer;
			ret[1] = '\0';
		}
		else {
			tmp = ret;
			ret = ft_append_uchar(ret, buffer);
			free(tmp);
			tmp = NULL;
		}
	}
	return (ret);
}

void	init_dict(unsigned char *** dict) {
	(*dict) = malloc(sizeof(unsigned char *) * 256);

	for (unsigned int i = 0; i < 128; i++) {
		(*dict)[i] = malloc(sizeof(unsigned char) * 2);
		(*dict)[i][0] = (unsigned char)i;
		(*dict)[i][1] = '\0';
	}
	for (unsigned int i = 128; i < 256; i++)
		(*dict)[i] = NULL;

}

int		content_in_dict(unsigned char ** dict, unsigned char * prefix, int * prefix_code) {
	int		i;

	i = 0;
	while (i < 256) {
		if (!dict[i])
			return (false);
		else if (!ft_strcmp(dict[i], prefix)) {
			if (prefix_code)
				*prefix_code = i;
			return (true);
		}
		i++;
	}
	return (false);
}

unsigned char * update_prefix(unsigned char c) {
	unsigned char * ret = malloc(sizeof(unsigned char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

void	secure_free(void ** ptr) {
	if (*ptr) {
		free(*ptr);
		*ptr = NULL;
	}
}

int		next_is_code(unsigned char ** dict, unsigned char * file_content, int i) {
	unsigned char * prefix;
	i--;
	prefix = update_prefix(file_content[i]);
	if (content_in_dict(dict, prefix, NULL)) {
		i++;
		prefix = ft_append_uchar(prefix, file_content[i]);
		if (content_in_dict(dict, prefix, NULL))
			return true;
	}
	return false;
}

void	update_dict(unsigned char *** dict, unsigned char * file_content) {
	unsigned char * prefix = NULL;
	unsigned char * tmp = NULL;
	int	prefix_code = 0;
	int	i = 1;
	int	dict_index = 128;
	int _bool = false;

	prefix = update_prefix(file_content[0]);
	printf("%s", prefix);
	while (file_content[i]) {
		if (content_in_dict(*dict, prefix, &prefix_code)) {
			if (prefix_code > 127) {
				printf("%c", (unsigned char)prefix_code);
				_bool = true;
			}
			tmp = prefix;
			prefix = ft_append_uchar(prefix, file_content[i]);
			secure_free((void **)&tmp);
		}
		else {
			if (dict_index < 256) {
				(*dict)[dict_index] = ft_strdup(prefix);
				dict_index++;
			}
			if (prefix_code <= 127) {
				if (_bool) {
					if (!next_is_code(*dict, file_content, i))
						printf("%s", prefix);
					else {
						size_t j = 0;
						while (j < ft_ustrlen(prefix) - 1) {
							printf("%c", prefix[j]);
							j++;
						}
					}
					_bool = false;
				}
				else if (!next_is_code(*dict, file_content, i))
					printf("%s", prefix + 1);
			}
			tmp = prefix;
			i--;
			prefix = update_prefix(file_content[i]);
			secure_free((void **)&tmp);
		}
		i++;
	}
	printf("%s", prefix);
}

int		main(int ac, char **av) {
	unsigned char *	file_content;
	unsigned char **	dict;

	if (ac != 2 || !(file_content = get_file(av[1])))
		return (84);
	dict = NULL;
	init_dict(&dict);
	update_dict(&dict, file_content);
	printf("\n");
	// for (unsigned int i = 128; i < 256; i++) {
	// 	if (!dict[i])
	// 		break ;
	// 	// printf("%s\n", dict[i]);
	// 	printf("%.3d %3s\n", i, (dict)[i]);
	// }

}