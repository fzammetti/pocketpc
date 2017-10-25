/* ****************************************************************************

HSS error defs header - 12/03/2004
    by Thomas Maniero - last modified 12/03/2004

todo:

**************************************************************************** */

#ifndef _HSSERRDEFS_H
#define _HSSERRDEFS_H


// no error
#define HSS_OK                 0



// output format not supported
#define HSS_ERR_OUTPUT_FORMAT -1

// sound system already initialized
#define HSS_ERR_ALLOCATED     -2

// error initializing thread output device
#define HSS_ERR_THREAD        -3

// error initializing driver output device
#define HSS_ERR_DRIVER        -4



// not enough memory
#define HSS_ERR_MEMORY        -10



// file format not supported
#define HSS_ERR_FILE_FORMAT   -100

// file not found
#define HSS_ERR_FILE_NOTFOUND -200

// error loading file
#define HSS_ERR_FILE_BAD      -300



// playing the sound failed
#define HSS_ERR_PLAY         -1000



#endif
