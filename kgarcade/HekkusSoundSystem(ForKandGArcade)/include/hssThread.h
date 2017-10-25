/* ****************************************************************************

HSS Thread ver 0.1 - 21/02/2004
    by Thomas Maniero - last modified 21/02/2004

todo:

**************************************************************************** */


#ifndef _HSSTHREAD_H
#define _HSSTHREAD_H


#include "hssImpExp.h"


#include "hssTypes.h"

#if (defined(_WIN32_WCE) || defined(WIN32))
    #include <windows.h>
    #define THREAD_PRIORITY_SOUND_PROPER THREAD_PRIORITY_HIGHEST
#else
    #include <w32std.h>
    #define THREAD_PRIORITY_SOUND_PROPER EPriorityMore
#endif




class HSS_CLS_API hssThread {

private:
#if (defined(_WIN32_WCE) || defined(WIN32))
    HANDLE m_thread;
    DWORD m_threadId;
#endif

    
#if defined(__SYMBIAN32__)
    RThread m_thread;
#endif


    bool m_ptcreate;
    bool m_ptsuspended;
    volatile bool m_ptexit;

private:
#if (defined(_WIN32_WCE) || defined(WIN32))
    static DWORD WINAPI staticThreadProc(LPVOID lpParameter);
#endif

#if defined(__SYMBIAN32__)
    static TInt staticThreadProc(TAny *pnt);
#endif


public:
    HSS_API hssThread();
    virtual HSS_API ~hssThread();

    virtual HSS_API u32 threadProc() = 0;

    s32 HSS_API createThread();
    s32 HSS_API destroyThread();

    void HSS_API priorityThread(u32 p);

    void HSS_API sleepThread(u32 s);

    void HSS_API suspendThread();
    void HSS_API resumeThread();
};


#endif