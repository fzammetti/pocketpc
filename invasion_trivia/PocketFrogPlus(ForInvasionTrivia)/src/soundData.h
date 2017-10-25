//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.94
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _SOUNDDATA_H
#define _SOUNDDATA_H


#include <windows.h>

#include "defs.h"



#define MOD_MAXCHANNEL 4
#define MOD_MAXSAMPLE 32


namespace Frog {


// ATTENZIONE tutti i word vanno capovolti... l'amiga è una macchina big-endian


// struttura per i mod sample... 
// sono 15 o 31. se 31 dopo i primi 15 NON abbiamo la stringa di 4 byte "M.K."
struct struct_ModSample {
    int8_t name[22];       // nome del sample
    uint16_t length;        // lunghezza in word (va quindi moltiplicato per 2) (* 2)
    uint8_t finetune;       // nota... lower 4 bits (-7..8) gestisco come unsigned...
    uint8_t volume;         // 0..64 (64? dovrebbe essere 63) -- vol = 20*log10(Vol/64)
    uint16_t loopstart;     // offset in word inizio del sample loop (* 2)
    uint16_t looplength;    // lunghezza in word del sample loop (loop se > 1) (* 2)
};
typedef struct struct_ModSample ModSample;


union union_ModNote {
    struct {
        unsigned notefreq : 12;
        unsigned : 4;
        unsigned y : 4;
        unsigned x : 4;    
        unsigned command : 4;
        unsigned sample : 4;    // 0 = NULL, 1..31 valid
    };
    struct {
        unsigned : 16;
        unsigned xy : 8;
        unsigned : 8;
    };
    uint32_t bits;
};
typedef union union_ModNote ModNote;


struct struct_ModPattern {
    ModNote notes[256];
    //ModNote notes[64][4];
};
typedef struct struct_ModPattern ModPattern;


// module header
struct struct_ModHeader {
    int8_t name[20];           // nome del modulo
    ModSample samples[31]; // sample del modulo
    uint8_t numSequence;        // numero sequenze (?) (1..128)
    uint8_t restart;            // non più usato (?)
    uint8_t sequences[128];     // sequenza (numSequence) suono pattern (ogni byte compreso 0..63)
    int8_t mkSign[4];          // "M.K." signature

    // pattern data...
    // ModPattern *patterns; // array di pattern, contiene 1024 note divise per 64

    // sample data...

};
typedef struct struct_ModHeader ModHeader;



struct struct_WaveChunk {
    uint32_t ckID;            // chunk type s8[4] = u32
    uint32_t nChunkSize;      // lunghezza di questo chunk (non comprende ckID e nChunkSize (8 byte))
};
typedef struct struct_WaveChunk WaveChunk;


#define WAVE_CHUNK_FMT  0x20746D66
#define WAVE_CHUNK_DATA 0x61746164


struct struct_WaveHeader {
    uint16_t wFormatTag;      // formato del wave
    uint16_t nChannels;       // numero canali
    uint32_t nSamplesPerSec;  // sample rate (11025 - 22050 - 44100...)
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;     
    uint16_t nBitsPerSample;  // bit campionamento... (8 - 16)
};
typedef struct struct_WaveHeader WaveHeader;




class Module {

    friend class Sound;

private:
    uint8_t *m_mh;
    uint32_t m_volume;
    bool m_loop;

    bool m_delete;

public:
    Module();
    ~Module();

    void setVolume(uint32_t v);
    uint32_t getVolume();

    void setLoop(bool l);
    bool getLoop();

    bool load(TCHAR *modname);
    bool load(HINSTANCE hInstance, DWORD dwResourceID);
};


// struttura per gli effetti sonori
class SoundFX {   

    friend class Sound;

private:
    uint8_t *m_sample;        // puntatore ai dati

    uint32_t m_freq;          // frequenza campionamento
    uint32_t m_length;        // lunghezza in byte del suono
    uint32_t m_left;          // 1 - canale sinistro, 0 - canale destro
    uint32_t m_volume;        // volume suono
    bool m_loop;

    bool m_delete;

public:
    SoundFX();
    ~SoundFX();

    void setVolume(uint32_t v);
    uint32_t getVolume();

    void setLoop(bool l);
    bool getLoop();

    bool load(TCHAR *wavname);
    bool load(HINSTANCE hInstance, DWORD dwResourceID);
};

}


#endif
