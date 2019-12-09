// main.c

/*
Authors –
	Moran Idan - 315239079
	Ofer Bear - 207943366
Project - TestGrade
Description - This project calculats the grade of indiviual student, given the path for his grades folder
*/

// Includes --------------------------------------------------------------------

#include "HardCodedData.h"
#include "TestGrade.h"
#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS /* to suppress compiler warnings (VS 2010 ) */

/*
In this entire project, we check for errors in each function that might fail.
If there's a failure, we update the return code and use the 'goto' function to the end of main.c.
Theres only 1 exit in this project, and its via the final return in main.c.
*/


// Function Definitions --------------------------------------------------------

int main(int argc, char *argv[]) {
	Sleep(10);
	int return_code = 0;					// initialize error code
	int final_grade = 0;					// initialize veriable for final grade
	int original_grades[NUM_THREADS];		// array to store all grades read from the files
	char id_number[MAX_ID_LENGTH + 1];		// id number string
	HANDLE p_thread_handles[NUM_THREADS];	// array for thread handles
	DWORD p_thread_ids[NUM_THREADS];		// array for thread id's
	CALC_GRADE_params_t *p_thread_params;	// array for thread parameters struct
	p_thread_params = (CALC_GRADE_params_t *)calloc(NUM_THREADS, sizeof(CALC_GRADE_params_t)); // allocate memory for thread parameters
	if (NULL == p_thread_params) {			// cheack if memery allocation was successful
		printf("Error when allocating memory");
		return_code = ERR_CODE_DEFAULT;
		goto EXIT;
	}

	// extract the id number from the path provided
	if (extract_id_number(argv, &id_number, &return_code) < 0) {
		goto EXIT;
	}

	// generate all the required parameters for the threads to run
	generate_parameters(p_thread_params, &id_number, argv);

	// create all threads and wait for them to finish running, store all grades received from the threads to 'original_grades'
	if (create_threads(p_thread_handles, p_thread_ids, p_thread_params, original_grades, &return_code) < 0) {
		goto EXIT;
	}

	// calculate the final grade based on the formula provided, given the original_grades array
	calculate_grade(original_grades, &final_grade);

	// create the final file and write the final grade to it
	if (create_final_file(&final_grade, &id_number, argv, &return_code) < 0) {
		goto EXIT;
	}

EXIT:
	free(p_thread_params);		// free memory
	return return_code;
}