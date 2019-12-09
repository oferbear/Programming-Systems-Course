// main.c

// Includes ---------------------------------------------------------------------

#include <stdio.h>
#include <Windows.h>
#include "HardCodedData.h"



// Function Definitions --------------------------------------------------------

int main(int argc, char *argv[])
{
	FILE *pfl_studentids = NULL;   // creat pointer for student ids file
	char student_id[STUDENT_ID_LENGTH] = "\0";      // size 10 becuse the ID contains 9 numbers and \o
	char remove_new_line_str[STUDENT_ID_LENGTH] = "\0";
	int return_code = ERR_CODE_DEFAULT;
	int exitcode = ERR_CODE_DEFAULT;
	char main_folder_path[MAX_INPUT_LENGTH] = "\0";
	if (argc < 2) {    //check if there are enough arguments
		printf("No folder name entered");
		return_code = ERR_CODE_NOT_ENOUGH_ARGUMENTS;
	}
	strcpy_s(main_folder_path, MAX_INPUT_LENGTH, RELATIV_PATH_PREFIX);
	strcat_s(main_folder_path, MAX_INPUT_LENGTH, argv[1]);   /* copy the folder name from command line and
																	add "./" in order to creat the path   */
	open_student_id_file(main_folder_path, &pfl_studentids); // open the student id file
	if (pfl_studentids == NULL) {    //check if file was open
		printf("cannot open student_ids file");
		return_code = ERR_CODE_OPEN_FILE;
		goto CANT_OPEN_FILE;  // skip the rest of the code and close the main
	}
	return_code = create_final_grades_file(main_folder_path); // creat final grades file
	while (fgets(student_id, 20, pfl_studentids) != NULL) {  // go over the student ids
		strtok_s(student_id, "\n", remove_new_line_str);
		exitcode = CreateProcessSimpleMain(main_folder_path, student_id);  //open process and send the ID to TestGrade
		if (exitcode != ERR_CODE_DEFAULT) {
			return_code = exitcode;
			printf("Captain, we were unable to calculate %s", student_id);
		}
		return_code = update_final_grades_file(student_id, main_folder_path); /* update the final grade file with
																							the grade calculated by TestGrade  */
	}
	if (return_code == ERR_CODE_DEFAULT) {
		printf("The grades have arrived, captain");
	}
	fclose(pfl_studentids);
CANT_OPEN_FILE:
	return return_code;
}