/*
    Preprocessor defines for this project:

    _DEBUG       Defined for a debug build.
    NDEBUG       Defined for a release build.
    CCLIB_BUILD  Defined for this project's build always.
*/

#pragma once


#ifndef CCEXPORT
#   ifdef CCLIB_BUILD
#       define CCEXPORT __declspec(dllexport)
#   else
#       define CCEXPORT
#   endif
#endif


// FORCE NO EXPORTS
#undef CCEXPORT
#define CCEXPORT



#ifndef SAFE_DELETEOBJECT
	#define SAFE_DELETEOBJECT(a) { if(a) DeleteObject(a); (a) = 0;}
#endif

#ifndef SAFE_FREE
	#define SAFE_FREE(a) { if(a) free(a); (a) = 0;}
#endif

#ifndef SAFE_RELEASE
    #define SAFE_RELEASE(a)             { if(a) (a)->Release(); (a) = 0;}
#endif


void InitResModule();
void UninitResModule();

