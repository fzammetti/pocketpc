//////////////////////////////////////////////////////////////////////////////
//
// PocketFrog - The Game Library for Pocket PC Devices
// Copyright 2002  Thierry Tremblay
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Thierry Tremblay makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef POCKETFROG_INTERNAL_INPUTDRIVER_H
#define POCKETFROG_INTERNAL_INPUTDRIVER_H

#include "driver.h"
#include "../input.h"

namespace Frog {
namespace Internal {

using InputDevice::KeyList;


    
//////////////////////////////////////////////////////////////////////////////
//
// InputDriver
//
//////////////////////////////////////////////////////////////////////////////

class InputDriver : public Driver
{
public:
    
    // Retrieve the list of button scan codes
    virtual const KeyList& GetKeyList() const = 0;
};



} // end of namespace Internal
} // end of namespace Frog



#endif
