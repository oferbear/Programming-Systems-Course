// functions.c

// Includes --------------------------------------------------------------------

#include "functions.h"
#include "HardCodedData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

//#pragma warning(disable:4996) //in order to avoid warning about fopen being unsafe function.

// Function Definitions --------------------------------------------------------

void open_student_id_file(char *main_folder_path, FILE *pfl_studentids) {
	char file_path[MAX_INPUT_LENGTH] = "\0";
	strcpy_s(file_path, MAX_INPUT_LENGTH, main_folder_path);
	char file_name_of_students_ids[] = FILE_NAME_STUDENT_IDS;
	strcat_s(file_path, MAX_INPUT_LENGTH, file_name_of_students_ids);  // creat './input/student_ids.txt'
	fopen_s(&*pfl_studentids, file_path, "r");  // open the file in read mode
}

void creat_file_path_for_student(char *student_folder_path, char *student_id, char *main_folder_path)
{
	char end_of_path[MAX_INPUT_LENGTH] = FOLDER_NAME_FOR_STUDENT;
	strcat_s(end_of_path, MAX_INPUT_LENGTH, student_id);  // creat '/grades_ID'
	strcat_s(student_folder_path, MAX_INPUT_LENGTH, main_folder_path);  //creat './input'
	strcat_s(student_folder_path, MAX_INPUT_LENGTH, end_of_path);  //creat './input/grades_ID'
}

int create_final_grades_file(char *main_folder_path) {
	FILE *pfl_finalgrades = NULL;    // creat pointer for final grades file
	char file_path[MAX_INPUT_LENGTH] = "\0";
	strcat_s(file_path, MAX_INPUT_LENGTH, main_folder_path); //creat './input'
	strcat_s(file_path, MAX_INPUT_LENGTH, FILE_NAME_FINAL_GRADES);  // creat './input/final_grades.txt'
	fopen_s(&pfl_finalgrades, file_path, "w");
	if (pfl_finalgrades != NULL) {   //check if the file opened
		fclose(pfl_finalgrades);
	}
	else {
		printf("Failed to creat final grades file.\n");
		return ERR_CODE_OPEN_FILE;
	}
	return ERR_CODE_DEFAULT;
}

int update_final_grades_file(char *student_id, char *main_folder_path) {
	FILE *pfl_finalgrades = NULL;    // creat pointer for final grades file
	char final_grades_file_path[MAX_INPUT_LENGTH] = "\0";
	strcat_s(final_grades_file_path, MAX_INPUT_LENGTH, main_folder_path);
	strcat_s(final_grades_file_path, MAX_INPUT_LENGTH, FILE_NAME_FINAL_GRADES);  //creat the path for final_grades.txt file
	fopen_s(&pfl_finalgrades, final_grades_file_path, "a");   //open the final_grades.txt file in append mode
	FILE *pfl_studentgrade;
	char final_grade_per_student_path[MAX_INPUT_LENGTH] = "\0";
	creat_file_path_for_student(final_grade_per_student_path, student_id, main_folder_path);
	strcat_s(final_grade_per_student_path, MAX_INPUT_LENGTH, FILE_NAME_STUDENT_GRADE);
	strcat_s(final_grade_per_student_path, MAX_INPUT_LENGTH, student_id);   //creat the path for grades_ID/final_ID.txt file
	strcat_s(final_grade_per_student_path, MAX_INPUT_LENGTH, TEXT_FILE_SUFFIX);
	fopen_s(&pfl_studentgrade, final_grade_per_student_path, "r");   //open the final_ID.txt file in read mode
	if (pfl_finalgrades != NULL && pfl_studentgrade != NULL) {  // if the files opened succesfuly 
		char final_grade[4] = "\0";
		fgets(final_grade, 4, pfl_studentgrade);  //copy the grade from final_ID.txt to final_grade varibel
		fputs(student_id, pfl_finalgrades);   //append the student ID  to final_grades.txt 
		fputs(" ", pfl_finalgrades);
		fputs(final_grade, pfl_finalgrades);   //append the grade from final_grade varibel to  final_grades.txt
		fputs("\n", pfl_finalgrades);
	}
	else if (pfl_finalgrades == NULL) {  //if couldnt open final_grades file return error code and print error message
		printf("Failed to open final grades file.\n");
		return ERR_CODE_OPEN_FILE;
		goto Failed_open_file;
	}
	else if (pfl_studentgrade == NULL) {   //if couldnt open final_ID file return error code and print error message
		printf("Failed to open student final grade file.\n");
		return ERR_CODE_OPEN_FILE;
		goto Failed_open_file;
	}
	fclose(pfl_finalgrades);
	fclose(pfl_studentgrade);
Failed_open_file:
	return ERR_CODE_DEFAULT;
}


void make_command_line_for_testgrade(char *student_id, char *main_folder_path, char *command) {
	strcpy_s(command, MAX_INPUT_LENGTH, CALL_TO_TEST_GRADE);
	char student_folder_path[MAX_INPUT_LENGTH] = "\0";
	creat_file_path_for_student(&student_folder_path, student_id, main_folder_path);
	strcat_s(command, MAX_INPUT_LENGTH, student_folder_path);
}

int CreateProcessSimpleMain(char *sent_main_folder_path, char *student_id)
{
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	CHAR				command[MAX_INPUT_LENGTH];	// = ("notepad.exe ../log.txt"); /* <ISP> TCHAR is a win32  */
													/* generic char which may be either a simple (ANSI) char or a unicode char, */
													/* depending on behind-the-scenes operating system definitions. Type LPTSTR */
													/* is a string of TCHARs. Type LPCTSTR is a const string of TCHARs. */

													/*  Start the child process. */
	char main_folder_path[MAX_INPUT_LENGTH] = "\0";
	strcpy_s(main_folder_path, MAX_INPUT_LENGTH, sent_main_folder_path);
	make_command_line_for_testgrade(student_id, main_folder_path, &command);  // creat the command line
	retVal = CreateProcessSimple(command, &procinfo);


	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		exitcode = ERR_CODE_OPEN_PROCESS;
		goto Failed_open_process;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */

	if (waitcode != WAIT_TIMEOUT && waitcode != WAIT_OBJECT_0) {
		printf("someting went wrong in WaitForSingleObject");
		exitcode = ERR_CODE_OPEN_PROCESS;
	}

	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate */
		exitcode = ERR_CODE_OPEN_PROCESS;
	}

	if (GetExitCodeProcess(procinfo.hProcess, &exitcode) == 0) {
		printf("someting went wrong in GetExitCodeProcess\n");
		exitcode = ERR_CODE_OPEN_PROCESS;
	}

	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */

	//printf("The exit code for the process is 0x%x\n", exitcode);
Failed_open_process:
	return exitcode;
}


BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

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