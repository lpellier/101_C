#include <stdio.h>

// "for" loops allow to create a loop - a block of code that runs multiple times until a condition is met
// they require an iterator variable, usually named "i"
// they also require a condition to end the loop
// and need a way to increase the iterator
//
// a "for" loop follows the syntax :
// for (init; condition; increment) {
//	// code
// }
//
// example :
// for (int i = 0; i < 5; i++) {
//	printf("%d\n", i);
// }
// this loop will print numbers 0 through 4
//
// we can use "for" loops to iterate over array values
// lets say i have an array named "grades" of 10 ints and i want to calculate the sum of its contents :
// int grades[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// int sum = 0;
// for (int i = 0; i < 10; i++) {
//	sum += grades[i];
// }
//
// printf("Sum of the array is %d\n", sum);

int main() {
	int factorial = 1;
	// declare an array of ints named "array" containing values 1 through 10
	
	// use a for loop to multiply the variable "factorial" with every single value of the array
	
	printf("10! (factorial) is %d.\n", factorial);
}
