// functions.c

// Description - This module provides functions and tools for main.c

// Includes --------------------------------------------------------------------

#include "functions.h"
#include "HardCodedData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#pragma warning(disable:4996) //in order to avoid warning about fopen being unsafe function.

// Function Definitions --------------------------------------------------------


int open_file(char *argv[]) {     
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp, "Computation.txt", "w");
	if (err == 0) {
		fputs(argv[1], fp);
		fputs("\n", fp);
		fclose(fp);
	}
	else {
		printf("Failed to open file.\n");
		return ERR_CODE_OPEN_FILE_FAIL;
	}
	return 0;
}


void find_simple_phrase_indx(int *start, int *end, char *equation) {  
	int temp;
	while (equation[*end] != ')') {		// while we havent reached the end of phrase
		if (equation[*start] == '('){	// start of phrase
			while (equation[*end] != ')') {		// if we havnt reached simple-pharse end
				if (equation[*end] == '(') {	// if found another start, restart searching for an end
					temp = *start;
					*start = *end - 1;
					*end = temp + 1;
					break;
				}
				(*end)++;
			}
		}
		(*start)++;
	}
	(*end)--;

}


void ready_for_son(int start, int end, char *equation, char *phrase) {   
	strcpy_s(phrase, MAX_INPUT_LENGTH , SONS_PREFIX);	// copy 'son.exe' to the beginning of pharse
	int last_index = strlen(phrase);	// find the last index, copy to phrase from that index
	for (start; start <= end; (start)++) {	// copy the simple-pharse from equation to phrase, using the indexes start and end
		phrase[last_index] = equation[start];
		last_index++;
	}
	phrase[last_index] = '\0';
}


int calc_nupdate_file(FILE *fp, char *equation) {
	int exitcode = DEFAULT_CALL_FOR_SON;	// default error code for sons return code
	char phrase[MAX_INPUT_LENGTH];
	phrase[0] = '\0';
	while (strchr(equation, ')')) {		// while theres still simple-phrases
		int start = 0;		// index for simple-pharse start
		int end = 1;		// index for simple-pharse end
		int *pstart = &start;
		int *pend = &end;
		char *new_equation[MAX_INPUT_LENGTH];
		new_equation[0] = '\0';
		find_simple_phrase_indx(pstart, pend, equation);	// find and update the indexes for start and end
		ready_for_son(start, end, equation, phrase);	// create the string "son.exe " + the simple-pharse. 
		exitcode = CreateProcessSimpleMain(&phrase);	//send the simple-phrase to son.
		if (exitcode < 0) {
			return DEFAULT_CALL_FOR_SON;	// internal error in son, return default error code
		}
		rewrite_equation(pstart, pend, equation, &new_equation, exitcode); //replace the simple-phrase we sent to son with the answer.
		strcpy_s(equation, MAX_INPUT_LENGTH, new_equation);		// update equation
		fputs(equation, fp);		// update file
		if (strchr(equation, ')')) {
			fputs("\n", fp);
		}
	}
	return 0;
}


void rewrite_equation( int *start, int *end, char *equation, char *new_equation, int exitcode) {
	char answer[MAX_SON_INPUT];
	sprintf(answer, "%d", exitcode);	// int to string
	for (int i = 0; i < (*start-1); i++) {    // copy the part in the equation that came before the simple-phrase we sent to son. 
		new_equation[i] = equation[i];
	}
	for (int i = 0; i < strlen(answer); i++) {    // replace the simple-phrase we sent to son with his answer.  
		new_equation[(*start-1) + i] = answer[i];
	}
	int i = 0;
	while (equation[i+(*end+1)] != '\0') {     // copy the part in the equation that came after the simple-phrase we sent to son, including the \0. 
		int nev_equ_indx = i + *start + strlen(answer) - 1;
		int equ_indx = i + *end + 2;
		new_equation[nev_equ_indx] = equation[equ_indx];
		i++;
	}
}


int CreateProcessSimpleMain(char *equation)
{
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	CHAR				command[MAX_SON_INPUT];

	/*  Start the child process. */
	command[0] = '\0';
	strcpy_s(command, MAX_SON_INPUT, equation);		// create a copy of equation
	retVal = CreateProcessSimple(command, &procinfo);	// create process


	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return DEFAULT_CALL_FOR_SON;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */


	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate */
	}

	GetExitCodeProcess(procinfo.hProcess, &exitcode);

	return exitcode;


	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
}


BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; 

	return CreateProcess(NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}