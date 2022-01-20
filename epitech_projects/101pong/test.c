int ft_atoi(char * str) {
	int ret = 0;

	int i = 0;
	while (str[i]) { // 98
		ret = ret * 10;
		ret += str[i] - '0';
		i++;
	}
	return ret;
}