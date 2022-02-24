int	ft_strlen(char * str) {
	if (!str)
		return ;
	int count = 0;
	while (str[count])
		count++;
	return count;
}
