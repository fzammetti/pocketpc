/* ****************************************************************************

HSS Data ver 0.99 - 07/12/2002
    by Thomas Maniero - last modified 12/03/2004

todo:

**************************************************************************** */


#ifndef _HSSDATA_H
#define _HSSDATA_H


#include "hssImpExp.h"


#if (defined(_WIN32_WCE) || defined(WIN32))
    #include <windows.h>
#endif

#include "hssTypes.h"



#define MOD_MAXCHANNEL 32
#define MOD_MAXSAMPLE  32


// ATTENZIONE tutti i word vanno capovolti... l'amiga è una macchina big-endian


// struttura per i mod sample... 
// sono 15 o 31. se 31 dopo i primi 15 NON abbiamo la stringa di 4 byte "M.K."
struct struct_ModSample {
    s8 name[22];       // nome del sample
    u16 length;        // lunghezza in word (va quindi moltiplicato per 2) (* 2)
    u8 finetune;       // nota... lower 4 bits (-7..8) gestisco come unsigned...
    u8 volume;         // 0..64 (64? dovrebbe essere 63) -- vol = 20*log10(Vol/64)
    u16 loopstart;     // offset in word inizio del sample loop (* 2)
    u16 looplength;    // lunghezza in word del sample loop (loop se > 1) (* 2)

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_ModSample ModSample;



union union_ModNote {
/*    struct {
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
    };*/
    u32 bits;

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef union union_ModNote ModNote;


struct struct_ModPattern {
    ModNote notes[256];
    //ModNote notes[64][4];

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_ModPattern ModPattern;


// module header
struct struct_ModHeader {
    s8 name[20];           // nome del modulo
    ModSample samples[31]; // sample del modulo
    u8 numSequence;        // numero sequenze (?) (1..128)
    u8 restart;            // non più usato (?)
    u8 sequences[128];     // sequenza (numSequence) suono pattern (ogni byte compreso 0..63)
    s8 mkSign[4];          // "M.K." signature

    // pattern data...
    // ModPattern *patterns; // array di pattern, contiene 1024 note divise per 64

    // sample data...

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_ModHeader ModHeader;



struct struct_WaveChunk {
    u32 ckID;            // chunk type s8[4] = u32
    u32 nChunkSize;      // lunghezza di questo chunk (non comprende ckID e nChunkSize (8 byte))

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_WaveChunk WaveChunk;


#define WAVE_RIFF_MAGIC 0x46464952
#define WAVE_CHUNK_FMT  0x20746D66
#define WAVE_CHUNK_DATA 0x61746164

#define WAVE_PCM_CODE	    0x0001
#define WAVE_MS_ADPCM_CODE	0x0002
#define WAVE_IMA_ADPCM_CODE	0x0011 


struct struct_WaveHeader {
    u16 wFormatTag;      // formato del wave
    u16 nChannels;       // numero canali
    u32 nSamplesPerSec;  // sample rate (11025 - 22050 - 44100...)
    u32 nAvgBytesPerSec;
    u16 nBlockAlign;     
    u16 nBitsPerSample;  // bit campionamento... (8 - 16)

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_WaveHeader WaveHeader;


struct decodestate_MSADPCM {
	u8 hPredictor;
	u16 iDelta;
	s16 iSamp1;
	s16 iSamp2;    
};



struct decoder_MSADPCM {
	WaveHeader wavefmt;
	u16 wSamplesPerBlock;
	u16 wNumCoef;
	s16 aCoeff[7][2];
	/* * * */
	struct decodestate_MSADPCM state[2];
};


struct struct_SndHeader {
    u32 frequency;          // frequenza di campionamento
    u32 channel;            // numero canali
    u32 bits;               // bits per sample
    u32 length;             // lunghezza dati (totale meno header)

#if defined (__SYMBIAN32__) && !defined (__WINS__)
} __attribute__((packed));
#else
};
#endif
typedef struct struct_SndHeader SndHeader;




/**
 *  Music class.
 *  Use this class to load a ProTracker module.\n
 *  You can play n times this object with hssEngine::playMusic(), 
 *  from one call to another you can vary the Music's properties like
 *  volume or loop flag, this affects only the next hssEngine::playMusic() call.
 *  \n\n Don't deallocated or reloaded a Music obj that are playing or your app will crash!
 * \n\n
 *  Supports ProTracker modules (.mod) with up to 32 channels.
 */
class HSS_CLS_API hssMusic {

    friend class hssSpeaker;

protected:
    u8 *m_mh;
    u32 m_volume;
    bool m_loop;

    u32 m_pan;

    u32 m_freq;

    u32 m_virtfreq;
    u32 m_speed;

    u32 m_numchl;

    bool m_delete;

protected:
    static HSS_API u32 getNumPattern(ModHeader *mh);
    static HSS_API u32 translatePTSign(s8 *str);

    HSS_API void destroy();

public:
    HSS_API hssMusic();
    virtual HSS_API ~hssMusic();

    HSS_API void volume(u32 v);
    HSS_API u32 volume();

    HSS_API void frequency(u32 f);
    HSS_API u32 frequency();
    
    HSS_API void loop(bool l);
    HSS_API bool loop();

    HSS_API void pan(u32 p);
    HSS_API u32 pan();

    HSS_API s32 load(const TCHAR *modname);
    HSS_API s32 load(void *membuf, bool copytomem);

#if (defined(_WIN32_WCE) || defined(WIN32))
    HSS_API s32 load(HINSTANCE hInstance, DWORD dwResourceID);
#endif
};


/**
 *  Sound class.
 *  Use this class to load a Waves sound.\n
 *  You can play n times this wave with hssEngine::playSound(), 
 *  from one call to another you can vary the Sound's properties like
 *  volume or loop flag, this affects only the next hssEngine::playSound() call.
 *  \n\n Don't deallocated or reloaded a Sound that are playing or your app will crash!
 * \n\n
 *  Supports 8bit/16bit uncompressed and Microsoft ADPCM compressed mono/stero WAVs.
 */
class HSS_CLS_API hssSound {   

    friend class hssSpeaker;

protected:
    u8 *m_sample;        // puntatore ai dati

    bool m_8bit, m_stereo;
    u32 m_freq;          // frequenza campionamento
    u32 m_length;        // lunghezza in byte del suono
    u32 m_left;          // 1 - canale sinistro, 0 - canale destro
    u32 m_volume;        // volume suono
    bool m_loop;
    u32 m_pan;

    s32 m_maxplaybacks;

    struct decoder_MSADPCM m_state_MSADPCM;

    u32 m_virtfreq;
    u32 m_speed;

    bool m_delete;

protected:
    HSS_API s32 init_MSADPCM(WaveHeader *format);
    HSS_API s32 nibble_MSADPCM(struct decodestate_MSADPCM *state, u8 nybble, s16 *coeff);
    HSS_API s32 decode_MSADPCM(u8 **audio_buf, u32 *audio_len, bool delbuf = true);
    
    HSS_API void destroy();

public:
    HSS_API hssSound();
    virtual HSS_API ~hssSound();

    HSS_API void volume(u32 v);
    HSS_API u32 volume();

    HSS_API void frequency(u32 f);
    HSS_API u32 frequency();

    HSS_API void loop(bool l);
    HSS_API bool loop();

    HSS_API void pan(u32 p);
    HSS_API u32 pan();

    HSS_API void maxplaybacks(s32 mpb);
    HSS_API s32 maxplaybacks();

    HSS_API s32 load(const TCHAR *wavname);
    HSS_API s32 load(void *membuf, bool copytomem);

#if (defined(_WIN32_WCE) || defined(WIN32))
    HSS_API s32 load(HINSTANCE hInstance, DWORD dwResourceID);
#endif
};



#endif
