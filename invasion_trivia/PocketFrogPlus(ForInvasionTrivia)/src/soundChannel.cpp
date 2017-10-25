//////////////////////////////////////////////////////////////////////////////
//
//  Sound extension for PocketFrog ver 0.94
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////

#include "soundChannel.h"



namespace Frog {


Channel::Channel() {

    m_pause = false;
    m_stop = true;
}


void Channel::setVolume(uint32_t v) {

    if (v > 64)
        v = 64;

    m_chlvol = v;
    m_volume = (m_chlvol * m_gblvol) >> 6;
}


uint32_t Channel::getVolume() {

    return m_chlvol;
}


void Channel::setLoop(bool l) {

    m_loop = l;
}


bool Channel::getLoop() {

    return m_loop;
}


void Channel::play() {

    m_pause = m_stop = false;
}


void Channel::stop() {

    m_stop = true;
}

void Channel::pause() {

    if (m_stop == false)
        m_pause = true;
}

void Channel::resume() {

    if (m_stop == false)
        m_pause = false;
}


bool Channel::playing() {

    return ((m_pause == false) && (m_stop == false));
}


ModChannel::ModChannel() {

    m_modheader = NULL;

    for (uint32_t i = 0; i < MOD_MAXCHANNEL; i++) {

        m_vibratoidx[i] = 0;
        m_vibratospeed[i] = 9;
        m_vibratodepth[i] = 2;

        m_slidetonote[i] = 0;
    }
}

void ModChannel::setVolume(uint32_t v) {

    Channel::setVolume(v);

    for (uint32_t i = 0; i < MOD_MAXCHANNEL; i++) {
        m_glbvol[i] = (m_clcvol[i] * m_volume) >> 6;
    }
}


SFXChannel::SFXChannel() {

    m_sample = 0;
}


}