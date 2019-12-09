// HardCodedData.h

// This header consists of the constat numbers in the project

#pragma once

// Constants -------------------------------------------------------------------

#define MAX_INPUT_LENGTH 32		// max length for the input string (simple-phrase), as defined in the instruction
static const int ERR_CODE_DEFAULT = -1;		// default error code. when undifined error occurs, this error code will be returned
static const int ERR_CODE_NOT_ENOUGH_ARGUMENTS = -2;	// error code for when not enough arguments sent with the program
static const int ERR_CODE_TOO_MANY_ARGUMENTS = -3;		// error code for when too many arguments sent with the program