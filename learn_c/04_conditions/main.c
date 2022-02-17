#include <stdio.h>

// conditions are very useful in programming
// they allow you to make a choice based on the values of your variables
// 
// "if" conditions allow you to check if an expression is true of false, and execute code accordingly
// in an expression, to evaluate if two variables are equal, you would use the operator "=="
// example :
// int target = 10;
// if (target == 10) {
//	printf("Target is equal to 10\n");
// }
//
// "if" conditions are sometimes accompanied by "else" conditions
// example :
// int target = 10;
// if (target == 10) {
//	printf("Target is equal to 10\n");
// }
// else {
//	printf("Target is not equal to 10\n");
// }
//
// you could also use "else if" conditions after an "if" condition
// example :
// int target = 15;
// if (target == 10) {
//	printf("Target is equal to 10\n");
// }
// else if (target == 15) {
//	printf("Target is equal to 15\n")
// }
// else {
//	printf("Target is not equal to 10 nor 15\n");
// }
//
// in an expression, you could also check if a variable is inferior to another with the operator "<"
// or if it is superior with the operator ">"
// inferior or equal : "<="
// superior or equal : ">="
// equal to : "=="
// different than : "!="
//
// you could check multiple expressions at the same time with the operator "&&"
// example :
// if (target < 15 && target > 0) {
//	printf("Target is between 0 and 15\n");
// }
//
// you could also check if one expression is true OR an other is with the operator "||"
// example :
// if (target == 10 || target == 15) {
//	printf("Target is equal to 10 OR 15\n");
// }

void	guessNumber(int guess) {
	// This function takes an integer and checks its value
	// if the value is equal to 555, print "Correct. You guessed it!" followed by a newline
	// if the value is less than 555, print "Your guess is too low." followed by a newline
	// if the value is greater than 555, print "Your guess is too high." followed by a newline
}

int main() {
	guessNumber(500);
	guessNumber(600);
	guessNumber(555);
}

