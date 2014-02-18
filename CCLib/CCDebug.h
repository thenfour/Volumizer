

#pragma once


#include "global.h"


#ifdef NDEBUG
    #define CCOpenDebugLog()
    #define CCCloseDebugLog()
    #define MsgBoxf()
    #define MsgBoxfv()
    #define odsfv()
    #define _odsf()
    #define odsf()
    #define odsr()
#else
/*
    Either an absolute path, or a path RELATIVE to the EXE that
    was used to start the app.
*/
HRESULT CCEXPORT CCOpenDebugLog(PCWSTR wszFileName);
HRESULT CCEXPORT CCCloseDebugLog();


/*
	MessageBox Formatted
*/
void CCEXPORT __cdecl MsgBoxf(PCWSTR wszString, ...);
void CCEXPORT MsgBoxfv(PCWSTR wszString, va_list argptr);


/*
	OutputDebugString FORMATTED (should have been included with everything)
*/
void CCEXPORT __cdecl odsf(PCWSTR wszFunction, PCWSTR wszString, ...);
void CCEXPORT odsfv(PCWSTR wszFunction, PCWSTR wszString, va_list argptr);
void CCEXPORT _odsf(PCWSTR wszFunction, PCWSTR wszString);


/*
	OutputDebugString RECTANGLE - this function just makes it easy
	to output the dimentions of a rectangle in the format:
	
	rcHwnd = (34,23)-(23,25)
*/
void CCEXPORT odsr(PCWSTR wszFunction, PCWSTR wszString, PRECT prc);

#endif
