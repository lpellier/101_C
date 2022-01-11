// https://www.cs.cmu.edu/~cil/lzw.and.gif.txt
// https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
// https://en.wikipedia.org/wiki/Lossless_compression

//    PSEUDOCODE
//    Initialize table with single character strings
//    OLD = first input code
//    output translation of OLD
//    WHILE not end of input stream
//        NEW = next input code
//        IF NEW is not in the string table
//               S = translation of OLD
//               S = S + C
//        ELSE
//               S = translation of NEW
//        output S
//        C = first character of S
//        OLD + C to the string table
//        OLD = NEW
//    END WHILE

#include "../includes/giantman.h"


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
void	decode_and_print(char ** dict, char * prefix) {
	int	prefix_code = 0;

	if (content_in_dict(dict, prefix, &prefix_code)) {
		int i = 0;
		while (prefix[i]) {
			int j = 0;
			while (dict[(int)prefix[i]][j]) {
				if (dict[(int)prefix[i]][j] > 127)
					decode_and_print(dict, dict[(int)dict[(int)prefix[i]][j]]);
				else
					printf("%c", dict[(int)prefix[i]][j]);
				j++;
			}
			i++;
		}
	}
	else {
		printf("%s", prefix);
	}
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
	// printf("%s\n", file_content);
	while (file_content[i]) {
		// printf("%c", file_content[i]);
		if (content_in_dict(*dict, prefix, &prefix_code)) {
			if (!prefix) {
				prefix = malloc(sizeof(char) * 2);
				prefix[0] = file_content[i];
				prefix[1] = '\0';
			}
			else if (prefix && file_content[i] >= 0){
				tmp = prefix;
				prefix = ft_append_char(prefix, file_content[i]);
				free(tmp);
				tmp = NULL;
			}
		}
		else if (dict_index < 256) {
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
		if (file_content[i] > 127) {
			// printf("\n%d\n", file_content[i]);
			printf("%s", (*dict)[file_content[i]]);
			free(prefix);
			prefix = malloc(sizeof(char) * 2);
			i++;
			prefix[0] = file_content[i];
			prefix[1] = '\0';
		}
		i++;
	}
	printf("%s", prefix);
}

int		main(int ac, char **av) {
	unsigned char *	file_content;
	char **	dict;

	if (ac != 2 || !(file_content = get_file(av[1])))
		return (84);
	dict = NULL;
	init_dict(&dict);
	// printf("%d", (char)256-67);
	update_dict(&dict, file_content);
	// for (unsigned int i = 0; i < 256; i++) {
	// 	if (!dict[i])
	// 		break ;
	// 	printf("%3d %3s\n", i, dict[i]);
	// 	// printf("%.3d %3s\n", i, (*dict)[i]);
	// }
	// printf("%s\n", file_content);

}