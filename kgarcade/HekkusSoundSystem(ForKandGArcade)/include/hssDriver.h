/* ****************************************************************************

HSS Driver Interface ver 0.1 - 21/02/2004
    by Thomas Maniero - last modified 21/02/2004

todo:

**************************************************************************** */


#ifndef _HSSDRIVER_H
#define _HSSDRIVER_H


#include "hssImpExp.h"


#include "hssTypes.h"



typedef struct {
    // frequenza campionamento
    u32 m_freqmix;
    // buffer mix
    u8 *m_bufmix;
    // lunghezza di un frame (senza il doppio per lo stereo)
    u32 m_bufmixframe;
    // totale lunghezza bufmix
    u32 m_bufmixtotal;
    // lunghezza di un elemento del buffer (1 = mono 8bit, 2 = stereo 8bit, 4 = stereo 16bit...) 
    u32 m_bufelemlen;
    // puntatore al buffer precedente (per il double/triple... buffer)
    u8 *m_pbufmix;
    // indica se output in stereo o mono, uso u32 per facilitarmi i <<...
    u32 m_stereo;
    // indica se output a 16 o 8 bit, uso u32 per facilitarmi i <<...
    u32 m_16bit;
} MixDriverData;



class HSS_CLS_API hssDriver {

protected:
    HSS_API MixDriverData m_mddata;

public:
    HSS_API hssDriver();
    virtual HSS_API ~hssDriver();

    virtual HSS_API s32 open(u32 freqmix, u32 bps, bool stereo) = 0;
    virtual HSS_API s32 close() = 0;

    virtual HSS_API bool poll() = 0;

    virtual HSS_API void enterCriticalSection() = 0;
    virtual HSS_API void leaveCriticalSection() = 0;

    virtual HSS_API void suspend() = 0;
    virtual HSS_API void resume() = 0;

    HSS_API MixDriverData *mddata();
};


#endif
