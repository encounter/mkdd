
#include "Osako/CardMgr.h"
#include "Osako/System.h"

static u8 aaWorkAreaBuffer[CARD_NUM_CHANS][CARD_WORKAREA_SIZE] ALIGN(32);

// clang-format off
#define CARD_ASSERT(chan, flag) \
    JUT_ASSERT((((msaCardData[ chan ].mProcessFlag) & (flag) ) != 0))
// clang-format on

namespace CardMgr
{
    u8 msProbeSlot;
    CardData msaCardData[CARD_NUM_CHANS];

    void create()
    {
        CARDInit();

        for (int i = 0; i < CARD_NUM_CHANS; i++)
        {
            msaCardData[i].mProcessFlag = mcNone;
            msaCardData[i].mTaskStatus = 0;
            msaCardData[i].mSaveFile = nullptr;
            msaCardData[i].mWorkArea = aaWorkAreaBuffer[i];
        }
    }

    void probe()
    {
        s32 status = CARDProbeEx(msProbeSlot, &msaCardData[msProbeSlot].mMemSize, &msaCardData[msProbeSlot].mSectorSize);

        if (status == CARD_RESULT_NOCARD)
        {
            msaCardData[msProbeSlot].mProcessFlag &= ~mcClear;
            msaCardData[msProbeSlot].mProcessFlag &= ~mcError;
        }

        msaCardData[msProbeSlot].mProbeStatus = status;
        msaCardData[msProbeSlot].mProcessFlag |= mcProbe;
        msProbeSlot++;
        msProbeSlot &= 1;
    }

    bool mount(s32 chan)
    {
#line 76
        JUT_MINMAX_ASSERT(0, chan, 2);

        if (msaCardData[chan].mTaskStatus == 0)
        {
            CARD_ASSERT(chan, mcProbe);

            if ((msaCardData[chan].mProcessFlag & mcError) == 0)
            {
                msaCardData[chan].mTaskStatus = 1;
                return SYSTEM_RequestTask(mountTask, (void *)chan, nullptr);
            }
        }
        return false;
    }

    void mountTask(void *arg)
    {
        s32 chan = (s32)arg;

        msaCardData[chan].mProcessFlag &= ~mcClear;
        msaCardData[chan].mCardStatus = CARDMount(chan, msaCardData[chan].mWorkArea, nullptr);

        switch (msaCardData[chan].mCardStatus)
        {
        case CARD_RESULT_IOERROR:
            msaCardData[chan].mProcessFlag |= mcError;
            break;
        case CARD_RESULT_ENCODING:
        case CARD_RESULT_BROKEN:
        case CARD_RESULT_READY:
            msaCardData[chan].mProcessFlag |= mcMount;
            break;
        }

        msaCardData[chan].mTaskStatus = 2;
    }

    bool check(s32 chan)
    {
        if (msaCardData[chan].mTaskStatus == 0)
        {
#line 124
            CARD_ASSERT(chan, mcMount);

            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(checkTask, (void *)chan, nullptr);
        }
        return false;
    }

    void checkTask(void *arg)
    {
        s32 chan = (s32)arg;

        msaCardData[chan].mCardStatus = CARDCheck(chan);
        if (msaCardData[chan].mCardStatus == CARD_RESULT_READY)
            CARDFreeBlocks(chan, &msaCardData[chan].mByteNotUsed, &msaCardData[chan].mFilesNotUsed);

        if (msaCardData[chan].mCardStatus == CARD_RESULT_IOERROR)
            msaCardData[chan].mProcessFlag |= mcError;

        msaCardData[chan].mProcessFlag |= mcCheck;
        msaCardData[chan].mTaskStatus = 2;
    }

    bool format(s32 chan)
    {
        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(formatTask, (void *)chan, nullptr);
        }

        return false;
    }

    void formatTask(void *arg)
    {
        s32 chan = (s32)arg;
        msaCardData[chan].mCardStatus = CARDFormat(chan);

        if (msaCardData[chan].mCardStatus == CARD_RESULT_IOERROR)
            msaCardData[chan].mProcessFlag |= mcError;

        msaCardData[chan].mProcessFlag |= mcFormat;
        msaCardData[chan].mTaskStatus = 2;
    }

    s32 openFile(s32 chan, SaveFile *pSaveFile)
    {
#line 192
        CARD_ASSERT(chan, mcCheck);

        msaCardData[chan].mSaveFile = pSaveFile;

        if (pSaveFile->getAccessWay() == 1)
            msaCardData[chan].mCardStatus = CARDOpen(chan, pSaveFile->getFileName(), &msaCardData[chan].mFileInfo);
        else
            msaCardData[chan].mCardStatus = CARDFastOpen(chan, pSaveFile->getFileNo(), &msaCardData[chan].mFileInfo);

        if (msaCardData[chan].mCardStatus == 0)
        {
            CARDGetStatus(chan, msaCardData[chan].mFileInfo.fileNo, &msaCardData[chan].mStat);
            msaCardData[chan].mProcessFlag |= mcOpen;
            msaCardData[chan].mProcessFlag |= mcGetStatus;
        }

        return msaCardData[chan].mCardStatus;
    }

    bool createFile(s32 chan, SaveFile *pSaveFile)
    {
        if (msaCardData[chan].mTaskStatus == 0)
        {
#line 221
            CARD_ASSERT(chan, mcCheck);

            msaCardData[chan].mTaskStatus = 1;
            msaCardData[chan].mSaveFile = pSaveFile;
            return SYSTEM_RequestTask(createTask, (void *)chan, 0);
        }
        return false;
    }

    void createTask(void *arg)
    {
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        msaCardData[chan].mCardStatus = CARDCreate(chan, pSaveFile->getFileName(), pSaveFile->getFileSize(), &msaCardData[chan].mFileInfo);

        switch (msaCardData[chan].mCardStatus)
        {
        case CARD_RESULT_IOERROR:
            msaCardData[chan].mProcessFlag |= mcError;
            break;
        case CARD_RESULT_READY:
            CARDGetStatus(chan, msaCardData[chan].mFileInfo.fileNo, &msaCardData[chan].mStat);
            msaCardData[chan].mProcessFlag |= mcGetStatus;
            break;
        }

        msaCardData[chan].mProcessFlag |= mcCreate;
        msaCardData[chan].mTaskStatus = 2;
    }

    bool read(s32 chan, SaveFile::FilePart filePart)
    {
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        pSaveFile->setPart(filePart);
        // clang-format off
#line 266
        JUT_ASSERT(pSaveFile->getBuf());
        JUT_ASSERT(!( pSaveFile->getOffset() & ( 512 - 1 ) ));
        // clang-format on

        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(readTask, (void *)chan, nullptr);
        }

        return false;
    }

    void readTask(void *arg)
    {
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        msaCardData[chan].mCardStatus = CARDRead(&msaCardData[chan].mFileInfo, pSaveFile->getBuf(), pSaveFile->getLength(), pSaveFile->getOffset());
        msaCardData[chan].mProcessFlag |= mcRead;
        msaCardData[chan].mTaskStatus = 2;
    }

    bool write(s32 chan, SaveFile::FilePart filePart)
    {
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        pSaveFile->setPart(filePart);
        pSaveFile->fetch();
        pSaveFile->setCheckData(OSGetTime());

        // clang-format off
#line 303
        JUT_ASSERT(pSaveFile->getBuf());
        JUT_ASSERT(!( pSaveFile->getLength() & ( msaCardData[ chan ].mSectorSize - 1 ) ));
        JUT_ASSERT(!( pSaveFile->getOffset() & ( msaCardData[ chan ].mSectorSize - 1 ) ));
        // clang-format on

        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(writeTask, (void *)chan, nullptr);
        }

        return false;
    }

    void writeTask(void *arg)
    {
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        msaCardData[chan].mCardStatus = CARDWrite(&msaCardData[chan].mFileInfo, pSaveFile->getBuf(), pSaveFile->getLength(), pSaveFile->getOffset());
        if (msaCardData[chan].mCardStatus == CARD_RESULT_IOERROR)
            msaCardData[chan].mProcessFlag |= mcError;

        msaCardData[chan].mProcessFlag |= mcWrite;
        msaCardData[chan].mTaskStatus = 2;
    }

    bool setStatus(s32 chan)
    {
#line 340
        CARD_ASSERT(chan, mcGetStatus);

        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(setStatusTask, (void *)chan, nullptr);
        }
        return false;
    }

    void setStatusTask(void *arg)
    {
        u8 icon;
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;
        CARDStat *stat = &msaCardData[chan].mStat;

        CARDSetBannerFormat(stat, pSaveFile->getBannerFormat());
        CARDSetCommentAddress(stat, pSaveFile->getCommentOffset());
        CARDSetIconAddress(stat, pSaveFile->getIconOffset());
        CARDSetIconAnim(stat, pSaveFile->getIconAnim());

        for (icon = 0; icon < pSaveFile->getIconNum(); icon++)
        {
            CARDSetIconFormat(stat, icon, pSaveFile->getIconFormat(icon));
            CARDSetIconSpeed(stat, icon, pSaveFile->getIconSpeed(icon));
        }

        if (icon < 7)
        {
            CARDSetIconSpeed(stat, icon, 0);
        }

        msaCardData[chan].mCardStatus = CARDSetStatus(chan, msaCardData[chan].mFileInfo.fileNo, stat);

        if (msaCardData[chan].mCardStatus == CARD_RESULT_IOERROR)
            msaCardData[chan].mProcessFlag |= mcError;

        msaCardData[chan].mProcessFlag |= mcSetStatus;
        msaCardData[chan].mTaskStatus = 2;
    }

    bool renameFile(s32 chan)
    {
#line 394
        CARD_ASSERT(chan, mcGetStatus);

        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(renameTask, (void *)chan, nullptr);
        }
        return false;
    }

    void renameTask(void *arg)
    {
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        char *newName = pSaveFile->getFileName();

        msaCardData[chan].mCardStatus = CARDRename(chan, msaCardData[chan].mStat.fileName, newName);

        if (msaCardData[chan].mCardStatus == CARD_RESULT_IOERROR)
            msaCardData[chan].mProcessFlag |= mcError;

        msaCardData[chan].mTaskStatus = 2;
    }

    bool deleteFile(s32 chan)
    {
#line 428
        CARD_ASSERT(chan, mcGetStatus);

        if (msaCardData[chan].mTaskStatus == 0)
        {
            msaCardData[chan].mTaskStatus = 1;
            return SYSTEM_RequestTask(deleteTask, (void *)chan, nullptr);
        }
        return false;
    }

    void deleteTask(void *arg)
    {
        s32 chan = (s32)arg;
        SaveFile *pSaveFile = msaCardData[chan].mSaveFile;

        if (pSaveFile->getAccessWay() == 1)
            msaCardData[chan].mCardStatus = CARDDelete(chan, pSaveFile->getFileName());
        else
            msaCardData[chan].mCardStatus = CARDFastDelete(chan, pSaveFile->getFileNo());

        msaCardData[chan].mTaskStatus = 2;
    }

    s32 closeFile(s32 chan)
    {
        msaCardData[chan].mCardStatus = 0;
        if (msaCardData[chan].mProcessFlag & mcOpen)
        {
            msaCardData[chan].mCardStatus = CARDClose(&msaCardData[chan].mFileInfo);
            msaCardData[chan].mProcessFlag &= ~mcOpen;
            msaCardData[chan].mProcessFlag |= mcClose;
        }

        return msaCardData[chan].mCardStatus;
    }

    s32 unmount(s32 chan)
    {
        msaCardData[chan].mCardStatus = 0;
        msaCardData[chan].mTaskStatus = 0;
        if (msaCardData[chan].mProcessFlag & mcMount)
        {
            msaCardData[chan].mCardStatus = CARDUnmount(chan);
            msaCardData[chan].mProcessFlag &= ~mcMount;
        }

        return msaCardData[chan].mCardStatus;
    }
}