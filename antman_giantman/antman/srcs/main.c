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

void	decode_and_print(char ** dict, char * prefix) {
	int	i = 0;
	while (prefix[i]) {
		int j = 0;
		while (dict[(int)prefix[i]][j]) {
			if (dict[(int)prefix[i]][j] > 127)
				decode_and_print(dict, dict[(int)prefix[i]]);
			else
				printf("%c", dict[(int)prefix[i]][j]);
			j++;
		}
		i++;
	}
}

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

void	init_dict(char *** dict) {
	(*dict) = malloc(sizeof(char *) * 256);

	for (unsigned int i = 0; i < 128; i++) {
		(*dict)[i] = malloc(sizeof(char) * 2);
		(*dict)[i][0] = (char)i;
		(*dict)[i][1] = '\0';
		// printf("%.3d %3s\n", i, (*dict)[i]);
	}
	for (unsigned int i = 128; i < 256; i++)
		(*dict)[i] = NULL;

}

int		content_in_dict(char ** dict, char * prefix, int * prefix_code) {
	int		i;

	if (!prefix)
		return true;
	i = 0;
	while (i < 256) {
		if (!dict[i])
			return (false);
		else if (!ft_strcmp(dict[i], prefix)) {
			*prefix_code = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	update_dict(char *** dict, unsigned char * file_content) {
	char *	prefix;
	char *	tmp;
	int		i;
	int		prefix_code;
	int		dict_index;

	tmp = NULL;
	prefix = NULL;
	i = 0;
	prefix_code = 0;
	dict_index = 128;
	while (file_content[i]) {
		if (content_in_dict(*dict, prefix, &prefix_code)) {
			if (!prefix) {
				prefix = malloc(sizeof(char) * 2);
				prefix[0] = file_content[i];
				prefix[1] = '\0';
			}
			else {
				tmp = prefix;
				prefix = ft_append_char(prefix, file_content[i]);
				free(tmp);
				tmp = NULL;
			}
			if (prefix_code > 127) {
				printf("%c", prefix_code);
				free(prefix);
				prefix = malloc(sizeof(char) * 2);
				prefix[0] = file_content[i];
				prefix[1] = '\0';
			}
		}
		else if (dict_index < 256){
			(*dict)[dict_index] = ft_strdup(prefix);
			dict_index++;
			// decode_and_print(*dict, prefix);
			printf("%s", prefix);
			free(prefix);
			prefix = malloc(sizeof(char) * 2);
			prefix[0] = file_content[i];
			prefix[1] = '\0';
		}
		else {
			// decode_and_print(*dict, prefix);
			printf("%s", prefix);
			free(prefix);
			prefix = malloc(sizeof(char) * 2);
			prefix[0] = file_content[i];
			prefix[1] = '\0';	
		}
		// else
		// 	printf("%s", prefix);
		i++;
	}
}

int		main(int ac, char **av) {
	unsigned char *	file_content;
	char **	dict;

	if (ac != 2 || !(file_content = get_file(av[1])))
		return (84);
	dict = NULL;
	init_dict(&dict);
	update_dict(&dict, file_content);
	// for (unsigned int i = 0; i < 256; i++) {
	// 	if (!dict[i])
	// 		break ;
	// 	printf("%s\n", dict[i]);
	// 	// printf("%.3d %3s\n", i, (*dict)[i]);
	// }
	// printf("%s\n", file_content);

}