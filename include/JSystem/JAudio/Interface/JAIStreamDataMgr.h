#ifndef JAUDIO_JAISTREAMDATAMGR_H
#define JAUDIO_JAISTREAMDATAMGR_H

#include "JSystem/JAudio/Interface/JAISound.h"

struct JAIStreamDataMgr
{
    virtual s32 getStreamFileEntry(JAISoundID) = 0;
    virtual ~JAIStreamDataMgr();
};

struct JAIStreamAramMgr
{
    virtual u32 newStreamAram(u32 *) = 0;
    virtual int deleteStreamAram(u32) = 0;
    virtual ~JAIStreamAramMgr();
};

#endif /* JAUDIO_JAISTREAMDATAMGR_H */