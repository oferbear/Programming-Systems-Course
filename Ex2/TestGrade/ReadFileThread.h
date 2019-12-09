// ReadFileThread.h

// This header consists the includes and function declerations for the function used in ReadFileThread, and its documentation.

#pragma once

#ifndef __READFILETHREAD_H__
#define __READFILETHREAD_H__

// Includes --------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include "HardCodedData.h"
#include "TestGrade.h"

// Function Declaration -------------------------------------------------------

/*
This function is called when creating a thread, opens a grade file,
read its content and saves the result in the designated variable in lpParam.
Input:  LPVOID lpParam - parameters for the thread. later we cast them as 'CALC_GRADE_params_t' struct we defined
Output: DWORD, success or error code
*/
DWORD WINAPI ReadFileThread(LPVOID lpParam);

#endif // __READFILETHREAD_H__