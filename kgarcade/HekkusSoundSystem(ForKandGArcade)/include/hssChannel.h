/* ****************************************************************************

HSS Channel ver 0.99 - 07/12/2002
    by Thomas Maniero - last modified 12/03/2004

todo:

* aggiunto frequency/tempo... fatto! da testare...

* aggiungo ai canali pause, resume and stop? problema di sync... fatto!

* aggiungo play?

**************************************************************************** */


#ifndef _HSSCHANNEL_H
#define _HSSCHANNEL_H


#include "hssImpExp.h"


#include "hssTypes.h"
#include "hssData.h"



/**
 *  %Sound channel class.
 *  When a sound are played the Sound class assign it to a Channel.\n
 *  Use this class to modify the state of a playing or paused hssMusic or hssSound.
 */
class HSS_CLS_API hssChannel {

    friend class hssSpeaker;

protected:
    hssSpeaker *m_ownsnd;

    //u32 *m_mstvol;  // pointer to m_masterVolume from Sound
	u32 m_chlvol;
    u32 m_volume;
    u32 m_pan;
    bool m_loop;

    bool m_pause, m_stop;

    u32 m_freq;         // frequency
    u32 m_virtfreq;     // virtual frequency
    bool m_changefreq;  // change frequency?
    u32 m_speed;


protected:
    HSS_API hssChannel();
    HSS_API void play(bool paused = false);

public:
    virtual HSS_API void volume(u32 v);
    HSS_API u32 volume();

    HSS_API void frequency(u32 f);
    HSS_API u32 frequency();

    HSS_API void speed(u32 s);
    HSS_API u32 speed();

    HSS_API void loop(bool l);
    HSS_API bool loop();

    virtual HSS_API void pan(u32 p);
    HSS_API u32 pan();

    virtual HSS_API void position(u32 p);
    virtual HSS_API u32 position();
    virtual HSS_API u32 length();

    HSS_API void stop();
    HSS_API void pause();
    HSS_API void resume();

    HSS_API bool playing();
};


class HSS_CLS_API hssMusicChannel : public hssChannel {

    friend class hssSpeaker;

private:
    // dati attuale modulo
    ModHeader *m_modheader;
    ModPattern *m_modpattern;
    // numero canali
    u32 m_numchl;
    // attuale pattern e note e numero nella sequenza pattern
    u32 m_pattern, m_note, m_seq, m_restart;
    // dati frequenze e tempo
    u32 m_bytextick, m_bytecnt;
    u32 m_tickxdivision, m_tickcnt;
    // dati per note e comandi canali
    u32 m_finenoteidx[MOD_MAXCHANNEL];
    u32 m_notefreq[MOD_MAXCHANNEL];
    u32 m_sample[MOD_MAXCHANNEL];
    u32 m_freqfactor[MOD_MAXCHANNEL];
    s32 m_clcvol[MOD_MAXCHANNEL];      // mi serve per i calcoli del vol slide
    u32 m_glbvol[MOD_MAXCHANNEL];      // gvolume contiene il vol modificato dal vol del m_mod
    u32 m_command[MOD_MAXCHANNEL];
    u32 m_opx[MOD_MAXCHANNEL];
    u32 m_opy[MOD_MAXCHANNEL];
    u32 m_opxy[MOD_MAXCHANNEL];
    u32 m_position[MOD_MAXCHANNEL];
    u32 m_cpan[MOD_MAXCHANNEL];
    // dati per sample
    u32 m_slength[MOD_MAXSAMPLE];
    u32 m_sloopstart[MOD_MAXSAMPLE];
    u32 m_slooplength[MOD_MAXSAMPLE];
    u32 m_svol[MOD_MAXSAMPLE];
    u32 m_sfinetune[MOD_MAXSAMPLE];
    u32 m_sdata[MOD_MAXSAMPLE];
    // dati per effetti
    s32 m_voldelta[MOD_MAXCHANNEL];
    u32 m_slideupdown[MOD_MAXCHANNEL];
    u32 m_slidetonote[MOD_MAXCHANNEL];
    u32 m_slidetonotedelta[MOD_MAXCHANNEL];
    u32 m_arpeggioidx[MOD_MAXCHANNEL];
    u32 m_arpeggiofq[MOD_MAXCHANNEL];   // freqfactor note
    u32 m_arpeggiofqx[MOD_MAXCHANNEL];  // freqfactor note+x
    u32 m_arpeggiofqy[MOD_MAXCHANNEL];  // freqfactor note+y
    u32 m_vibratoidx[MOD_MAXCHANNEL];   // indice alla tabella
    u32 m_vibratospeed[MOD_MAXCHANNEL]; // adder all'indice
    u32 m_vibratodepth[MOD_MAXCHANNEL]; // profondità curva, da moltiplicare al valore tabella
    u32 m_delaynote[MOD_MAXCHANNEL];
    u32 m_delaynotefreq[MOD_MAXCHANNEL];
    u32 m_tickcutsample[MOD_MAXCHANNEL]; // per effetto 0xEC
    u32 m_jumpseq;
    u32 m_jumpnote;
    u32 m_delaypattern;
    u8 m_looppattern[MOD_MAXCHANNEL];    // ffffllll f = flag, l = number to loop
    u8 m_looppatternrow[MOD_MAXCHANNEL];
    u32 m_offset[MOD_MAXCHANNEL];

    u32 m_bpm;


private:
    HSS_API hssMusicChannel();

public:
    virtual HSS_API void volume(u32 v);

    virtual HSS_API void pan(u32 p);

    virtual HSS_API void position(u32 p);
    virtual HSS_API u32 position();
    virtual HSS_API u32 length();
};


class HSS_CLS_API hssSoundChannel : public hssChannel {

    friend class hssSpeaker;

private:
    u8 *m_sample;
    u32 m_freqfactor;
    u32 m_position;
    u32 m_length;

    bool m_8bit, m_stereo;


private:
    HSS_API hssSoundChannel();

public:
    virtual HSS_API void volume(u32 v);
    
    virtual HSS_API void position(u32 p);
    virtual HSS_API u32 position();
    virtual HSS_API u32 length();
};



#endif
