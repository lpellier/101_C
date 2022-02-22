#include <stdio.h>

// functions are sub programs
// they will take either a fixed or variable amount of arguments
// they will return either one value or no value

// in c, arguments are copied by value to functions, which means that we cannot change the arguments
// to affect their value outside of the function
// to do that, we must use pointers (for later)

// functions use the following syntax
// int	foo(int bar) {
// 		code goes here
//		return bar * 2;
// }
//
// int	main() {
// 		foo(1);
// }
//
// the function foo we defined receives one argument, which is bar
// the function receives an integer, multiplies it by two and returns the result
// to execute the function foo, with 1 as the argument bar, we use the following syntax:
// foo(1);

// functions must be first defined before they are used in the code

// to write a function that returns no value, we use the keyword "void"
// void		moo() {
// 		code goes here, and function does not return a value
// }

// Write a function called "print_big" which receives one argument (an integer) and prints the line
// "x is big" (where x is the argument) if the argument given to the function is a number bigger than 10
// don't forget to add a newline at the end of the printf string


int main() {
	int array[] = { 1, 11, 2, 22, 3, 33 };
	int i;
	for (i = 0; i < 6; i++) {
		print_big(array[i]);
	}
	return 0;
}