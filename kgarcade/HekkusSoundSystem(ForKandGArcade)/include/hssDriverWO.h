/* ****************************************************************************

HSS Driver WaveOut ver 0.1 - 21/02/2004
    by Thomas Maniero - last modified 21/02/2004

todo:

**************************************************************************** */


#ifndef _HSSDRIVERWAVEOUT_H
#define _HSSDRIVERWAVEOUT_H


#include "hssImpExp.h"


#include "hssDriver.h"




#define MIXER_BUFFERLENGTH 135

#define MIXER_BLOCKLENGTH   20
#define MIXER_BLOCKMIN       3
#define MIXER_BLOCKMAX      32



class HSS_CLS_API hssDriverWO : public hssDriver {

protected:
    HWAVEOUT m_hwaveout;
    WAVEFORMATEX m_waveformatx;
    WAVEHDR *m_wavehdr;
    u32 m_numwavehdr;

    // circle buffer contenente la lista dei buffer da riempire
    WAVEHDR **m_cbwhdr;
    u32 m_cbw, m_cbr;

    CRITICAL_SECTION m_critSecRtp;

private:
    static HSS_API void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);


public:
    HSS_API hssDriverWO();
    virtual HSS_API ~hssDriverWO();

    virtual HSS_API s32 open(u32 freqmix, u32 bps, bool stereo);
    virtual HSS_API s32 close();

    virtual HSS_API bool poll();

    virtual HSS_API void enterCriticalSection();
    virtual HSS_API void leaveCriticalSection();

    virtual HSS_API void suspend();
    virtual HSS_API void resume();
};


#endif