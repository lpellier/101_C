#include <stdio.h>

// strings are arrays of character variables
// there are multiple ways of initializing a string, example :
// char * name = "John"
// char name[] = "John"
// the empty brackets tell the compiler to calculate the site of the array automatically
// char name[5] = "John" -> this is the same

// "John" is 4 characters long, but we indicated it's size to be 5
// Why is that ? Because when working with strings, it's important to reserve
// one space at the end for a special character that acts like a period '.' at the end of a sentence
// it lets the compiler know that the string is over
// this character is '\0' -> EXTREMELY IMPORTANT

// some important string related functions : strlen, strcmp, strcat
// strlen takes a string as argument and returns its size
// strncmp takes two strings as arguments, it will compare the two strings 
// and check if there is a difference or not
// strncat takes two strings as arguments and adds the second string at the end of the first one


int main() {
	// declare a string named "first_name" with the value "John" using the pointer notation
	// declare a string named "last_name" with the value "Smith" using the local array notation

	char name[100];
	name[0] = '\0';
	strcat(name, first_name);
	strcat(name, last_name);
	printf("%s\n", name);
}