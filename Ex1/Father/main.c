// main.c

/*
Authors –
	Moran Idan - 315239079
	Ofer Bear - 207943366
Project - Father
Description - This project calculates the result of math problem, by using sub processes of "Son.exe", and writes the result and way of solution to "computation.txt".
*/

// Includes --------------------------------------------------------------------

#include "HardCodedData.h"
#include <stdio.h>
#pragma warning(disable:4996) // in order to avoid warning about fopen being unsafe function.
#include "functions.h"

// Function Definitions --------------------------------------------------------

int main(int argc, char *argv[]) {
	int return_code = ERR_CODE_DEFAULT;		// set default return code. if the program works properly, it will change later
	return_code = open_file(argv);		// open 'computation.txt' file, if failed change error code
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp, "Computation.txt", "a");		// open 'computation.txt' in append mode
	if (err == 0) {     // if file opened successfully
		char equation[MAX_INPUT_LENGTH];		// create new variable for the original equation received
		equation[0] = '\0';
		strcpy_s(equation, sizeof equation, argv[1]);	// copy argv[1] to equation
		return_code = calc_nupdate_file(fp, equation);		// calculate the equation, and simultaneously update the file
		fclose(fp);			// close file
	}
	else {
		printf("Failed to open file.\n");
		return ERR_CODE_OPEN_FILE_FAIL;
	}
	return return_code;
}