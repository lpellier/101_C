#include "encryption.h"

int	square_size(int len) {
	int size = 0;

	while (len > (size * size))
		size++;
	return size;
}

int	get_matrix_size(int len, int nbr_cols) {
	int nbr_lines = 0;

	while (len > (nbr_lines * nbr_cols))
		nbr_lines++;
	return nbr_lines;
}

void	init_matrix(int ** matrix, int lines, int cols) {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = 0;
		}
	}
}

void	free_matrix(int ** matrix, int lines) {
	for (int i = 0; i < lines; i++)
		free(matrix[i]);
	free(matrix);
}

void	print_matrix(int ** matrix, int lines, int cols) {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%5d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main(int ac, char ** av) {
	if (ac != 4)
		exit(EXIT_FAILURE);
	
	char *	msg = av[1];
	char *	key = av[2];
	// int		method = atoi(av[3]);
	
	// ENCRYPTION
	// Get key in a square matrix, smallest possible size
	int	matrix_size = square_size(strlen(key));

	int ** key_matrix = malloc(sizeof(int *) * matrix_size);
	for (int i = 0; i < matrix_size; i++)
		key_matrix[i] = malloc(sizeof(int) * matrix_size);
	init_matrix(key_matrix, matrix_size, matrix_size);
	

	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (!key[(i * matrix_size) + j])
				break ;
			key_matrix[i][j] = key[(i * matrix_size) + j];
		}
	}

	printf("Key matrix:\n");
	print_matrix(key_matrix, matrix_size, matrix_size);
	
	// Get message in a matrix; its number of columns must fit the key matrix size
	int	line_nbr = get_matrix_size(strlen(msg), matrix_size);
	int ** msg_matrix = malloc(sizeof(int *) * line_nbr);
	for (int i = 0; i < line_nbr; i++)
		msg_matrix[i] = malloc(sizeof(int) * matrix_size);

	init_matrix(msg_matrix, line_nbr, matrix_size);

	for (int i = 0; i < line_nbr; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (!msg[(i * matrix_size) + j])
				break ;
			msg_matrix[i][j] = msg[(i * matrix_size) + j];
		}
	}

	// printf("Message matrix:\n");
	// print_matrix(msg_matrix, line_nbr, matrix_size);

	// Multiply the two matrices which gives the encrypted message
	int ** result_matrix = malloc(sizeof(int *) * line_nbr);
	for (int i = 0; i < line_nbr; i++)
		result_matrix[i] = malloc(sizeof(int) * matrix_size);

	init_matrix(result_matrix, line_nbr, matrix_size);
	
	for (int i = 0; i < line_nbr; i++) {
		for (int j = 0; j < matrix_size; j++) {
			for (int k = 0; k < matrix_size; k++) {
				result_matrix[i][j] += msg_matrix[i][k] * key_matrix[k][j];
			}
		}
	}

	printf("Encrpyted message:\n");
	for (int i = 0; i < line_nbr; i++) {
		for (int j = 0; j < matrix_size; j++) {
			printf("%d ", result_matrix[i][j]);
		}
	}
	printf("\n");

	// DECRYPTION
	// Inverse key matrix

	float det = determinant(key_matrix, matrix_size);
	if (det == 0)
		printf("Since the determinant is zerp (0), therefore inverse is not possible.\n");
	else {
		float	** result_inverse = malloc(sizeof(float *) * line_nbr);
		for (int i = 0; i < line_nbr; i++)
			result_inverse[i] = malloc(sizeof(float) * matrix_size);
		float ** inverse;
		inverse = cofactor(key_matrix, matrix_size);
		for (int i = 0; i < line_nbr; i++) {
			for (int j = 0; j < matrix_size; j++) {
				for (int k = 0; k < matrix_size; k++) {
					result_inverse[i][j] += result_matrix[i][k] * inverse[k][j];
				}
			}
		}
		printf("Decrpyted message:\n");
		for (int i = 0; i < line_nbr; i++) {
			for (int j = 0; j < matrix_size; j++) {
				printf("%c", (int)result_inverse[i][j]);
			}
		}
	}

	free_matrix(key_matrix, matrix_size);
	free_matrix(msg_matrix, line_nbr);
	free_matrix(result_matrix, line_nbr);
}
