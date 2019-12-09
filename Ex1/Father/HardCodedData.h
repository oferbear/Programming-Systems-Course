// HardCodedData.h

// This header consists of the constat numbers in the project

#pragma once

// Constants -------------------------------------------------------------------

#define MAX_INPUT_LENGTH 256				// max input length
#define MAX_SON_INPUT 32					// max simple-phrase length
#define TIMEOUT_IN_MILLISECONDS 5000		// time limit for the process son.exe
#define BRUTAL_TERMINATION_CODE 0x55		// return code for when subprocess reaches time limit 
#define SONS_PREFIX "son.exe "
static const int ERR_CODE_DEFAULT = -4;		// default error code
static const int ERR_CODE_OPEN_FILE_FAIL = -5;	// default error when cant open file
static const int DEFAULT_CALL_FOR_SON = -6;		// default exit code for subprocess