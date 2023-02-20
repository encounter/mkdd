#ifndef RACEBGMPLAYER_H
#define RACEBGMPLAYER_H

#include "types.h"

class RaceBGMPlayer
{ // Autogenerated
    // Global
    public:
    RaceBGMPlayer();               // 0x801c6da0
    void reset();                  // 0x801c6dd0
    int getCrsDemoBGMLabel();      // 0x801c6e64
    int getRaceStartBGMLabel();    // 0x801c6eac
    void calc();                   // 0x801c6f84
    int getGoalBGMLabel();         // 0x801c72e0
    static short sCrsBGMDelayTime; // 0x804146f0
    // Inline/Unused
    // void stop();
    // Inline
    void stopCrsDemo();         // 0x801c6e54
    bool isMiniGameEnd() const; // 0x801c7288
    bool isLastTime() const;    // 0x801c7294
    bool isExecPrepare() const; // 0x801c72a0
    bool isPlay() const;        // 0x801c72ac
    void execPrepare();         // 0x801c72b8
    bool isPrepare() const;     // 0x801c72c8
    bool isCrsDemoEnd() const;  // 0x801c72d4

    void setLowestKartNo(int kartNo) { mLowestKartNo = kartNo; };
    void setGoalKartNo(int kartNo) { mGoalKartNo = kartNo; };
    void setFinalLapKartNo(int kartNo) { mFinalLapKartNo = kartNo; };

private:
    u8 _0[0x8];
    s16 mFinalLapKartNo;
    s16 mGoalKartNo;
    s16 mLowestKartNo;
};                              // class RaceBGMPlayer
// void RaceMgr::isRaceModeVs() const // RaceMgr.h; // 0x801c6f2c
// void RaceMgr::isRaceModeTA() const // RaceMgr.h; // 0x801c6f58
#endif // RACEBGMPLAYER_H