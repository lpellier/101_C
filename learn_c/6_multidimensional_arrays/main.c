#include <stdio.h>

// multidimensional arrays are basically arrays of arrays
// example : int a[3][4] is a 2-dimensional array containing 3 arrays of 4 ints
// to visualize it :
// 	    0        1        2        3
// 0	a[0][0]  a[0][1]  a[0][2]  a[0][3]
// 1	a[1][0]  a[1][1]  a[1][2]  a[1][3]
// 2	a[2][0]  a[2][1]  a[2][2]  a[2][3]
//
// every element in an array is defined in the form a[i][j] where,
// a is the name of the array,
// i is the line number
// j is the column number
// therefore, to access the element at the 3rd column and 2nd line, i would write
// a[2][1];
//
// to populate my 2-dimensional array "a", i could write :
// int a[3][4];
// a[0][0] = 10;
// a[0][1] = 20;
// a[0][2] = 30;
// a[0][3] = 40;
// a[1][0] = 50;
// a[1][1] = 60;
// a[1][2] = 70;
// a[1][3] = 80;
// a[2][0] = 90;
// a[2][1] = 100;
// a[2][2] = 110;
// a[2][3] = 120;
// 
// or i could write :
// int a[3][4] = { {10, 20, 30, 40}, {50, 60, 70, 80}, {90, 100, 110, 120} };
//
// or to make it even clearer :
// int a[3][4] = { 
// 	{10, 20, 30, 40}, 
// 	{50, 60, 70, 80}, 
// 	{90, 100, 110, 120} 
// };

// Exercise : You are a teacher and need to calculate the average score of students for two subjects,
// Mathematics and Physics
// There are 5 students in your class
int main() {
	// declare a 2D array of ints with 2 lines and 5 columns named "grades"
	// The first line is for Mathematics, and each value for the first line is for one of the 5 students
	// set its value at first line, first column to 80
	// set its value at first line, second column to 70
	// set its value at first line, third column to 65
	// set its value at first line, fourth column to 89
	// set its value at first line, fifth column to 90

	// The second line is for Physics, and each value for the second line is for one of the 5 students
	// set its value at second line, first column to 85
	// set its value at second line, second column to 80
	// set its value at second line, third column to 80
	// set its value at second line, fourth column to 82
	// set its value at second line, fifth column to 87

	// declare a variable of type float named "average"
	
	// complete the condition for each of these for loops
	for (int i = 0; i < ; i++) {
		// set value of "average" to 0
		
		for (int j = 0; j < ; j++) {
			average += grades[i][j];
		}
		// calculate average for each subjects here

		printf("The average marks obtained in subject %d is: %.2f\n", i, average);
	}
	return 0;
}

