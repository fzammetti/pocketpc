//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.93
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////


#include <tchar.h>


#include "Sound.h"

#include "SoundConst.h"



namespace Frog {



// big to little endian 16bit
uint16_t btol16(uint16_t big) {

    uint16_t little;

    ((uint8_t *)&little)[1] = ((uint8_t *)&big)[0];
    ((uint8_t *)&little)[0] = ((uint8_t *)&big)[1];

    return little;
}

// big to little endian 32bit
uint32_t btol32(uint32_t big) {

    uint32_t little;

    ((uint8_t *)&little)[1] = ((uint8_t *)&big)[0];
    ((uint8_t *)&little)[0] = ((uint8_t *)&big)[1];
    ((uint8_t *)&little)[3] = ((uint8_t *)&big)[2];
    ((uint8_t *)&little)[2] = ((uint8_t *)&big)[3];

    return little;
}



Sound::Sound() {

    m_open = false;
    m_bufmix = 0;

    btol32(gerdata[1]);
}

Sound::~Sound() {

    close();
}



bool Sound::open(uint32_t freqmix, bool stereo) {

    uint32_t i;

    if (m_open)
        return false;

    switch (freqmix) {
      case 44100 :
          m_bufmixframe = MOD_MIXBUF_44100;
          m_samplefreq = (uint16_t *)samplefreq_44100;
        break;

      case 22050 :
          m_bufmixframe = MOD_MIXBUF_22050;
          m_samplefreq = (uint16_t *)samplefreq_22050;
        break;

      case 11025 :
          m_bufmixframe = MOD_MIXBUF_11025;
          m_samplefreq = (uint16_t *)samplefreq_11025;
        break;

      default :
          m_bufmixframe = MOD_MIXBUF_22050;
          m_samplefreq = (uint16_t *)samplefreq_22050;
          freqmix = 22050;
        break;
    }

    // setto stereo
    if (stereo)
        m_stereo = 1;
    else
        m_stereo = 0;


    m_globalVolume = 64;


    m_freqmix = freqmix;
    m_bufmixtotal = (m_bufmixframe*MOD_PPC_WHDR) << m_stereo;
    m_bufmix = new uint8_t[m_bufmixtotal];
    if (m_bufmix == 0)
        return false;

    // pulisco mixbuffer con scrittura a 8bit
    for (i = 0; i < m_bufmixtotal; i++)
        (*(uint8_t *)((uint32_t)m_bufmix + i)) = 128;



    // Implementazione PocketPC
    InitializeCriticalSection(&m_critSecRtp);

    m_thread = CreateThread(NULL,           // pointer to security attributes
                          0,                // initial thread stack size
                          update,           // pointer to thread function
                          (void *)this,     // argument for new thread
                          CREATE_SUSPENDED, // creation flags
                          &m_threadId);     // pointer to receive thread ID
    if (m_thread == NULL)
        return false;

    m_killEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_exitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    MMRESULT res;

    // apro waveout
    m_waveformatx.wFormatTag = WAVE_FORMAT_PCM;
    m_waveformatx.nSamplesPerSec = m_freqmix;
    m_waveformatx.nChannels = 1 << m_stereo;
    m_waveformatx.wBitsPerSample = 8;
    m_waveformatx.nBlockAlign = m_waveformatx.nChannels * (m_waveformatx.wBitsPerSample/8);
    m_waveformatx.nAvgBytesPerSec = m_waveformatx.nSamplesPerSec * m_waveformatx.nChannels;
    m_waveformatx.cbSize = 0; // no extra information

    for (i = 0; i < waveOutGetNumDevs(); i++)  {

        res = waveOutOpen(&m_hwaveout,      // LPHWAVEOUT phwo,	
                          i,                // UINT uDeviceID,	
                          &m_waveformatx,   // LPWAVEFORMATEX pwfx,	
                          m_threadId,       // DWORD dwCallback,	      indirizzo proc callback
                          (DWORD)this,      // DWORD dwCallbackInstance, indirizzo ulteriori dati per cb
                          CALLBACK_THREAD); // DWORD fdwOpen	

        if (res == MMSYSERR_NOERROR)
            break;
    }
    if (res != MMSYSERR_NOERROR) {
        CloseHandle(m_killEvent);
        CloseHandle(m_exitEvent);
        CloseHandle(m_thread);
        delete [] m_bufmix;
        m_bufmix = 0;
        return false;
    }
    

    waveOutPause(m_hwaveout);

    // inserisco nella coda MOD_PPC_WHDR pacchetti vuoti
    for (i = 0; i < MOD_PPC_WHDR; i++) {

        ZeroMemory(&m_wavehdr[i], sizeof(WAVEHDR));

        // assegno i giusti buffer...
        m_wavehdr[i].dwBufferLength = 8;
        m_wavehdr[i].lpData = (char *)&m_bufmix[(i*m_bufmixframe) << m_stereo];

        waveOutPrepareHeader(m_hwaveout,       // HWAVEOUT hwo,	
                             &m_wavehdr[i],    // LPWAVEHDR pwh,	
                             sizeof(WAVEHDR)); // UINT cbwh	  

        waveOutWrite(m_hwaveout,       // HWAVEOUT hwo,	
                     &m_wavehdr[i],    // LPWAVEHDR pwh,	
                     sizeof(WAVEHDR)); // UINT cbwh

    }


    // avvio thread sonoro
    SetThreadPriority(m_thread, THREAD_PRIORITY_HIGHEST);
    Sleep(100);
    ResumeThread(m_thread);

    // riavvio waveout
    waveOutRestart(m_hwaveout);


    m_open = true;

    return true;
}


bool Sound::close() {

    if (m_open) {

        // faccio uscire il thread, setto evento
        SetEvent(m_killEvent);

        // aspetto finché esce
        WaitForSingleObject(m_exitEvent, INFINITE);
        // aspetto l'uscita... 100 ms
        Sleep(100);

        CloseHandle(m_killEvent);
        CloseHandle(m_exitEvent);
        CloseHandle(m_thread);

        DeleteCriticalSection(&m_critSecRtp);

	    waveOutReset(m_hwaveout);

	    for (uint32_t i = 0; i < MOD_PPC_WHDR; i++)
		    waveOutUnprepareHeader(m_hwaveout, &m_wavehdr[i], sizeof(WAVEHDR));

        waveOutClose(m_hwaveout);

        if (m_bufmix) {
            delete [] m_bufmix;
            m_bufmix = 0;
        }

        m_open = false;
    }

    return true;
}


Channel *Sound::getChannel(uint32_t chl) {


    if (chl < MOD_MAX)
        return &m_mc[chl];

    if (chl < MOD_MAX+SFX_MAX)
        return &m_sc[chl-MOD_MAX];

    return NULL;
}

uint32_t Sound::numChannelMod() {

    return MOD_MAX;
}

uint32_t Sound::numChannelSFX() {

    return SFX_MAX;
}

uint32_t Sound::playingChannelMod() {

    uint32_t modchl = 0;
    for (uint32_t i = 0; i < MOD_MAX; i++) {
        if (m_mc[i].playing())
            modchl++;
    }

    return modchl;
}

uint32_t Sound::playingChannelSFX() {

    uint32_t sfxchl = 0;
    for (uint32_t i = 0; i < SFX_MAX; i++) {
        if (m_sc[i].playing())
            sfxchl++;
    }

    return sfxchl;
}


uint32_t Sound::playSFX(SoundFX *sndfx) {

    uint32_t i;

    SFXChannel *c;

    if ((!m_open) || (sndfx->m_sample == NULL))
        return 0xFFFF;

    for (i = 0; i < SFX_MAX; i++) {
        if ((m_sc[i].m_stop == true) && (m_sc[i].m_pause == false))
            break;
    }
    if (i == SFX_MAX) {
        return 0xFFFF;
    }

    c = &m_sc[i];

    EnterCriticalSection(&m_critSecRtp);

    c->m_sample = sndfx->m_sample;
    c->m_freqfactor = (sndfx->m_freq << 16) / (m_freqmix << 8);
    c->m_position = 0;
    c->m_length = sndfx->m_length << 8;
    c->m_loop = sndfx->m_loop;  // set loop

    // set volume
    c->m_gblvol = m_globalVolume;
    c->setVolume(sndfx->m_volume);

    c->play();

    LeaveCriticalSection(&m_critSecRtp);

    return i + MOD_MAX;
}


void Sound::stopSFX(uint32_t chl) {

    if (!m_open)
        return;

    // aggiusto l'indice
    chl -= MOD_MAX;

    EnterCriticalSection(&m_critSecRtp);

    if (chl < SFX_MAX)
        m_sc[chl].stop();
        //m_sc[chl].m_sample = 0;

    LeaveCriticalSection(&m_critSecRtp);
}



// estraggo dalla sequenza pattern il numero maggiore
// ottengo quindi il numero di pattern presenti
uint32_t snd_getNumPattern(ModHeader *mh) {

    uint32_t i, max;

    max = 0;
    for (i = 0; i < mh->numSequence; i++) {
        if (max < mh->sequences[i])
            max = mh->sequences[i];
    }

    return max+1;
}

uint32_t Sound::playMod(Module *mod) {

    uint32_t start, now, i;
    uint32_t j;

    ModChannel *c;

    if ((!m_open) || (mod->m_mh == NULL))
        return 0xFFFF;

    for (j = 0; j < MOD_MAX; j++) {
        if ((m_mc[j].m_stop == true) && (m_mc[j].m_pause == false))
            break;
    }
    if (j == MOD_MAX) {
        //LeaveCriticalSection(&critSecRtp);
        return 0xFFFF;
    }

    c = &m_mc[j];


    EnterCriticalSection(&m_critSecRtp);

    // salvo puntatore
    c->m_modheader = (ModHeader *)mod->m_mh;

    c->m_modpattern = (ModPattern *)((uint32_t)c->m_modheader + sizeof(ModHeader));

    // calcolo dati sample.. 1..31 ma tengo lo 0 per facilitarmi
    // successivamente la gestione
    start = (uint32_t)c->m_modpattern + sizeof(ModPattern) * snd_getNumPattern(c->m_modheader);
    now = 0;

    // setto a 0 per evitare di processare sample usati per il silenzio
    c->m_sdata[0] = 0;
    c->m_sfinetune[0] = 0;
    for (i = 1; i < MOD_MAXSAMPLE; i++) {
        if (c->m_modheader->samples[i-1].length != 0) {

            c->m_slength[i] = btol16(c->m_modheader->samples[i-1].length) << 9; // *2 (in word...) e fixo
            c->m_sloopstart[i] = btol16(c->m_modheader->samples[i-1].loopstart) << 9;
            if (btol16(c->m_modheader->samples[i-1].looplength) <= 1)
                c->m_slooplength[i] = 0;
            else
                c->m_slooplength[i] = btol16(c->m_modheader->samples[i-1].looplength) << 9;

            c->m_svol[i] = c->m_modheader->samples[i-1].volume;
            c->m_sfinetune[i] = (uint32_t)c->m_modheader->samples[i].finetune;
            

            c->m_sdata[i] = (start + now);
            now += btol16(c->m_modheader->samples[i-1].length)*2;
        }
        else
            c->m_sdata[i] = 0;       
    }


    // setto dati di default

    c->m_bytextick = m_freqmix/(125*2/5);
    c->m_bytecnt = 0;

    // setto anche tickcnt in modo che scatti immediatamente e mi legga le prime 4 note
    c->m_tickxdivision = 6;
    c->m_tickcnt = c->m_tickxdivision;

    c->m_seq = 0;
    c->m_pattern = c->m_modheader->sequences[c->m_seq];
    c->m_note = 0*4;

    if ( (c->m_modheader->restart == 127) || (c->m_modheader->numSequence <= c->m_modheader->restart) )
        c->m_restart = 0;
    else
        c->m_restart = c->m_modheader->restart;

    c->m_jumpseq = c->m_jumpnote = 0xFFFFFF;

    c->m_delaypattern = 0;

    // setto default pan
    c->m_pan[0] = c->m_pan[3] = 64;
    c->m_pan[1] = c->m_pan[2] = 192;
   
    // pulisco dati essenziali
    for (i = 0; i < MOD_MAXCHANNEL; i++) {
        c->m_sample[i] = 0;
        c->m_notefreq[i] = 0;
    }

//    m_pauseMod = false;
    //m_stopMod = false;

    // set loop
    c->m_loop = mod->m_loop;

    // set volume
    c->m_gblvol = m_globalVolume;
    c->setVolume(mod->m_volume);

    c->play();
    
    LeaveCriticalSection(&m_critSecRtp);

    return j;
}


void Sound::stopMod(uint32_t chl) {

    if (!m_open)
        return;

    EnterCriticalSection(&m_critSecRtp);

    if (chl < MOD_MAX)
        m_mc[chl].stop();
        //m_mc[chl].m_modheader = 0;

    LeaveCriticalSection(&m_critSecRtp);
}



// for debug...
#define from 0
#define to 3

void Sound::updateModSFX() {

    uint32_t i, p, j;
    int32_t l, r, s;
    uint32_t freqsample;

    uint32_t ext_sample;
    uint32_t ext_command, ext_x, ext_y, ext_xy;
    uint32_t ext_notefreq;

    ModChannel *c;
    SFXChannel *x;


    p = 0;
    while (p < m_bufmixframe << m_stereo) {
    
    l = r = 0;
    for (j = 0; j < MOD_MAX; j++) {
        // salto se non deve suonare
        if ((m_mc[j].m_stop == true) || (m_mc[j].m_pause == true))
            continue;

        c = &m_mc[j];

        if (c->m_tickcnt == c->m_tickxdivision) {

            if (c->m_delaypattern == 0) {

               // nuove note
                for (i = from; i < to+1; i++) {

                    // prendo la nuova nota
                    uint32_t n = c->m_modpattern[c->m_pattern].notes[i + c->m_note].bits;

                    ext_command = (n & 0x000F0000) >> 16;
                    ext_x = n >> 28;
                    ext_y = (n & 0x0F000000) >> 24;
                    ext_xy = (n & 0xFF000000) >> 24;
                    ext_sample = ((n & 0x00F00000) >> 20) | (n & 0xF0);
                    ext_notefreq = ((n & 0xF) << 8) | ((n & 0xFF00) >> 8);

                    // estraggo dati comandi
                    c->m_command[i] = ext_command;
                    c->m_opx[i] = ext_x; c->m_opy[i] = ext_y;
                    c->m_opxy[i] = ext_xy;


                    // resetta volume e update sample
                    if (ext_sample != 0) {
                        c->m_sample[i] = ext_sample;
                        c->m_clcvol[i] = c->m_svol[ext_sample];
                        c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                    }

                    // resetta posizione e update notefreq (no se effect 3, 5, ED)
                    if (ext_notefreq != 0) {
                        if ((c->m_command[i] != 0x03) && (c->m_command[i] != 0x05) && ((c->m_command[i]<<4)+c->m_opx[i] != 0xED)) {
                            c->m_position[i] = 0;
                            c->m_notefreq[i] = amiganote[noteidx[ext_notefreq] + 60*c->m_sfinetune[c->m_sample[i]] ];
                        }
                    }


                    // se ho un sample nel canale...
                    if (c->m_sample[i] != 0) {
                        freqsample = m_samplefreq[c->m_notefreq[i]];
                        c->m_freqfactor[i] = freqsample;
                    }


                    switch (c->m_command[i]) {

                        // effetto 0x00 Arpeggio
                        case 0x00 : {

                            if (c->m_opxy[i] == 0)
                                break;

                            c->m_arpeggioidx[i] = 0;
                            c->m_arpeggiofq[i] = c->m_freqfactor[i];
           
                            /*c->m_arpeggiofqx[i] = (samplefreq[amiganote[noteidx[c->m_notefreq[i]] + c->m_opx[i] ]] << 8) / (m_freqmix << 8);
                            c->m_arpeggiofqy[i] = (samplefreq[amiganote[noteidx[c->m_notefreq[i]] + c->m_opy[i] ]] << 8) / (m_freqmix << 8);*/
                            c->m_arpeggiofqx[i] = m_samplefreq[amiganote[noteidx[c->m_notefreq[i]] + c->m_opx[i] ]];
                            c->m_arpeggiofqy[i] = m_samplefreq[amiganote[noteidx[c->m_notefreq[i]] + c->m_opy[i] ]];
                        

                            break;
                        }

                        // effetto 0x0A (10) volume slide 
                        // effetto 0x06  vibrato + vol slide
                        // effetto 0x05  vibrato + vol slide
                        case 0x05 :
                        case 0x06 :
                        case 0x0A :

                            if (c->m_opxy[i] == 0) {
                                c->m_voldelta[i] = 0;
                                break;
                            }
    
                            if (c->m_opx[i] != 0)
                                c->m_voldelta[i] = c->m_opx[i];
                            else 
                                c->m_voldelta[i] = -(int32_t)c->m_opy[i];

                        break;
                    

                        // effetto 0x01 (1) slide (portamento) up
                        case 0x01 : {
                            c->m_slideupdown[i] = c->m_notefreq[i];
                            break;
                        }

                        // effetto 0x02 (2) slide (portamento) down
                        case 0x02 : {
                            c->m_slideupdown[i] = c->m_notefreq[i];
                            break;
                        }

                        // effetto 0x03 (3) slide to note
                        case 0x03 : {

                            if (ext_notefreq != 0) {
                                c->m_slidetonote[i] = amiganote[noteidx[ext_notefreq] + 60*c->m_sfinetune[c->m_sample[i]] ];
                            }
                            else {
                                if (c->m_slidetonote[i] == 0)
                                    c->m_slidetonote[i] = amiganote[noteidx[c->m_notefreq[i]] + 60*c->m_sfinetune[c->m_sample[i]] ];
                            }

                            if (c->m_opxy[i] != 0)
                                c->m_slidetonotedelta[i] = c->m_opxy[i];

                            break;
                        }

                        // effetto 0x04 (4) vibrato
                        case 0x04 : {

                            if (c->m_opxy[i] == 0) {
                                break;
                            }

                            c->m_vibratospeed[i] = c->m_opx[i];
                            c->m_vibratodepth[i] = c->m_opy[i];

                            break;
                        }

                        case 0x09 : {

                            c->m_position[i] = (c->m_opx[i] << 12) + (c->m_opy[i] << 8);

                            break;
                        }
                    

                        // effetto 0xC () set volume
                        case 0x0C : {
                            c->m_clcvol[i] = c->m_opxy[i];
                            c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                            break;
                        }

                        // effetto 0x0F (15) set vel/tempo
                        case 0x0F : {
                            if (c->m_opxy[i] <= 32)
                                c->m_tickxdivision = c->m_opxy[i];
                            else
                                c->m_bytextick = m_freqmix / (c->m_opxy[i]*2 / 5);

                            break;
                        }


                        // pattern jump (10)
                        case 0x0B : {
                            c->m_jumpseq = c->m_opxy[i];
                            c->m_jumpnote = 0;
                            break;
                        }

                        // comando pattern break (13)
                        case 0x0D : {
                            // se il prossimo nella sequenza non esiste
                            if ((c->m_seq+1) >= c->m_modheader->numSequence) {
                                // se ho il loop riparto
                                if (c->m_loop) {
                                    //c->m_jumpseq = 0;
                                    c->m_jumpseq = c->m_restart;
                                    c->m_jumpnote = (c->m_opx[i]*10+c->m_opy[i]) << 2;
                                }
                                // altrimenti vado alla fine
                                else {
                                    c->m_jumpnote = 63 << 2;
                                }
                      
                            }
                            // altrimenti passo al prossimo nella sequenza
                            else {
                                c->m_jumpseq = c->m_seq+1;
                                c->m_jumpnote = (c->m_opx[i]*10+c->m_opy[i]) << 2;
                            }

                            break;
                        }


                        // exctended effect
                        case 0x0E : {

                            switch (c->m_opx[i]) {

                                // effect 0xEA fine volume slide up
                                case 0xA : {
                                    c->m_clcvol[i] += c->m_opy[i];
                                    c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                                    break;
                                }

                                // effect 0xEB fine volume slide down
                                case 0xB : {
                                    c->m_clcvol[i] -= c->m_opy[i];
                                    c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                                    break;
                                }

                                // effect 0xEC cut sample
                                case 0xC : {
                                    c->m_tickcutsample[i] = c->m_opy[i];
                                    break; 
                                }

                                // effect 0xED note delay o delay sample (13)
                                case 0xD : {
                                    c->m_delaynote[i] = c->m_opy[i]-1;
                                    c->m_delaynotefreq[i] = ext_notefreq;
                                    break;
                                }

                                // effect 0xEE pattern delay
                                case 0xE : {
                                    c->m_delaypattern = c->m_opy[i];
                                    break;
                                }

                            } // switch
                        }
                
                
                    } // switch

                }


                // aggiorno note, pattern, sequenza
                if (c->m_jumpseq != 0xFFFFFF) {
                    c->m_seq = c->m_jumpseq;
                    c->m_pattern = c->m_modheader->sequences[c->m_seq];
                    c->m_note = c->m_jumpnote;
                    c->m_jumpseq = 0xFFFFFF;
                }
                else {
                    c->m_note += 4;
                    if (c->m_note == 256) {
                        c->m_note = 0;
                        c->m_seq++;
                        if (c->m_seq >= c->m_modheader->numSequence) {
                            if (c->m_loop) {
                                //c->m_seq = 0;
                                c->m_seq = c->m_restart;
                            }
                            // stoppo
                            else {
                                // stoppo canale
                                c->stop();

                                continue;
                            }
                        }

                        c->m_pattern = c->m_modheader->sequences[c->m_seq];
                    }
                }


            } // if delaypattern != 0
            else {
                c->m_delaypattern--;
            }


            c->m_tickcnt = 0;
        }
        else {

            if (c->m_bytecnt == c->m_bytextick) {
                c->m_tickcnt++;
                c->m_bytecnt = 0;

                if (c->m_tickcnt != c->m_tickxdivision) {

                // update dell'effetto... (gli effetti sono tick dipendenti)
                for (i = from; i < to+1; i++) {

                    
                    switch (c->m_command[i]) {
 
                        // effetto 0x00 Arpeggio
                        case 0x00 : {
                            // se 0 no arpeggio in pratica
                            if (c->m_opxy[i] == 0)
                                break;

                            c->m_arpeggioidx[i]++;
                            if (c->m_arpeggioidx[i] == 3)
                                c->m_arpeggioidx[i] = 0;
                            switch (c->m_arpeggioidx[i]) {
                              case 0:
                                  c->m_freqfactor[i] = c->m_arpeggiofq[i];
                                  break;
                              case 1:
                                  c->m_freqfactor[i] = c->m_arpeggiofqx[i];
                                  break;
                              case 2:
                                  c->m_freqfactor[i] = c->m_arpeggiofqy[i];
                                  break;
                            }

                            break;
                        }

   
                        // effetto 0x01 (1) slide (portamento) up
                        case 0x01 : {
                            c->m_slideupdown[i] -= c->m_opxy[i];
                            freqsample = m_samplefreq[c->m_slideupdown[i]]; // * finetune
                            if (freqsample != 0)
                                c->m_freqfactor[i] = freqsample;

                            c->m_notefreq[i] = c->m_slideupdown[i];

                            break;
                        }

                        // effetto 0x02 (2) slide (portamento) down
                        case 0x02 : {
                            c->m_slideupdown[i] += c->m_opxy[i];
                            freqsample = m_samplefreq[c->m_slideupdown[i]]; // * finetune
                            if (freqsample != 0)
                                c->m_freqfactor[i] = freqsample;

                            c->m_notefreq[i] = c->m_slideupdown[i];

                            break;
                        }

                        // effetto 0x03 (3) slide to note
                        case 0x05 :
                        case 0x03 :
                            //uint32_t refnote = actual[i].notefreq;
                            if (c->m_notefreq[i] > c->m_slidetonote[i]) {
                                c->m_notefreq[i] -= c->m_slidetonotedelta[i];
                                if ((c->m_notefreq[i] < c->m_slidetonote[i]) || ((int32_t)c->m_notefreq[i] < 0))
                                    c->m_notefreq[i] = c->m_slidetonote[i];
                            }

                            if (c->m_notefreq[i] < c->m_slidetonote[i]) {
                                c->m_notefreq[i] += c->m_slidetonotedelta[i];
                                if ((c->m_notefreq[i] > c->m_slidetonote[i]))
                                    c->m_notefreq[i] = c->m_slidetonote[i];
                            }

                            freqsample = m_samplefreq[c->m_notefreq[i]]; // * finetune
                            //c->m_freqfactor[i] = (freqsample << 8) / (m_freqmix << 8);
                            c->m_freqfactor[i] = freqsample;

                            // anche volume slide
                            if (c->m_command[i] == 0x05) {
                                c->m_clcvol[i] += c->m_voldelta[i];
                                if ((int32_t)c->m_clcvol[i] < 0)
                                    c->m_clcvol[i] = 0;
                                if (c->m_clcvol[i] > 64)
                                    c->m_clcvol[i] = 64;
                                c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                            }

                          break;
                        

                        // effetto 0x04 (4) vibrato
                        case 0x06 :
                        case 0x04 :

                            if (c->m_vibratoidx[i] >= 32)
                                freqsample = m_samplefreq[((c->m_notefreq[i] << 8) - (sine[c->m_vibratoidx[i]-32] * (c->m_vibratodepth[i]))) >> 8];
                            else
                                freqsample = m_samplefreq[((c->m_notefreq[i] << 8) + (sine[c->m_vibratoidx[i]] * (c->m_vibratodepth[i]))) >> 8];

                            c->m_vibratoidx[i] += c->m_vibratospeed[i];
                            if (c->m_vibratoidx[i] >= 64)
                                c->m_vibratoidx[i] -= 64;

                            //c->m_freqfactor[i] = (freqsample << 8) / (m_freqmix << 8);
                            c->m_freqfactor[i] = freqsample;

                            // anche volume slide
                            if (c->m_command[i] == 0x06) {
                                c->m_clcvol[i] += c->m_voldelta[i];
                                if ((int32_t)c->m_clcvol[i] < 0)
                                    c->m_clcvol[i] = 0;
                                if (c->m_clcvol[i] > 64)
                                    c->m_clcvol[i] = 64;
                                c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;
                            }
         
                          break;
                        
                        
                        // effetto 0x0A (10) volume slide
                        case 0x0A : {
                            c->m_clcvol[i] += c->m_voldelta[i];
                            if ((int32_t)c->m_clcvol[i] < 0)
                                c->m_clcvol[i] = 0;
                            if (c->m_clcvol[i] > 64)
                                c->m_clcvol[i] = 64;
                            c->m_glbvol[i] = (c->m_clcvol[i] * c->m_volume) >> 6;

                            break;
                        }


                        // extended effect
                        case 0x0E : {
 
                            switch (c->m_opx[i]) {

                                // effect 0xEC cut sample
                                case 0xC : {

                                    if (c->m_tickcutsample[i] > 0) {
                                        c->m_tickcutsample[i]--;
                                        if (c->m_tickcutsample[i] == 0)
                                            c->m_glbvol[i] = 0;
                                    }
                                    break;
                                }

                                // effect 0xED note delay o delay sample (13)
                                case 0xD : {

                                    if (c->m_delaynote[i] == 0xFFFFFFFF) {
                                        c->m_notefreq[i] = c->m_delaynotefreq[i];
                                        c->m_delaynote[i] = 0x00FFFFFF;
                                        freqsample = m_samplefreq[c->m_notefreq[i]]; // * finetune
                                        //c->m_freqfactor[i] = (freqsample << 8) / (m_freqmix << 8);
                                        c->m_freqfactor[i] = freqsample;
                                    }
                                    else {
                                        if (c->m_delaynote[i] != 0x00FFFFFF)
                                            c->m_delaynote[i]--;
                                    }

                                }

                            } // switch
                        }

                        

                    } // switch


                } // for

                } // l'if riparatore :)

            }
            else
                c->m_bytecnt++;

        }


        for (i = from; i < to+1; i++) {

            uint32_t p;

            //if (m_sample[i] != 0) {
            if (c->m_sdata[c->m_sample[i]] != 0) {
                if (c->m_slooplength[c->m_sample[i]] == 0) {
                    if (c->m_position[i] <= c->m_slength[c->m_sample[i]]) {

                        s = (*(int8_t *)( c->m_sdata[c->m_sample[i]] + (c->m_position[i] >> 8)));

                        if (m_stereo) {
                            p = (c->m_pan[i] * c->m_glbvol[i]) >> 8;
                            l += (c->m_glbvol[i] - p) * s;
                            r += p * s;
                        }
                        else
                            l += c->m_glbvol[i] * s;
                    }

                    c->m_position[i] += c->m_freqfactor[i];
                }
                // with loop
                else {             
                    if (c->m_position[i] > (c->m_sloopstart[c->m_sample[i]] + c->m_slooplength[c->m_sample[i]]) )
                        c->m_position[i] -= c->m_slooplength[c->m_sample[i]];
                        
                    s = (*(int8_t *)( c->m_sdata[c->m_sample[i]] + (c->m_position[i] >> 8)));

                    if (m_stereo) {
                        p = (c->m_pan[i] * c->m_glbvol[i]) >> 8;
                        l += (c->m_glbvol[i] - p) * s;
                        r += p * s;
                    }
                    else
                        l += c->m_glbvol[i] * s;

                    c->m_position[i] += c->m_freqfactor[i];
                }
            }

        } // for ProTrackerChannel

        } // for ModChannel



        // aggiorno i canali sfx
        for (i = 0; i < SFX_MAX; i++) {
            if ((m_sc[i].m_stop == true) || (m_sc[i].m_pause == true))
                continue;

            x = &m_sc[i];

            if (x->m_loop) {
                if ( x->m_position > x->m_length )
                    x->m_position -= x->m_length;
            }

            if ( x->m_position <= x->m_length ) {
                s = (*(uint8_t *)( (uint32_t)x->m_sample + (x->m_position >> 8)));
                s -= 128;

                s *= x->m_volume;

                if (m_stereo) {
                    l += s;
                    r += s;
                }
                else
                    l += s;

                x->m_position += x->m_freqfactor;
            }
            else {
                x->stop();
            }

        } // for channel


        // clippo
        l >>= 7;
        if (l > 127)
            l = 127;
        else
            if (l < -128)
                l = -128;
        l += 128;

        *(uint8_t *)((uint32_t)m_pbufmix + p) = (uint8_t)l;
        p++;

        if (m_stereo) {
            r >>= 7;
            if (r > 127)
                r = 127;
            else
                if (r < -128)
                    r = -128;
            r += 128;

            *(uint8_t *)((uint32_t)m_pbufmix + p) = (uint8_t)r;
            p++;
        }

        //p += 1 << m_stereo;
    } // while buffer

    //return note;
}



DWORD WINAPI Sound::update(LPVOID lpParameter) {

    Sound *snd;
    MSG msg;
    WAVEHDR *pwavehdr;
	//DWORD dwWait;


    snd = (Sound *)lpParameter;
	if (snd == NULL)
	    return -1;


    //while (!snd->m_exitThread) {
	while ((WaitForSingleObject(snd->m_killEvent, 5) != 0)) {


        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {

            if (msg.message == MM_WOM_DONE) {  
				
                pwavehdr = (WAVEHDR *)msg.lParam;
			    if (pwavehdr == NULL)
				    break;


                // recupero il buffer ormai usato
                snd->m_pbufmix = (uint8_t *)pwavehdr->lpData;

                // entro nella sezione critica e scrivo bufmix
                EnterCriticalSection(&snd->m_critSecRtp);

                // update mod & sfx
                snd->updateModSFX();

                LeaveCriticalSection(&snd->m_critSecRtp);

                // unpreparo il wavehdr
                waveOutUnprepareHeader(snd->m_hwaveout, pwavehdr, sizeof(WAVEHDR));

                // e reinserisco il buffer ora riempito
                ZeroMemory(pwavehdr, sizeof(WAVEHDR));
                pwavehdr->dwBufferLength = snd->m_bufmixframe << snd->m_stereo; // *2 stereo
                pwavehdr->lpData = (char *)snd->m_pbufmix;

                waveOutPrepareHeader(snd->m_hwaveout, pwavehdr, sizeof(WAVEHDR));

                waveOutWrite(snd->m_hwaveout, pwavehdr, sizeof(WAVEHDR));

            }// if (msg.message == MM_WOM_DONE)

        }// while peekmessage
        
    }// while (1)


    SetEvent(snd->m_exitEvent);


    return 0;
}


void Sound::pauseSFX() {

    if (!m_open)
        return;

    EnterCriticalSection(&m_critSecRtp);

    //m_pauseSFX = true;
    for (uint32_t i = MOD_MAX; i < SFX_MAX; i++)
        m_sc[i-MOD_MAX].pause();
    
    LeaveCriticalSection(&m_critSecRtp);
}

void Sound::resumeSFX() {

    if (!m_open)
        return;

    EnterCriticalSection(&m_critSecRtp);

    //m_pauseSFX = false;
    for (uint32_t i = MOD_MAX; i < SFX_MAX; i++)
        m_sc[i-MOD_MAX].resume();
    
    LeaveCriticalSection(&m_critSecRtp);
}


void Sound::pauseMod() {

    if (!m_open)
        return;

    EnterCriticalSection(&m_critSecRtp);

    //m_pauseMod = true;
    for (uint32_t i = 0; i < MOD_MAX; i++)
        m_mc[i].pause();

    LeaveCriticalSection(&m_critSecRtp);
}

void Sound::resumeMod() {

    if (!m_open)
        return;

    EnterCriticalSection(&m_critSecRtp);

    //m_pauseMod = false;
    for (uint32_t i = 0; i < MOD_MAX; i++)
        m_mc[i].resume();
    
    LeaveCriticalSection(&m_critSecRtp);
}


void Sound::suspend() {

    if (!m_open)
        return;

    /*pauseSFX();
    pauseMod();*/
    waveOutPause(m_hwaveout);
    SuspendThread(m_thread);
}

void Sound::resume() {

    if (!m_open)
        return;

    /*resumeSFX();
    resumeMod();*/
    ResumeThread(m_thread);
    waveOutRestart(m_hwaveout);
}


void Sound::setVolume(uint32_t v) {

    uint32_t i;

    if (v > 64)
        v = 64;

    m_globalVolume = v;

    for (i = 0; i < MOD_MAX; i++) {
        m_mc[i].m_gblvol = m_globalVolume;
        m_mc[i].setVolume(m_mc[i].m_chlvol);
    }

    for (i = 0; i < SFX_MAX; i++) {
        m_sc[i].m_gblvol = m_globalVolume;
        m_sc[i].setVolume(m_sc[i].m_chlvol);
    }
}

uint32_t Sound::getVolume() {

    return m_globalVolume;
}


}

