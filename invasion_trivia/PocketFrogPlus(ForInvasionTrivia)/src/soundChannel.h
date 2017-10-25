//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.94
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _SOUNDCHANNEL_H
#define _SOUNDCHANNEL_H


#include "defs.h"

#include "soundData.h"


namespace Frog {


class Channel {

    friend class Sound;

protected:
    uint32_t m_chlvol, m_gblvol;
    uint32_t m_volume;
    bool m_loop;

    bool m_pause, m_stop;


protected:
    Channel();
    void play();

public:
    virtual void setVolume(uint32_t v);
    uint32_t getVolume();

    void setLoop(bool l);
    bool getLoop();

    void stop();
    void pause();
    void resume();

    bool playing();
};


class ModChannel : public Channel {

    friend class Sound;

private:
    // dati attuale modulo
    ModHeader *m_modheader;
    ModPattern *m_modpattern;
    // attuale pattern e note e numero nella sequenza pattern
    uint32_t m_pattern, m_note, m_seq, m_restart;
    // dati frequenze e tempo
    uint32_t m_bytextick, m_bytecnt;
    uint32_t m_tickxdivision, m_tickcnt;
    // dati per note e comandi canali
    uint32_t m_notefreq[MOD_MAXCHANNEL];
    uint32_t m_sample[MOD_MAXCHANNEL];
    uint32_t m_freqfactor[MOD_MAXCHANNEL];
    uint32_t m_clcvol[MOD_MAXCHANNEL];      // mi serve per i calcoli del vol slide
    uint32_t m_glbvol[MOD_MAXCHANNEL];      // gvolume contiene il vol modificato dal vol del m_mod
    uint32_t m_command[MOD_MAXCHANNEL];
    uint32_t m_opx[MOD_MAXCHANNEL];
    uint32_t m_opy[MOD_MAXCHANNEL];
    uint32_t m_opxy[MOD_MAXCHANNEL];
    uint32_t m_position[MOD_MAXCHANNEL];
    uint32_t m_pan[MOD_MAXCHANNEL];
    // dati per sample
    uint32_t m_slength[MOD_MAXSAMPLE];
    uint32_t m_sloopstart[MOD_MAXSAMPLE];
    uint32_t m_slooplength[MOD_MAXSAMPLE];
    uint32_t m_svol[MOD_MAXSAMPLE];
    uint32_t m_sfinetune[MOD_MAXSAMPLE];
    uint32_t m_sdata[MOD_MAXSAMPLE];
    // dati per effetti
    int32_t m_voldelta[MOD_MAXCHANNEL];
    uint32_t m_slideupdown[MOD_MAXCHANNEL];
    uint32_t m_slidetonote[MOD_MAXCHANNEL];
    uint32_t m_slidetonotedelta[MOD_MAXCHANNEL];
    uint32_t m_arpeggioidx[MOD_MAXCHANNEL];
    uint32_t m_arpeggiofq[MOD_MAXCHANNEL];   // freqfactor note
    uint32_t m_arpeggiofqx[MOD_MAXCHANNEL];  // freqfactor note+x
    uint32_t m_arpeggiofqy[MOD_MAXCHANNEL];  // freqfactor note+y
    uint32_t m_vibratoidx[MOD_MAXCHANNEL];   // indice alla tabella
    uint32_t m_vibratospeed[MOD_MAXCHANNEL]; // adder all'indice
    uint32_t m_vibratodepth[MOD_MAXCHANNEL]; // profondità curva, da moltiplicare al valore tabella
    uint32_t m_delaynote[MOD_MAXCHANNEL];
    uint32_t m_delaynotefreq[MOD_MAXCHANNEL];
    uint32_t m_tickcutsample[MOD_MAXCHANNEL]; // per effetto 0xEC
    uint32_t m_jumpseq;
    uint32_t m_jumpnote;
    uint32_t m_delaypattern;


private:
    ModChannel();

public:
    virtual void setVolume(uint32_t v);
};


class SFXChannel : public Channel {

    friend class Sound;

private:
    uint8_t *m_sample;
    uint32_t m_freqfactor;
    uint32_t m_position;
    uint32_t m_length;


private:
    SFXChannel();
};

}

#endif
