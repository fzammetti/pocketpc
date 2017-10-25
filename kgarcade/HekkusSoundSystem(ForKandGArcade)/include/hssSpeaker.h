/* ****************************************************************************

HSS Engine ver 0.99 - 18/06/2002
    by Thomas Maniero - last modified 12/03/2004

todo:

**************************************************************************** */


#ifndef _HSSSPEAKER_H
#define _HSSSPEAKER_H


#include "hssImpExp.h"


#include "hssData.h"
#include "hssChannel.h"
#include "hssDriver.h"
#include "hssThread.h"
#include "hssErrorDefs.h"




#define MUSIC_MIN  1
#define MUSIC_MAX  3
#define SOUND_MIN  8
#define SOUND_MAX 64


#define AMIGA_FREQ 7159090.5




/**
 *  Basic sound class.
 *  Use this class to open/close/supend/resume sound output and to play sounds.
 */
class HSS_CLS_API hssSpeaker : public hssThread {

    friend class hssChannel;
    friend class hssSoundChannel;
    friend class hssMusicChannel;

private:
    hssDriver *m_driver;

    bool m_open;
    bool m_suspended;

    // canali per MOD
    u32 m_modchannels;
    hssMusicChannel *m_mc;
    hssMusicChannel **m_mcpling;
    //u32 m_playingmodchannels;

    // canali per SFX
    u32 m_sfxchannels;
    hssSoundChannel *m_sc;
    hssSoundChannel **m_scpling;
    //u32 m_playingsfxchannels;

    u32 m_samplefreq[1713];
    u16 m_noteidx[1713];

    u32 m_masterModVol;   // master music volume
    u32 m_masterSFXVol;   // master sound volume

    volatile bool m_exitThread;


protected:
    virtual HSS_API u32 threadProc();
    
    HSS_API void updateModSFX(MixDriverData *mddata);

    HSS_API u32 findBestNoteIndex(u32 note);
    HSS_API void createTables(u32 freq);


public:
    HSS_API hssSpeaker();
    virtual HSS_API ~hssSpeaker();

    HSS_API s32 open(u32 freqmix, u32 bps, bool stereo, u32 maxmodchannels = MUSIC_MIN, u32 maxsfxchannels = SOUND_MIN);
    HSS_API s32 close();

    HSS_API void suspend();
    HSS_API void resume();

    HSS_API hssChannel *channel(s32 chl);

    HSS_API u32 maxChannelMusics();
    HSS_API u32 maxChannelSounds();

    HSS_API u32 playingChannelMusics();
    HSS_API u32 playingChannelSounds();


    HSS_API s32 playSound(hssSound *sndfx, bool paused = false);
    HSS_API void stopSounds();
    HSS_API void pauseSounds();
    HSS_API void unpauseSounds();

    HSS_API s32 playMusic(hssMusic *mod, bool paused = false);
    HSS_API void stopMusics();
    HSS_API void pauseMusics();
    HSS_API void unpauseMusics();

    HSS_API void volumeSounds(u32 v);
    HSS_API u32 volumeSounds();

    HSS_API void volumeMusics(u32 v);
    HSS_API u32 volumeMusics();
};



#endif
