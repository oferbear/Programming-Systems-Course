// HardCodedData.h

// This header consists of the constat numbers and strings in the project

#pragma once

// Constants -------------------------------------------------------------------

#define MAX_ID_LENGTH 9						// id number length
#define NUM_THREADS 13						// number of threads in the project
#define NUM_EXERCISES 10					// number of exercises
#define MAX_PATH_SIZE 48					// max path size, based on the assumption that the foldar name length is 5 max
#define MAX_EXERCISE_SUFFIX_LEN 11			// max size for the exercise files suffix
#define MIDTERM_INDEX 10					// index of midterm in the original_grades array
#define TEST_INDEX 11						// index of testA in the original_grades array
#define THREAD_TIMEOUT 4000					// timeout for threads
#define NUM_SMALLEST_GRADES_TO_IGNORE 2		// how many exercise grades we want to ignore, smallest of them
// string constants, for creating file pathes
#define EX_PREFIX "/ex"
#define SUFFIX ".txt"
#define MIDTERM "/midterm.txt"
#define TESTA "/moedA.txt"
#define TESTB "/moedB.txt"
#define FINAL_FILE "/final_"
static const int ERR_CODE_DEFAULT = -1;		// default error code. when undifined error occurs, this error code will be returned
static const int SUCCESS_CODE = 0;			// default success code