// TestGrade.h

// This header consists the function declerations for all the functions used in the project, and their documentation.

#pragma once

#include "HardCodedData.h"
#include <windows.h>
#include <math.h>



#ifndef __FUNCTION_H__
#define __FUNCTION_H__


// Types -----------------------------------------------------------------------

/* struct for thread parameters
	-> char path[] - path of file to be opened, and grade to be read from. initialized before the thread starts.
	-> int grade - integer for the grade read. updated only after reading the grade from the file.
*/
typedef struct
{
	char path[MAX_PATH_SIZE];
	int grade;
} CALC_GRADE_params_t;


// Function Declarations -------------------------------------------------------

/*
This function extracts the id number from the path given as argument. called at the start of the program.
Input:  char *argv[] - pointer to command line arguments
		char *id_number - id number will be written in this variable
		int *return_code - pointer to return code, if theres error in the function update it to ERR_CODE_DEFAULT
Output: int, success or error code
*/
int extract_id_number(char *argv[], char *id_number, int *return_code);

/*
This function generates the parameters for the threads.
Input:  CALC_GRADE_params_t *p_thread_params - pointer to the parameters array, where each element is struct CALC_GRADE_params_t
		char *id_number - pointer to the id number
		char *argv[] - pointer to command line arguments
Output: void
*/
void generate_parameters(CALC_GRADE_params_t *p_thread_params, char *id_number, char *argv[]);

/*
This function generates the path for the exercises, based on the counter received.
Input:  char *exercise_path - the exercise file path will be written to this variable (pointer to that variable)
		char *argv[] - pointer to command line arguments
		int counter - number of ex__.txt file, the path will be created according to that variable
Output: void
*/
void generate_exercise_path(char *exercise_path, char *argv[], int counter);

/*
This function generates the path for the files we must open, which aren't exercise files.
Input:  char *other_path - the file path will be written to this variable (pointer to that variable)
		char *argv[] - pointer to command line arguments
		char *suffix - pointer to the suffix, filename to be opened
Output: void
*/
void generate_other_path(char *other_path, char *argv[], char *suffix);

/*
This function creates threads and waits for them to end. than saves their result from their parameter and closes the handle.
Input:  HANDLE *p_thread_handles - pointer to the thread handles array
		DWORD *p_thread_ids - pointer to the thread ids array
		CALC_GRADE_params_t *p_thread_params - pointer to the thread parameters array
		int *original_grades - pointer to array which will hold the grades read by the thread, this function updates this array
		int *return_code - pointer to return code, if theres error in the function update it to ERR_CODE_DEFAULT
Output: int, success or error code
*/
int create_threads(
	HANDLE *p_thread_handles,
	DWORD *p_thread_ids,
	CALC_GRADE_params_t *p_thread_params,
	int *original_grades,
	int *return_code
);

/*
This function creats a thread.
Input:  LPTHREAD_START_ROUTINE p_start_routine - function to be called in the new thread created
		LPVOID p_thread_parameters - pointer to parameters for the new thread, only one is permitted so we send struct
		LPDWORD p_thread_id - pointer for thread id to be written
Output: void, creates thread
*/
static HANDLE CreateThreadSimple(
	LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id
);

/*
This function calculates the final grade based on the formula given in the project assignment.
Input:  int *original_grades - pointer to the array which holds all the grades read from the files
		int *final_grade - pointer to variable where the final grade will be stored, this function updates it
Output: void
*/
void calculate_grade(int *original_grades, int *final_grade);

/*
This function calculates the average grade of the exercises, without the 2 worst grades.
Input:  int *original_grades - pointer to the array which holds all the grades read from the files
		float *exercise_grade - pointer to variable where the exercises grade will be stored, this function updates it
Output: void
*/
void calculate_exercise_grade(int *original_grades, float *exercise_grade);

/*
This function is used to sort an array, where the worst grades are at the end of the array. number of worst grades is determined by 'howmany'.
Input:  int *arr - pointer to array to be sorted
		int howmany - how many smallest numbers we want to move to the end of the array
		int stop_index - max index of the array to be counted in the sort
Output: void
*/
void find_smallest(int *arr, int howmany, int stop_index);

/*
This function opens the final grade file, and writes the final grade to it.
Input:  int *grade - pointer to the final grade int
		char *id_number - pointer to the id number string
		char *argv[] - pointer to command line arguments
		int *return_code - pointer to return code, if theres error in the function update it to ERR_CODE_DEFAULT
Output: int, success or error code
*/
int create_final_file(int *grade, char *id_number, char *argv[], int *return_code);


#endif // __FUNCTION_H__
