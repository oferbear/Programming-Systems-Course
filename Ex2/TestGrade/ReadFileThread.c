// ReadFileThread.c

// Description - This module contain the function called when new thread is created.

// Includes --------------------------------------------------------------------

#include "ReadFileThread.h"

#pragma warning(disable:4996) //in order to avoid warning about fopen being unsafe function.


// Function Definitions --------------------------------------------------------

DWORD WINAPI ReadFileThread(LPVOID lpParam)
{
	Sleep(10);								// as required
	CALC_GRADE_params_t *p_params;			// pointer for the parameters
	char path[MAX_PATH_SIZE];
	int grade = 0;
	if (NULL == lpParam) {					// check if NULL was received instead of parameter
		printf("Error declaring parameters in ReadFileThread");
		return ERR_CODE_DEFAULT;
	}
	p_params = (CALC_GRADE_params_t *)lpParam;	// cast the parameters as 'CALC_GRADE_params_t' struct we declared

	strcpy_s(path, MAX_PATH_SIZE, p_params->path);

	FILE *fptr = NULL;
	fptr = fopen(path, "r");		// open the grade file, at the path received in the parameter struct
	if (fptr == NULL) {				// check for error while opening file
		printf("Error opening file %s", path);
		return ERR_CODE_DEFAULT;
	}
	fscanf(fptr, "%d", &grade);
	p_params->grade = grade;		// update the parameter struct with the grade read from the file
	fclose(fptr);
	return SUCCESS_CODE;
}