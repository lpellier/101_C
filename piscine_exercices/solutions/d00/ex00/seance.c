#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

# define BUFFER_SIZE 32

int	my_strlen(char * str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return (i);
}

void	my_putstr(char * str) {
	for (int i = 0; i < my_strlen(str); i++) {
		write(1, &str[i], 1);
	}
}

int fs_open_file(char const * filepath) {

	int fd = open(filepath, O_RDONLY | O_CREAT);

    if (fd >= 0) {
		my_putstr("SUCCESS\n");
		return (fd);
	}
	my_putstr("FAILURE\n");
	return (-1);
}

void fs_understand_return_of_read (int fd , char * buffer , int size )
{
    int char_read = read(fd, buffer, size);

    if (char_read == -1)
		my_putstr("read failed\n");
    else if (char_read == 0)
		my_putstr("read has nothing more to read\n");
    else if (char_read < size )
		my_putstr("read didn’t complete the entire buffer\n");
    else if (char_read == size)
        my_putstr("read completed the entire buffer\n");
}

void fs_cat_500_bytes ( char const * filepath) {
	int fd = fs_open_file(filepath);
	char * buf;
	if ((buf = malloc(sizeof(char) * 500 + 1)) == NULL)
		exit(1);
	buf[500] = '\0';
	fs_understand_return_of_read(fd, buf, 500);
	my_putstr(buf);
	close(fd);
}

void fs_cat_x_bytes (char const * filepath , int x)
{
    int fd = fs_open_file(filepath);
    char * buf_x;
	if ((buf_x = malloc(sizeof(char) * x + 1)) == NULL)
		exit(1);
	buf_x[x] = '\0';
	fs_understand_return_of_read(fd, buf_x, x);
	my_putstr(buf_x);
    close(fd);
}

int returnLineInBuffer(char * str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\n')
        	return 1;
        i++;
    }
    return 0;
}


int isThereN(char * str) {
    int i = 0;

    for (; str[i] != '\0' && str[i] != '\n'; i++) {}

	return (i);
}

char *appendToStr(char *s1, char *s2) {
    char *s3;

	if (my_strlen(s2) != isThereN(s2))
		s3 = malloc(sizeof(char) * my_strlen(s1) + isThereN(s2) + 2);
    else
    	s3 = malloc(sizeof(char) * my_strlen(s1) + isThereN(s2) + 1);
    if (s3 == NULL)
        return (NULL);
    
    for (int i = 0; s1[i] != '\0'; i++)
	    s3[i] = s1[i];
    for (int i = 0; s2[i] != '\0' && s2[i] != '\n'; i++)
        s3[i + my_strlen(s1)] = s2[i];
	if (my_strlen(s2) != isThereN(s2)) {
		s3[my_strlen(s1) + isThereN(s2)] = '\n';	
		s3[my_strlen(s1) + isThereN(s2) + 1] = '\0';
	}
	else
		s3[my_strlen(s1) + isThereN(s2)] = '\0';
    return s3;
}

void fs_print_first_line(char const * filepath) {
	int fd = fs_open_file(filepath);

	char * total_read = malloc(sizeof(char) * 1);
	total_read[0] = '\0';
	while (returnLineInBuffer(total_read) == 0) {
		char * buf;
		if ((buf = malloc(sizeof(char) * BUFFER_SIZE + 1)) == NULL)
			exit(1);
		buf[BUFFER_SIZE] = '\0';
		fs_understand_return_of_read(fd, buf, BUFFER_SIZE);
		char * tmp = total_read;
		total_read = appendToStr(tmp, buf);
		free(tmp);
		tmp = NULL;
		free(buf);
		buf = NULL;
	}
	my_putstr(total_read);
	close(fd);
}


int main(void) {
	// fs_cat_500_bytes("subject.README");
	// fs_cat_x_bytes("subject.README", 50);
	fs_print_first_line("subject.README");
}
