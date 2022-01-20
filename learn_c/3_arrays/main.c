#include <stdio.h>

// arrays are basically groups of variables organized with an index
// the syntax is as follows : "variable_type	variable_name[number_of_elements]"
// example : int a[5] is an array of ints that can contain 5 elements
// example : char b[10] = "azertyuiop"
// if i wanted to access a specific element of the array, i would use an index
// example : to access b's 5th element, i would write "b[4]" which is 't'
// why 4 and not 5 ? because the index in an array starts at 0, therefore for the 5th element, 0, 1, 2, 3, 4 is the fifth
// to populate my array of 5 ints, i would write
// a[0] = 10;
// a[1] = 20;
// a[2] = 30;
// a[3] = 40;
// a[4] = 50;
// i could also write
// int a[5] = {10, 20, 30, 40, 50};

int main() {
	// declare an array of ints named "grades" containing 3 elements
	// set its first value to 80
	// set its second value to 85
	// set its third value to 90
	
	int average = (grades[0] + grades[1] + grades[2]) / 3;
	printf("The average of the 3 grades is: %d\n", average);
	return 0;
}

