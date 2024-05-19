#ifndef JASARAMSTREAM_H
#define JASARAMSTREAM_H

#include "JSystem/JAudio/System/JASTaskThread.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/dvd.h"

class JASChannel;

namespace JASDsp
{
    class TChannel;
}

class JASAramStream
{
public:
    typedef void (*StreamCallback)(u32, JASAramStream *, void *);
    static const u32 CHANNEL_MAX = 6;
    enum CallbackType
    {
        /* 0 */ CB_START,
        /* 1 */ CB_STOP,
    };

    // Used internally for passing data to task functions
    struct TaskData
    {
        /* 0x0 */ JASAramStream *stream;
        /* 0x4 */ u32 _4;
        /* 0x8 */ int _8;
    };

    struct Header
    {
        /* 0x00 */ u32 tag;
        /* 0x04 */ u8 _4[5];
        /* 0x09 */ u8 format;
        /* 0x0A */ u8 bits;
        /* 0x0C */ u16 channels;
        /* 0x0E */ u16 loop;
        /* 0x10 */ int _10;
        /* 0x14 */ u8 _14[4];
        /* 0x18 */ int loop_start;
        /* 0x1C */ int loop_end;
        /* 0x20 */ u32 block_size;
        /* 0x24 */ u8 _24[4];
        /* 0x28 */ u8 _28;
        /* 0x29 */ u8 _29[0x17];
    }; // Size: 0x40

    struct BlockHeader
    {
        /* 0x00 */ u32 tag;
        /* 0x04 */ u32 _4;
        /* 0x08 */ struct
        {
            s16 _0;
            s16 _2;
        } _8[6];
    }; // Size: 0x20

    /* 8029631C */ static void initSystem(u32, u32);
    /* 802963A8 */ JASAramStream();
    /* 8029649C */ void init(u32, u32, StreamCallback, void *);
    /* 8029655C */ bool prepare(s32, int);
    /* 80296618 */ bool start();
    /* 8029664C */ bool stop(u16);
    /* 80296684 */ bool pause(bool);
    /* 802966CC */ bool cancel();
    /* 80296710 */ u32 getBlockSamples() const;
    /* 8029673C */ static void headerLoadTask(void *);
    /* 8029676C */ static void firstLoadTask(void *);
    /* 80296848 */ static void loadToAramTask(void *);
    /* 80296868 */ static void finishTask(void *);
    /* 802968C8 */ static void prepareFinishTask(void *);
    /* 80296920 */ bool headerLoad(u32, int);
    /* 80296AE8 */ bool load();
    /* 80296D74 */ static s32 channelProcCallback(void *);
    /* 80296D94 */ static s32 dvdErrorCheck(void *);
    /* 80296DF0 */ static void channelCallback(u32, JASChannel *, JASDsp::TChannel *, void *);
    /* 80296E2C */ void updateChannel(u32, JASChannel *, JASDsp::TChannel *);
    /* 802974AC */ s32 channelProc();
    /* 80297658 */ void channelStart();
    /* 80297870 */ void channelStop(u16);

    void setPitch(f32 pitch) { mPitch = pitch; }
    void setVolume(f32 volume)
    {
        for (int i = 0; i < CHANNEL_MAX; i++)
        {
            mChannelVolume[i] = volume;
        }
    }

    void setPan(f32 pan)
    {
        for (int i = 0; i < CHANNEL_MAX; i++)
        {
            mChannelPan[i] = pan;
        }
    }

    void setFxmix(f32 fxMix)
    {
        for (int i = 0; i < CHANNEL_MAX; i++)
        {
            mChannelFxMix[i] = fxMix;
        }
    }

    void setDolby(f32 dolby)
    {
        for (int i = 0; i < CHANNEL_MAX; i++)
        {
            mChannelDolby[i] = dolby;
        }
    }

    void setChannelVolume(int channel, f32 volume)
    {
#line 288
        JUT_ASSERT(channel < CHANNEL_MAX);
        mChannelVolume[channel] = volume;
    }

    void setChannelPan(int channel, f32 pan)
    {
        JUT_ASSERT(channel < CHANNEL_MAX);
        mChannelPan[channel] = pan;
    }

    void setChannelFxmix(int channel, f32 fxMix)
    {
        JUT_ASSERT(channel < CHANNEL_MAX);
        mChannelFxMix[channel] = fxMix;
    }

    void setChannelDolby(int channel, f32 dolby)
    {
        JUT_ASSERT(channel < CHANNEL_MAX);
        mChannelDolby[channel] = dolby;
    }

    static u32 getBlockSize() { return sBlockSize; }

    /* 0x000 */ OSMessageQueue _000;
    /* 0x020 */ OSMessageQueue _020;
    /* 0x040 */ void *_040[16];
    /* 0x080 */ void *_080[4];
    /* 0x090 */ JASChannel *mChannels[CHANNEL_MAX];
    /* 0x0A8 */ JASChannel *_0a8;
    /* 0x0AC */ bool _0ac;
    /* 0x0AD */ bool _0ad;
    /* 0x0AE */ u8 _0ae;
    /* 0x0B0 */ int _0b0;
    /* 0x0B4 */ int _0b4;
    /* 0x0B8 */ u32 _0b8;
    /* 0x0BC */ int _0bc;
    /* 0x0C0 */ bool _0c0;
    /* 0x0C4 */ u32 _0c4;
    /* 0x0C8 */ f32 _0c8;
    /* 0x0CC */ DVDFileInfo mDvdFileInfo;
    /* 0x108 */ u32 _108;
    /* 0x10C */ int _10c;
    /* 0x110 */ u32 mBlock;
    /* 0x114 */ u8 _114;
    /* 0x118 */ u32 _118;
    /* 0x11C */ int _11c;
    /* 0x120 */ int _120;
    /* 0x124 */ int _124;
    /* 0x128 */ u16 _128;
    /* 0x12C */ int _12c;
    /* 0x130 */ s16 _130[CHANNEL_MAX];
    /* 0x13C */ s16 _13c[CHANNEL_MAX];
    /* 0x148 */ int _148;
    /* 0x14C */ u32 _14c;
    /* 0x150 */ StreamCallback mCallback;
    /* 0x154 */ void *mCallbackData;
    /* 0x158 */ u16 _158;
    /* 0x15A */ u16 mChannelNum;
    /* 0x15C */ u32 mBufCount;
    /* 0x160 */ u32 _160;
    /* 0x164 */ u32 _164;
    /* 0x168 */ bool mLoop;
    /* 0x16C */ u32 mLoopStart;
    /* 0x170 */ u32 mLoopEnd;
    /* 0x174 */ f32 mVolume;
    /* 0x178 */ f32 mPitch;
    /* 0x17C */ f32 mChannelVolume[CHANNEL_MAX];
    /* 0x194 */ f32 mChannelPan[CHANNEL_MAX];
    /* 0x1AC */ f32 mChannelFxMix[CHANNEL_MAX];
    /* 0x1C4 */ f32 mChannelDolby[CHANNEL_MAX];
    /* 0x1DC */ u16 _1dc[CHANNEL_MAX];

    static JASTaskThread *sLoadThread;
    static u8 *sReadBuffer;
    static u32 sBlockSize;
    static u32 sChannelMax;
};

#endif /* JASARAMSTREAM_H */