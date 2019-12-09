// TestGrade.c

// Description - This module provides functions and tools for main.c

// Includes --------------------------------------------------------------------

#include "TestGrade.h"
#include "HardCodedData.h"
#include "ReadFileThread.h"
#include <stdio.h>

#pragma warning(disable:4996) //in order to avoid warning about fopen being unsafe function.

// Function Definitions --------------------------------------------------------

int extract_id_number(char *argv[], char *id_number, int *return_code) {
	char *p_path = NULL;
	p_path = (char *)malloc(strlen(argv[1]) * sizeof(char));	// allocate memory for path
	if (NULL == p_path) {		// check for error when allocating memory
		printf("Error when allocating memory");
		*return_code = ERR_CODE_DEFAULT;
		return ERR_CODE_DEFAULT;
	}
	strcpy_s(p_path, strlen(argv[1]) + 1, argv[1]);		// copy the path received from argv to new variable

	char delim[] = "_";		// split the path by this char
	char *p_part = strtok(p_path, delim);	// pointer to the splitted string
	char *p_last_part = NULL;

	while (p_part != NULL)		// find the last part when splitting by delim
	{
		p_last_part = p_part;
		p_part = strtok(NULL, delim);
	}
	strcpy_s(id_number, MAX_ID_LENGTH + 1, p_last_part);	// we take 'last_part' because the final part is NULL
	return SUCCESS_CODE;
}


void generate_parameters(CALC_GRADE_params_t *p_thread_params, char *id_number, char *argv[]) {
	char temp_path[MAX_PATH_SIZE];
	for (int i = 1; i <= NUM_EXERCISES; i++) {
		temp_path[0] = '\0';
		generate_exercise_path(&temp_path, argv, i);	// create path for ex.txt files, iterative
		strcpy_s(p_thread_params[i - 1].path, strlen(argv[1]) + MAX_EXERCISE_SUFFIX_LEN, temp_path);
	}
	generate_other_path(&temp_path, argv, MIDTERM);		// create path for midterm
	strcpy_s(p_thread_params[MIDTERM_INDEX].path, MAX_PATH_SIZE, temp_path);
	generate_other_path(&temp_path, argv, TESTA);		// create path for test A
	strcpy_s(p_thread_params[TEST_INDEX].path, MAX_PATH_SIZE, temp_path);
	generate_other_path(&temp_path, argv, TESTB);		// create path for test B
	strcpy_s(p_thread_params[TEST_INDEX + 1].path, MAX_PATH_SIZE, temp_path);
}


void generate_exercise_path(char *exercise_path, char *argv[], int counter) {
	strcpy_s(exercise_path, MAX_PATH_SIZE, argv[1]);
	char suffix[MAX_EXERCISE_SUFFIX_LEN];
	sprintf_s(suffix, MAX_EXERCISE_SUFFIX_LEN, "%s%02d%s", EX_PREFIX, counter, SUFFIX);
	strcat_s(exercise_path, MAX_PATH_SIZE, suffix);
}


void generate_other_path(char *other_path, char *argv[], char *suffix) {
	other_path[0] = '\0';
	strcpy_s(other_path, MAX_PATH_SIZE, argv[1]);
	strcat_s(other_path, MAX_PATH_SIZE, suffix);
}


int create_threads(
	HANDLE *p_thread_handles,
	DWORD *p_thread_ids,
	CALC_GRADE_params_t *p_thread_params,
	int *original_grades,
	int *return_code
) {
	int internal_return_code = SUCCESS_CODE;		// if everything works properly success code will be returned
	BOOL ret_val;

	for (int i = 0; i < NUM_THREADS; i++)			// create thread for every file
	{
		p_thread_handles[i] = CreateThreadSimple(ReadFileThread, &p_thread_params[i], &p_thread_ids[i]);	// create thread
		if (NULL == p_thread_handles[i])	// check for errors
		{
			printf("Error when creating thread: %d\n", GetLastError());
			*return_code = ERR_CODE_DEFAULT;
			internal_return_code = ERR_CODE_DEFAULT;
			for (int j = 0; j < i; j++) {		// close handles that were already opened
				ret_val = CloseHandle(p_thread_handles[j]);
				if (FALSE == ret_val)
				{
					printf("Error when closing thread: %d\n", GetLastError());
				}
			}
			return internal_return_code;		// return immediately before creating more threads
		}
	}

	DWORD wait_code;

	wait_code = WaitForMultipleObjects(NUM_THREADS, p_thread_handles, TRUE, THREAD_TIMEOUT);	// wait for threads to run
	if (WAIT_OBJECT_0 != wait_code)			// check for errors
	{
		printf("Error when waiting\n");
		*return_code = ERR_CODE_DEFAULT;
		internal_return_code = ERR_CODE_DEFAULT;
	}

	for (int j = 0; j < NUM_THREADS; j++)	// loop for saving threads output and closing their handles
	{
		original_grades[j] = p_thread_params[j].grade;
		ret_val = CloseHandle(p_thread_handles[j]);
		if (FALSE == ret_val)
		{
			printf("Error when closing thread: %d\n", GetLastError());
			*return_code = ERR_CODE_DEFAULT;
			internal_return_code = ERR_CODE_DEFAULT;
		}
	}
	return internal_return_code;
}


static HANDLE CreateThreadSimple(
	LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id
) {
	HANDLE thread_handle;

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		return NULL;		// return NULL, error will be caught in "create_threads"
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		return NULL;		// return NULL, error will be caught in "create_threads"
	}

	thread_handle = CreateThread(
		NULL,                /*  default security attributes */
		0,                   /*  use default stack size */
		p_start_routine,     /*  thread function */
		p_thread_parameters, /*  argument to thread function */
		0,                   /*  use default creation flags */
		p_thread_id);        /*  returns the thread identifier */

	if (NULL == thread_handle)
	{
		printf("Couldn't create thread\n");
	}

	return thread_handle;
}


void calculate_grade(int *original_grades, int *final_grade) {
	float exercise_grade = 0;
	calculate_exercise_grade(original_grades, &exercise_grade);		// calculate only exercise grades
	float midterm = (float)original_grades[MIDTERM_INDEX];
	if (midterm < 60) {		// check if passed
		midterm = 0;
	}
	float moedA = (float)original_grades[TEST_INDEX];
	float moedB = (float)original_grades[TEST_INDEX + 1];
	float test_grade = 0;
	if (moedB == 0) {			// check if took moed B
		if (moedA < 60) {		// check if passed
			test_grade = 0;
		}
		else {
			test_grade = moedA;
		}
	}
	else {
		if (moedB < 60) {		// check if passed
			test_grade = 0;
		}
		else {
			test_grade = moedB;
		}
	}
	*final_grade = (int)ceil(0.2*exercise_grade + 0.2*midterm + 0.6*test_grade);	// formula given in project instructions
}


void calculate_exercise_grade(int *original_grades, float *exercise_grade) {
	find_smallest(original_grades, NUM_SMALLEST_GRADES_TO_IGNORE, NUM_EXERCISES - 1);	// rearrange original_grades, smallest at the end
	for (int i = 0; i < NUM_EXERCISES - NUM_SMALLEST_GRADES_TO_IGNORE; i++) {	// take only first elemnts in count, based on how many we awnt to ignore
		if (original_grades[i] >= 60) {		// check if passed
			*exercise_grade += original_grades[i];
		}
	}
	*exercise_grade = *exercise_grade / (NUM_EXERCISES - NUM_SMALLEST_GRADES_TO_IGNORE);	// calculate final exercise grade
}

void find_smallest(int *arr, int howmany, int stop_index) {
	int smallest_index;
	int temp = 0;
	for (int j = NUM_EXERCISES - 1; j > NUM_EXERCISES - 1 - howmany; j--) {		// loop 'howmany' times, how many minimal values we want to move
		smallest_index = 0;
		for (int i = 1; i <= stop_index - (NUM_EXERCISES - j - 1); i++) {	// loop over the array values, without the ones we already moved to the end
			if (arr[i] < arr[smallest_index]) {		// find smallest values index
				smallest_index = i;
			}
		}
		// replace between the smallest value and the value at the end of the array
		temp = arr[j];
		arr[j] = arr[smallest_index];
		arr[smallest_index] = temp;
	}
}


int create_final_file(int *grade, char *id_number, char *argv[], int *return_code) {
	FILE *p_grade_file = NULL;
	char path[MAX_PATH_SIZE];
	path[0] = '\0';
	sprintf_s(path, MAX_PATH_SIZE, "%s%s%s%s", argv[1], FINAL_FILE, id_number, SUFFIX);	// create the path for final grade file
	fopen_s(&p_grade_file, path, "w");		// open final grade file
	if (p_grade_file == NULL) {				// check for errors
		printf("Error opening file %s", path);
		*return_code = ERR_CODE_DEFAULT;
		return ERR_CODE_DEFAULT;
	}
	fprintf(p_grade_file, "%d", *grade);	// write to file
	fclose(p_grade_file);					// close file
	return SUCCESS_CODE;
}