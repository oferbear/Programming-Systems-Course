// functions.h

// this header consists the function declerations for all the functions used in the project, and their documentation.

#pragma once
#include <stdio.h>
#include <windows.h>
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

// Function Declarations -------------------------------------------------------

/*
This function open the 'computation.txt' file. Opens new file in write mode.
Input:  char *argv[] - pointer to the arguments array
Output: int, succes/error code for openning file 
*/
int open_file(char *argv[]);

/*
This function goes over the equation and finds simple phrase indexes.
Input:  int *start - pointer to the start index of the simple-phrase
		int *end - pointer to the end index of the simple-phrase
		char *equation - an equation to fins a simple-phrase in it
Output: void
*/
void find_simple_phrase_indx(int *start, int *end, char *equation);

/*
This function gets the start and end indexs of a simple-pharse in equation and updates in a different veriable the command line executaion code for running Son with this simple-phrase.
Input:  int start - start index of the simple-phrase
		int end - end index of the simple-phrase
		char *equation - the full equation in which the simple-phrase in
		char *phrase - empty string for the simple-phrase to be written into
Output: void
*/
void ready_for_son(int start, int end, char *equation, char *phrase);

/*
This function calculates the equation, by dividing the equation into simple-phrases, and calling Son program for each one.
In every round of calculation, the function updates the output file with the latest calculation.
Input:  FILE *fp - pointer to the calculation.txt file, consisting of the method of calculation
		char *equation - the full equation received in command line argument
Output: void
*/
int calc_nupdate_file(FILE *fp, char *equation);

/*
This function takes the equation that we already calculated a simple-phrase in, and updates a new string, new equation.
the new equation will be the same as the old equation, but with the particular simple-phrase replaced with its result.
Input:  int *start - pointer to the start index of the simple-phrase
		int *end - pointer to the end index of the simple-phrase
		char *equation - the old equation, with simple-phrase in it
		char *new_eqution - pointer to the new equation variable, which will hold the updated equation
		int exitcode - the exit code received from the Son process, which hold simple-phrases solution
Output: void
*/
void rewrite_equation(int *start, int *end, char *equation, char *new_equation, int exitcode);

/*
This function handles calling for another process, and receiving its return code
Input:  char *equation - a simple-phrase string to be calculated by Son process
Output: int, Son process exit code, answer to the simple-equation
*/
int CreateProcessSimpleMain(char *equation);

/*
This function creates new process easily, without the need for all the parameters available for opening a process.
Input:  LPTSTR CommandLine - command line argument
		PROCESS_INFORMATION *ProcessInfoPtr - pointer to a struct with process information
Output: BOOL, 0 if failed, anything else for success
*/
BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr);

#endif // __FUNCTION_H__

