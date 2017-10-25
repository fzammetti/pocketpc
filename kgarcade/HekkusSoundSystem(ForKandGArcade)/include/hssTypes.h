/* ****************************************************************************

HSS typedef header - 07/11/2002
    by Thomas Maniero - last modified 07/11/2002

todo:

**************************************************************************** */

#ifndef _HSSTYPES_H
#define _HSSTYPES_H



#if (defined(_WIN32_WCE) || defined(WIN32)) && !defined(__WINS__)

    #include <tchar.h>

    typedef char  s8;
    typedef __int16 s16;
    typedef __int32 s32;
    typedef __int64 s64;

    typedef unsigned char  u8;
    typedef unsigned __int16 u16;
    typedef unsigned __int32 u32;
    typedef unsigned __int64 u64;

    typedef __int32 s24f8;

#endif


#if defined(__SYMBIAN32__)

    #include <e32std.h>

    typedef signed char  s8;
    typedef signed short int s16;
    typedef signed int s32;

    #if defined(__GNUC__)
        typedef long long s64;
    #else
        typedef long int s64;
    #endif

    typedef unsigned char  u8;
    typedef unsigned short int u16;
    typedef unsigned int u32;

    #if defined(__GNUC__)
        typedef long long u64;
    #else
        typedef long int u64;
    #endif

    typedef signed int s24f8;

    // definizioni di TCHAR e funzioni usate
    typedef char TCHAR;
    #define _T(x)     (x)
    #define _tfopen   fopen
    #define _tcscat   strcat
    #define _tcscpy   strcpy
    #define _tcslen   strlen
    
#endif




#endif
