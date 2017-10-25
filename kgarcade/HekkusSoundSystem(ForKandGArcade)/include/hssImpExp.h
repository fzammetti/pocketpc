

#ifndef _HSSIMPEXP_H
#define _HSSIMPEXP_H


#if (defined(_WIN32_WCE) || defined(WIN32))

#ifdef HSS_EXPORTS
#define HSS_CLS_API __declspec(dllexport)
#define HSS_API
#else
#define HSS_CLS_API __declspec(dllimport)
#define HSS_API
#endif

#endif


#if defined(__SYMBIAN32__)

#ifdef HSS_EXPORTS
#define HSS_API     EXPORT_C
#define HSS_CLS_API
#else
#define HSS_API     IMPORT_C
#define HSS_CLS_API
#endif

#endif



#endif

