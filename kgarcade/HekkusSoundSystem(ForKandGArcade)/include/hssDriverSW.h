/* ****************************************************************************

HSS Driver Symbian ver 0.1 - 21/02/2004
    by Thomas Maniero - last modified 21/02/2004

todo:

**************************************************************************** */


#ifndef _HSSDRIVERSYMBIAN_H
#define _HSSDRIVERSYMBIAN_H


#include "hssImpExp.h"


#include "hssDriver.h"

#include <mda\common\audio.h>
#include <MdaAudioOutputStream.h>


#if defined(__WINS__)
    #define MAGIC_MIXER_NUMBER 130
#else
    #define MAGIC_MIXER_NUMBER 80
#endif


#define MIXER_BUFFERLENGTH  MAGIC_MIXER_NUMBER*2

#define MIXER_BLOCKLENGTH   MAGIC_MIXER_NUMBER
#define MIXER_BLOCKMIN       1
#define MIXER_BLOCKMAX      32



class hssDriverSW : public hssDriver, public MMdaAudioOutputStreamCallback {

protected:
    CMdaAudioOutputStream* m_stream;
    TMdaAudioDataSettings m_settings;
    TInt m_samplerate, m_monostereo;

    TPtr8 **m_descbuf;

    u32 m_numwavehdr;

    // circle buffer contenente la lista dei buffer da riempire
    u8 **m_cbwhdr;
    u32 m_cbw, m_cbr;

    bool m_suspended;


private:
    virtual HSS_API void MaoscOpenComplete(TInt aError);
    virtual HSS_API void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer);
    virtual HSS_API void MaoscPlayComplete(TInt aError);

    HSS_API s32 symbianvalue(TInt &samplerate, TInt &monostereo);


public:
    HSS_API hssDriverSW();
    virtual HSS_API ~hssDriverSW();

    virtual HSS_API s32 open(u32 freqmix, u32 bps, bool stereo);
    virtual HSS_API s32 close();

    virtual HSS_API bool poll();

    virtual HSS_API void enterCriticalSection();
    virtual HSS_API void leaveCriticalSection();

    virtual HSS_API void suspend();
    virtual HSS_API void resume();
};


#endif