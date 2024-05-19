
#include "JSystem/JAudio/Interface/JAIAudience.h"
#include "JSystem/JAudio/Interface/JAIStreamMgr.h"
#include "JSystem/JAudio/Interface/JAIStream.h"
#include "JSystem/JAudio/Interface/JAIStreamDataMgr.h"
#include "JSystem/JAudio/Interface/JAISound.h"
#include "JSystem/JAudio/System/JASMemPool.h"
#include "JSystem/JAudio/System/JASAudioThread.h"

// Move this shit to correct header + sym on shit
DECL_WEAK JASAudioThread* JASGlobalInstance<JASAudioThread>::sInstance;

static void JAIStream_JASAramStreamCallback_(u32 type, JASAramStream *param_2, void *stream)
{
    switch (type)
    {
    case 1:
        ((JAIStream *)(stream))->_2c5 = 1;
        break;
    case 0:
        ((JAIStream *)(stream))->_2c6 = 1;
        break;
    }
}

JAIStream::JAIStream(JAIStreamMgr *streamMgr, JAISoundStrategyMgr<JAIStream> *strategyMgr) : JSULink<JAIStream>(this)
{
    _290 = 0;
    mStrategyMgr = strategyMgr;
    mStreamMgr = streamMgr;
    mAramAddr = 0;
    _2c5 = 0;
    _2c6 = 0;
    for (int i = 0; i < CHANNEL_MAX; i++)
    {
        mChilds[i] = NULL;
    }
}

void JAIStream::JAIStreamMgr_startID_(JAISoundID soundID, s32 param_2,
                                      const JGeometry::TVec3f *pos, JAIAudience *audience_,
                                      int param_5)
{
    _298 = param_5;
    _294 = param_2;
    start_JAISound_(soundID, pos, audience_);
    _290 = 0;
    if (mStrategyMgr != NULL)
    {
        _2bc = mStrategyMgr->calc(soundID);
    }
    else
    {
        _2bc = NULL;
    }
}

bool JAIStream::prepare_prepareStream_()
{
    u32 aramSize;
    switch (_290)
    {
    case 0:
        JAIStreamAramMgr *streamAramMgr = mStreamMgr->getStreamAramMgr();
#line 100
        JUT_ASSERT(streamAramMgr);
        mAramAddr = streamAramMgr->newStreamAram(&aramSize);
        if (mAramAddr != NULL)
        {
            mInner.mAramStream.init(mAramAddr, aramSize, &JAIStream_JASAramStreamCallback_, this);
            _290 = 1;
            prepareCount_ = 0;
        }
        else
        {
            increasePrepareCount_JAISound_();
        }
        break;
    case 1:
        if (audible_ != NULL)
        {
            JASSoundParams *soundParams = audible_->getOuterParams(0);
            mInner.mAramStream.setPitch(soundParams->mPitch);
            mInner.mAramStream.setVolume(soundParams->mVolume);
            mInner.mAramStream.setPan(soundParams->mPan);
            mInner.mAramStream.setFxmix(soundParams->mFxMix);
            mInner.mAramStream.setDolby(soundParams->mDolby);
        }
        _2c5 = 0;
        if (mInner.mAramStream.prepare(_294, -1))
        {
            _290 = 2;
        }
        break;
    case 2:
        if (_2c5 != 0)
        {
            _2c5 = 0;
            _290 = 3;
        }
        else
        {
            increasePrepareCount_JAISound_();
        }
        break;
    case 3:
        return true;
    case 4:
#line 155
        JUT_WARNING_F2("%s", "PC must not pass here.");
        break;
    }

    return false;
}

void JAIStream::prepare_()
{
    if (_2c6 != 0)
    {
        return;
    }
    switch (status_.state.unk)
    {
    case 6:
        JUT_ASSERT(false)
        break;
    case 0:
        if (prepare_prepareStream_())
        {
            status_.state.unk = 5;
            prepare_startStream_();
        }
        break;
    case 1:
        if (prepare_prepareStream_())
        {
            status_.state.unk = 3;
        }
        break;
    case 4:
        status_.state.unk = 5;
        prepare_startStream_();
        break;
    case 5:
        break;
    }
}

void JAIStream::prepare_startStream_()
{
    if (mInner.mAramStream.start())
    {
        _2c6 = 0;
        _2c4 = 0;
        _290 = 4;
    }
}

void JAIStream::JAIStreamMgr_mixOut_(const JASSoundParams &param_1, JAISoundActivity param_2)
{
    JASSoundParams local_4c;
    params_.mixOutAll(param_1, &local_4c, (status_.isMute() || param_2._0.flags.flag1) ? 0.0f : fader_.getIntensity());
    if (_2bc != NULL)
    {
        _2bc->virtual4(this, local_4c);
    }
    JASSoundParams *mixParams = &local_4c;
    if (audible_ != NULL && audience_ != NULL)
    {
        for (int i = 0; i < audience_->getMaxChannels(); i++)
        {
            JASSoundParams *outerParams = audible_->getOuterParams(i);
            if (outerParams != NULL)
            {
                audience_->mixChannelOut(local_4c, audible_, i);
                mixParams = outerParams;
                break;
            }
        }
    }
    for (int i = 0; i < JASAramStream::CHANNEL_MAX; i++)
    {
        mInner.mAramStream.setPitch(mixParams->mPitch);
        if (mChilds[i] != NULL)
        {
            mInner.mAramStream.setChannelVolume(i, mChilds[i]->mMove.mParams.mVolume *
                                                          mixParams->mVolume);
            mInner.mAramStream.setChannelPan(
                i, (mChilds[i]->mMove.mParams.mPan + mixParams->mPan) - 0.5f);
            mInner.mAramStream.setChannelFxmix(i, mChilds[i]->mMove.mParams.mFxMix +
                                                         mixParams->mFxMix);
            mInner.mAramStream.setChannelDolby(i, mChilds[i]->mMove.mParams.mDolby +
                                                         mixParams->mDolby);
        }
        else
        {
            mInner.mAramStream.setChannelVolume(i, mixParams->mVolume);
            mInner.mAramStream.setChannelPan(i, mixParams->mPan);
            mInner.mAramStream.setChannelFxmix(i, mixParams->mFxMix);
            mInner.mAramStream.setChannelDolby(i, mixParams->mDolby);
        }
    }
    prepare_();
    if (_290 == 4)
    {
        bool notPlaying = status_.isPaused() || param_2._0.flags.flag2;
        if (notPlaying != _2c4)
        {
            mInner.mAramStream.pause(notPlaying);
            _2c4 = notPlaying;
        }
    }
}

void JAIStream::die_JAIStream_()
{
    die_JAISound_();
    for (int i = 0; i < CHANNEL_MAX; i++)
    {
        if (mChilds[i] != NULL)
        {
            delete mChilds[i];
            mChilds[i] = NULL;
        }
    }
    if (_2bc != NULL)
    {
        mStrategyMgr->virtual4(_2bc);
        _2bc = NULL;
    }
}

bool JAIStream::JAISound_tryDie_()
{
    if (_2c6)
    {
        die_JAIStream_();
        return true;
    }
    switch (_290)
    {
    case 0:
    case 1:
        die_JAIStream_();
        return true;
    case 2:
    case 3:
        _290 = 5;
        mInner.mAramStream.cancel();
        break;
    case 4:
        _290 = 6;
        mInner.mAramStream.stop(10);
        break;
    }

    return false;
}

void JAIStream::JAIStreamMgr_calc_()
{
    if (_2c6 != 0)
    {
        _290 = 0;
        stop_JAISound_();
    }
    if (calc_JAISound_())
    {
        for (int i = 0; i < CHANNEL_MAX; i++)
        {
            if (mChilds[i] != NULL)
            {
                mChilds[i]->calc();
            }
        }
        if (_2bc != NULL)
        {
            _2bc->calc(this);
        }
    }
}

s32 JAIStream::getNumChild() const
{
    return 6;
}

JAISoundChild *JAIStream::getChild(int i_idx)
{
    if (mChilds[i_idx] == NULL)
    {
        mChilds[i_idx] = new JAISoundChild();
        if (mChilds[i_idx] == NULL)
        {
#line 370
            JUT_WARNING_F2("%s", "JASPoolAllocObject::<JAISoundChild>::operator new failed .\n")
        }
    }
    return mChilds[i_idx];
}

void JAIStream::releaseChild(int i_idx)
{
    if (mChilds[i_idx] != NULL)
    {
        JAISoundChild *child = mChilds[i_idx];
        delete child;
        mChilds[i_idx] = NULL;
    }
}

JASTrack *JAIStream::getTrack()
{
    return NULL;
}

JASTrack *JAIStream::getChildTrack(int param_0)
{
    return NULL;
}

JAIStream *JAIStream::asStream()
{
    return this;
}

JAITempoMgr *JAIStream::getTempoMgr()
{
    return NULL;
}

#include "JSystem/JAudio/JASFakeMatch8.h"