#include <stdio.h>

// pointers are a speical type of variable that play a very VERY important role in C
// a pointer is essentially a simple integer variable which holds a memory address (!!) that points to a value,
// instead of holding the actual value itself

// the computer's memory is a sequential store of data, and a pointer points to a specific part of the memory

// string as pointers :
// char * name = "John";
// this line does three things :
// it allocates a local variable called "name", which is a pointer to a single (!) character
// it causes the string "John" to appear somewhere in the memory (when the program is executed)
// it initializes the "name" argument to point where the 'J' character resides at (which is followed
// by the rest of the string in the memory)

// the variable "name" points to the beginning of the string
// we can read its contents by "dereferencing" the pointer and iterate over each character until we find
// its null terminator '\0'

// DEREFERENCING is the act of referring to where the pointer points, instead of the memory address
// we were already dereferencing when accessing the contents of an array with the brackets []
// [0] for example, accesses the first item of the array
// and since arrays are actually pointers, accessing the first item in the array is the same as dereferencing a pointer
//
// Dereferencing a pointer is done using the asterisk operator '*'
//
// let's create two variables, an integer that holds the value 42 and a pointer that holds a pointer to the first variable
/*
 * // define a local variable "a"
 * int a = 42;
 *
 * // define a pointer variable, and point it to "a" using the & operator
 * int * pointer_to_a = &a;
 *
 * // these printf will print the same value
 * printf("%d\n", a);
 * printf("%d\n", *pointer_to_a);
 *
 * // if we modified the value of a, *pointer_to_a would also have that new value
 * a += 1;
 * printf("%d\n", a);
 * printf("%d\n", *pointer_to_a); // prints 43
 *
 * *pointer_to_a += 1;
 * printf("%d\n", a);
 * printf("%d\n", *pointer_to_a); // prints 44
 * */

// create a pointer to the local variable n called pointer_to_n, and use it to increase the value of n by one
int main() {
	int n = 10;

	/* your code goes here */

	/* testing code */
	if (pointer_to_n != &n) 
		return 1;
	if (*pointer_to_n != 11) 
		return 1;

	printf("Done!\n");
	return 0;
}
