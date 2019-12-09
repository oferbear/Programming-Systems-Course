// main.c

/*
Authors – 
	Moran Idan - 315239079
	Ofer Bear - 207943366
Project - Son
Description - This project calculates the result of a simple math pharse, and return the answer as the return value.
*/

// Includes --------------------------------------------------------------------

#include "HardCodedData.h"
#include "functions.h"
#include <stdio.h>

// Function Definitions --------------------------------------------------------

int main(int argc, char *argv[]) {
	int return_code = ERR_CODE_DEFAULT;			// initalize return code with default negative code
	if (check_arguments(&return_code, argc) != ERR_CODE_DEFAULT) {		// check if theres enough arguments
		return return_code;
	}
	int first_element = 0, second_element = 0;		// declare 2 integers, for storing the 2 elements recieved in the simple phrase
	parse_numbers(argv, &first_element, &second_element);	// parse the expression recieved, and store the elemnts in equivelent variables
	return_code = calc_equation(argv, first_element, second_element);	// calculate the result of the expression given, and store the result in return_code
	return return_code;
}