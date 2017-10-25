//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.94
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////

#include "soundData.h"

#include "PocketPC.h"

#include <stdio.h>


namespace Frog {


Module::Module() {

    m_mh = NULL;
    m_volume = 64;
    m_loop = false;

    m_delete = false;
}


Module::~Module() {

    if ((m_delete) && (m_mh)) {
        delete [] m_mh;
        m_mh = NULL;
        m_delete = false;
    }
}


void Module::setVolume(uint32_t v) {

    if (v > 64)
        v = 64;

    m_volume = v;
}


uint32_t Module::getVolume() {

    return m_volume;
}


void Module::setLoop(bool l) {

    m_loop = l;
}


bool Module::getLoop() {

    return m_loop;
}


bool Module::load(TCHAR *modname) {

    TCHAR pathname[MAX_PATH];
    FILE *f;
    uint32_t modsize;
    uint8_t *mod;

    if (PocketPC::GetFullPathName(modname, pathname) == 0)
        return false;

    if ((f = _tfopen(pathname, _T("rb"))) == NULL)
        return false;


    fseek(f, 0, SEEK_END);
    modsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (modsize == 0) {
        fclose(f);
        return false;
    }

    mod = new uint8_t[modsize];
    if (mod == 0) {
        fclose(f);
        return false;
    }

    fread(mod, modsize, 1, f);

    m_mh = mod;

    m_delete = true;

    return true;
}

bool Module::load(HINSTANCE hInstance, DWORD dwResourceID) {

    HRSRC hr; 
    HGLOBAL hg; 

    // trovo risorsa
    hr = FindResource(hInstance, MAKEINTRESOURCE(dwResourceID), TEXT("PTMOD")); 

    if (hr != NULL) { 

        // carico risorsa
        hg = LoadResource(hInstance, hr);

        if (hg != NULL) { 
            // lock resource
            m_mh = (uint8_t *)LockResource(hg); 
            if (m_mh != NULL) {
                m_delete = false;
                return true;
            }

        }

    }

    return false;
}




SoundFX::SoundFX() {

    m_sample = NULL;
    m_volume = 64;
    m_loop = false;

    m_delete = false;
}


SoundFX::~SoundFX() {

    if ((m_delete) && (m_sample)) {
        delete [] m_sample;
        m_sample = NULL;
        m_delete = false;
    }
}



void SoundFX::setVolume(uint32_t v) {

    if (v > 64)
        v = 64;

    m_volume = v;
}


uint32_t SoundFX::getVolume() {

    return m_volume;
}


void SoundFX::setLoop(bool l) {

    m_loop = l;
}


bool SoundFX::getLoop() {

    return m_loop;
}


bool SoundFX::load(TCHAR *wavname) {

    TCHAR pathname[MAX_PATH];
    FILE *f;


    if (PocketPC::GetFullPathName(wavname, pathname) == 0)
        return false;

    if ((f = _tfopen(pathname, _T("rb"))) == NULL)
        return false;

    if (fseek(f, 12, SEEK_SET) != 0)
        return false;

    WaveChunk wck;
    WaveHeader whdr;

    // read chunk fmt   
    if ((fread(&wck, sizeof(WaveChunk), 1, f) != 1) || (wck.ckID != WAVE_CHUNK_FMT)) {
        fclose(f);
        return false;
    }

    // read header
    fread(&whdr, sizeof(WaveHeader), 1, f);
    if ((whdr.nBitsPerSample != 8) || (whdr.nChannels != 1)) {
        fclose(f);
        return false;
    }

    // adjust position...
    if (wck.nChunkSize > sizeof(WaveHeader))
        fseek(f, wck.nChunkSize - sizeof(WaveHeader), SEEK_CUR);

    // find data chunk
    fread(&wck, sizeof(WaveChunk), 1, f);
    while (wck.ckID != WAVE_CHUNK_DATA) {
        fseek(f, wck.nChunkSize, SEEK_CUR);
        if (fread(&wck, sizeof(WaveChunk), 1, f) != 1) {
            fclose(f);
            return false;
        }
    }

    m_freq = whdr.nSamplesPerSec;
    m_length = wck.nChunkSize - 8;

    m_sample = new uint8_t[m_length];
    if (m_sample == 0) {
        fclose(f);
        return false;    
    }

    fread(m_sample, m_length, 1, f);

    m_delete = true;

    return true;
}

bool SoundFX::load(HINSTANCE hInstance, DWORD dwResourceID) {


    HRSRC hr; 
    HGLOBAL hg; 


    // trovo risorsa
    hr = FindResource(hInstance, MAKEINTRESOURCE(dwResourceID), TEXT("WAVE")); 

    if (hr != NULL) { 

        // carico risorsa
        hg = LoadResource(hInstance, hr);

        if (hg != NULL) { 

            WaveChunk wck;
            WaveHeader whdr;
            uint8_t *pwav;

            // lock resource
            pwav = (uint8_t *)((uint32_t)LockResource(hg) + 12);
            if (pwav == NULL) 
                return false;

            // first chunk, must be fmt
            memcpy(&wck, pwav, sizeof(WaveChunk));
            if (wck.ckID != WAVE_CHUNK_FMT)
                return false;

            pwav += sizeof(WaveChunk);

            memcpy(&whdr, pwav, sizeof(WaveHeader));
            if ((whdr.nBitsPerSample != 8) || (whdr.nChannels != 1))
                return false;

            // next chunk
            pwav += wck.nChunkSize;

            // trovo il chunk data
            memcpy(&wck, pwav, sizeof(WaveChunk));
            while (wck.ckID != WAVE_CHUNK_DATA) {
                pwav += sizeof(WaveChunk) + wck.nChunkSize;
                memcpy(&wck, pwav, sizeof(WaveChunk));
            }


            m_freq = whdr.nSamplesPerSec;
            m_length = wck.nChunkSize - 8;

            m_sample = (uint8_t *)((uint32_t)pwav + sizeof(WaveChunk));

            m_delete = false;

            return true;
        }

    }

    return false;
}

}
