// functions.h

#pragma once
#include <stdio.h>
#include <windows.h>
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

// Function Declarations -------------------------------------------------------
/*
this function opens the student id file in read mode
INPUT: char *main_folder_path - string contains the relative path to the main folder
	   FILE *pfl_studentids - pointer to the "student_ids.txt" file
OUTPUT: void
*/
void open_student_id_file(char *main_folder_path, FILE *pfl_studentids);
/*
this function creat the path for the student folder, (./input/grades_ID)
INPUT: char *student_folder_path -  string contains the relative path to a student folder  (grades_ID)
	   char *student_id - contains a string of the student ID
	   char *main_folder_path - string contains the relative path to the main folder
OUTPUT: void
*/
void creat_file_path_for_student(char *student_folder_path, char *student_id, char *main_folder_path);
/*
this function creat a new file called final_grades that will contains all the final grades for each student
INPUT: FILE *pfl_finalgrades -  pointer to the "final_grades.txt" file
	   char *main_folder_path - string contains the relative path to the main folder
OUTPUT: int - succes/error code for opening a file
*/
int create_final_grades_file(char *main_folder_path);
/*
this function take the final grade from final_ID file that the test_grade creates and add it
	 with the matching ID to the final_grades file
INPUT: char *student_id - contains a string of the student ID
	   FILE *pfl_finalgrades -  pointer to the "final_grades.txt" file
	   char *main_folder_path - string contains the relative path to the main folder
OUTPUT: int - succes/error code for opening both files
*/
int update_final_grades_file(char *student_id, char *main_folder_path);
/*
this function creates the command line "test_grade.exe "student_folder_path"" in order to open process per student ID
INPUT: char *student_id - contains a string of the student ID
	   char *main_folder_path - string contains the relative path to the main folder
	   char *command - the command line we creat goes into this varibel
OUTPUT: void
*/
void make_command_line_for_testgrade(char *student_id, char *main_folder_path, char *command);
/*
This function handles calling for another process, and receiving its return code
INPUT: char *sent_main_folder_path - string contains the relative path to the main folder
	   char *student_id - contains a string of the student ID
OUTPUT: int - succes/error code for opening a process and for succes/error inside the process
*/
int CreateProcessSimpleMain(char *sent_main_folder_path, char *student_id);
/*
This function creates new process easily, without the need for all the parameters available for opening a process.
Input:  LPTSTR CommandLine - command line argument
		PROCESS_INFORMATION *ProcessInfoPtr - pointer to a struct with process information
Output: BOOL, 0 if failed, anything else for success
*/
BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr);

#endif // __FUNCTION_H__