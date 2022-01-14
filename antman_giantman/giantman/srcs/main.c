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

void	print_prefix(unsigned char ** dict, unsigned char * prefix) {
	int	i = 0;

	while (prefix[i]) {
		if (prefix[i] > 127 && dict[prefix[i]])
			print_prefix(dict, dict[prefix[i]]);
		else
			printf("%c", prefix[i]);
		i++;
	}
}

unsigned char *	insert_str(unsigned char * str, int i, unsigned char * added) {
	unsigned char * ret = malloc(sizeof(unsigned char) * (ft_ustrlen(str) + ft_ustrlen(added) + 1));
	int	str_index = 0;
	int k = 0;

	while (str[str_index] && str_index < i) {
		ret[k] = str[str_index];
		str_index++;
		k++;
	}
	int add_index = 0;
	while (added[add_index]) {
		ret[k] = added[add_index];
		k++;
		add_index++;
	}
	str_index++;
	while (str[str_index]) {
		ret[k] = str[str_index];
		k++;
		str_index++;
	}
	ret[k] = '\0';
	return ret;
} 

void	replace_prefix(unsigned char ** dict, unsigned char ** prefix) {
	int		i = 0;
	if (!dict || !(*prefix))
		return;
	while ((*prefix)[i]) {
		if ((*prefix)[i] > 127 && dict[(*prefix)[i]]) {
			replace_prefix(dict, &dict[(*prefix)[i]]);
			unsigned char * tmp = *prefix;
			*prefix = insert_str(*prefix, i, dict[(*prefix)[i]]);
			secure_free((void **)&tmp);
		}
		i++;
	}
}

void	update_dict(unsigned char *** dict, unsigned char * file_content) {
	unsigned char * prefix = NULL;
	unsigned char * tmp = NULL;
	int	prefix_code = 0;
	int	i = 1;
	int	dict_index = 128;

	prefix = update_prefix(file_content[0]);
	while (file_content[i]) {
		if (content_in_dict(*dict, prefix, &prefix_code)) {
			tmp = prefix;
			prefix = ft_append_uchar(prefix, file_content[i]);
			secure_free((void **)&tmp);
		}
		else {
			if (dict_index < 256) {
				secure_free((void **)&(*dict)[dict_index]);
				(*dict)[dict_index] = ft_strdup(prefix);
				dict_index++;
			}
			tmp = prefix;
			i--;
			prefix = update_prefix(file_content[i]);
			secure_free((void **)&tmp);
		}
		replace_prefix(*dict, &file_content);
		i++;
	}
	print_prefix(*dict, file_content);
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