#include <stdarg.h>
#include <unistd.h>
// #include <>

void ft_putchar(int c) {
	write(1, &c, 1);
}

int ft_printf(const char * format, ...) {
	va_list args;

	va_start(args, format);

	// d, s, x
	for (int i = 0; format[i]; i++) {
		if (format[i] == '%') {
			i++;
			if (format[i] && format[i] == '%')
				ft_putchar('%');
			else if (format[i] && format[i] == 's') {
				char * str = va_arg(args, char *);
				ft_putstr(str);
			}
			else if (format[i] && format[i] == 'd') {
				int n = va_arg(args, int);
				ft_putnbr(n);
			}
			else if (format[i] && format[i] == 'x') {
				int n = va_arg(args, int);
				ft_puthexa(n);
			}			
		}
		else {
			ft_putchar(format[i]);
		}
	}

	va_end(args);
}

int main() {
	ft_printf("dsifhisdh%ddsofjlsduflulsi%x", 15, 42);
}