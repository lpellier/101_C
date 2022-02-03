#include <stdio.h>

// while loops are similar to for loops, with less functionality
// a while loop continues executing the while block as long as the condition in the while remains true

// the following code will execute exactly ten times:
// int n = 0;
// while (n < 10) {
// 	n++;
// }

// while loops can execute infinitely if the condition given always evaluates as true
// while (1 == 1) {				while (1) {
// 		code goes here				code goes here
// }							}

// there exists loop directives that are used with all loops in c
// the "break" directive stops the loop, even if the condition is still true
// int n = 0;
// while (1) {
// 	if (n == 15)
// 		break;
//	n++;
// }
// break here will ensure the loop is stopped after 15 loops

// the "continue" directive skips the current iteration of the loop
// int n = 0;
// while (n < 10) {
// 	n++;
// 	if (n % 2 == 0)
// 		continue; // goes back to the start of the loop
// 	printf("%d ", n);
// }


// the array variable consists of a sequence of ten numbers
// inside the while loop, you must write two if conditions :
// if the number about to be printed is less than 5, don't print it
// if the number about to be printed is greated that 10, don't print it and stop the loop
int main() {
	int array[] = {1, 7, 4, 5, 9, 3, 5, 11, 6, 3, 4};
    int i = 0;

    while (i < 10) {
        /* your code goes here */

        printf("%d\n", array[i]);
        i++;
    }

    return 0;
}