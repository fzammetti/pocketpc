/* ****************************************************************************

HSS Utility class - 12/03/2003
    by Thomas Maniero - last modified 12/03/2003

todo:

**************************************************************************** */

#ifndef _HSSUTILITY_H
#define _HSSUTILITY_H


#include "hssImpExp.h"


#include "hssTypes.h"


#define MAX_PATHNAME 512



class HSS_CLS_API hssUtility {

public:
    static HSS_API u32 fullPathName(TCHAR pathname[MAX_PATHNAME], const TCHAR *filename);

    static HSS_API u16 btol16(u16 big);
    static HSS_API u32 btol32(u32 big);

    static HSS_API s8 getDigit(s8 a);
    static HSS_API s8 getUpAlpha(s8 a);
};


#endif
