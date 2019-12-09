// functions.c

// Description - This module provides functions and tools for main.c

// Includes --------------------------------------------------------------------

#include "functions.h"
#include "HardCodedData.h"
#include <stdio.h>

// Function Definitions --------------------------------------------------------

int check_arguments(int *return_code, int argc) {
	//checking input parameters:
	//only one parameter is allowed
	if (argc < 2) {
		printf("ERROR: Not enough input arguments");
		*return_code = ERR_CODE_NOT_ENOUGH_ARGUMENTS;
	}
	if (argc > 2) {
		printf("ERROR: Too many input arguments");
		*return_code = ERR_CODE_TOO_MANY_ARGUMENTS;
	}
	if (*return_code != ERR_CODE_DEFAULT) {
		return *return_code;
	}
	else{
		return ERR_CODE_DEFAULT;
	}
}


void parse_numbers(char *argv[], int *first_element, int *second_element) {
	char equation[MAX_INPUT_LENGTH];
	initialize_zeros(&equation);		// initialize equation with '\0's
	strcpy(equation, argv[1]);
	char delim[] = "+*";				// possible opernads
	char *pnum1 = strtok(equation, delim);		// split equation by one of the possible operands, save the pointer to the first element
	*first_element = atoi(pnum1);				// atoi converts string into integer
	char *pnum2 = strtok(NULL, delim);			// save the pointer of the second element
	*second_element = atoi(pnum2);
}


int calc_equation(char *argv[], int first_element, int second_element) {
	if (strchr(argv[1], '*') == NULL) {		// if the original pharse doesnt contain '*', its an addition 
		return first_element + second_element;
	}
	else {
		return first_element * second_element;	// else, its multiplication
	}
}


void initialize_zeros(char equation[]) {
	for (int i = 0; i < MAX_INPUT_LENGTH; i++) {       //  Loop over 32 cells
		equation[i] = '\0';
	}
}