//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.93
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////


#ifndef _SOUND_H
#define _SOUND_H


#include <windows.h>
#include <mmreg.h>

#include "SoundData.h"
#include "SoundChannel.h"

#include "defs.h"



#define MOD_MAX 2

#define SFX_MAX 8

#define MOD_MIXBUF_11025 298   //496
#define MOD_MIXBUF_22050 588   //984
#define MOD_MIXBUF_44100 1176  //1968

#define MOD_PPC_WHDR 5


namespace Frog {


class Sound {

private:
    HWAVEOUT m_hwaveout;
    WAVEFORMATEX m_waveformatx;
    WAVEHDR m_wavehdr[MOD_PPC_WHDR];

    HANDLE m_thread;
    DWORD m_threadId;
    CRITICAL_SECTION m_critSecRtp;
    HANDLE m_killEvent, m_exitEvent;

    bool m_open;

    uint32_t m_freqmix;

    // canali per MOD
    ModChannel m_mc[MOD_MAX];

    // canali per SFX
    SFXChannel m_sc[SFX_MAX];

    uint16_t *m_samplefreq;

    // buffer mix
    uint8_t *m_bufmix;
    // lunghezza di un frame (senza il doppio per lo stereo)
    uint32_t m_bufmixframe;
    // totale lunghezza bufmix
    uint32_t m_bufmixtotal;
    // puntatore al buffer precedente (per il double/triple... buffer)
    uint8_t *m_pbufmix;
    // indica se output in stereo o mono, uso uint32_t per facilitarmi i <<...
    uint32_t m_stereo;

    uint32_t m_globalVolume;   // global volume


private:
    static DWORD WINAPI update(LPVOID lpParameter);
    void updateModSFX();


public:
    Sound();
    ~Sound();

    bool open(uint32_t freqmix, bool stereo);
    bool close();

    void suspend();
    void resume();

    Channel *getChannel(uint32_t chl);

    uint32_t numChannelMod();
    uint32_t numChannelSFX();

    uint32_t playingChannelMod();
    uint32_t playingChannelSFX();


    uint32_t playSFX(SoundFX *sndfx);
    void stopSFX(uint32_t chl);
    void pauseSFX();
    void resumeSFX();

    uint32_t playMod(Module *mod);
    void stopMod(uint32_t chl);
    void pauseMod();
    void resumeMod();

    void setVolume(uint32_t v);
    uint32_t getVolume();
};


}


#endif
