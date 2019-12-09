// functions.h

// this header consists the function declerations for all the functions used in the project, and their documentation.

#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__


// Function Declarations -------------------------------------------------------

/*
This function checks if we received exactly one argument.
If not, we update the return code to specified default errors, and main handles the error.
Input:  int *return_code - pointer to the return code integer
		int argc - number of parameters the program called with
Output: int, return code for the program
*/
int check_arguments(int *return_code, int argc);

/*
This function parse the simple-phrase received as argument, and store the 2 elements (numbers) in designated variables.
Input:  char *argv[] - pointer to the arguments array
		int *first_element - pointer to the first number in the phrase
		int *second_element - pointer to the second number in the phrase
Output: void
*/
void parse_numbers(char *argv[], int *first_element, int *second_element);

/*
This function calculates the result of the simple phrase, according to the operand in the simple-phrase received.
Input:  char *argv[] - pointer to the arguments array
		int first_element - the first element in the phrase, as an integer
		int second_element - the second element in the phrase, as an integer
Output: int, the result of the calculation
*/
int calc_equation(char *argv[], int first_element, int second_element);

/*
This function receives a 32 bytes long string (including NULL terminator), and initialize it with '\0', to indicate its empty.
Input:  char equation[] - string with 32 bytes of memory allocated
Output: void
*/
void initialize_zeros(char equation[]);


#endif // __FUNCTION_H__
