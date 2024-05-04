#ifndef KARTANIME_H
#define KARTANIME_H

#include "types.h"

class KartAnime
{ // Autogenerated
public:
    KartAnime() {}

public:
    bool IsAppeal(int);                 // 0x802f9a5c
    bool IsThrow(int);                  // 0x802f9aa4
    bool IsMove(int);                   // 0x802f9aec
    bool IsSuspend(int);                // 0x802f9b34
    bool IsDamage(int);                 // 0x802f9bf8
    bool IsDamageL(int);                // 0x802f9c40
    bool IsDamageS(int);                // 0x802f9c88
    bool IsRide(int);                   // 0x802f9cd0
    bool IsNormalStart(int);            // 0x802f9d18
    bool IsBackStart(int);              // 0x802f9d60
    bool IsRun(int);                    // 0x802f9da8
    bool IsDrift(int);                  // 0x802f9df0
    bool IsDriftStart(int);             // 0x802f9e38
    bool IsDriftLeft(int);              // 0x802f9e80
    bool IsDriftRight(int);             // 0x802f9ec8
    bool IsChange(int);                 // 0x802f9f10
    bool IsRocket(int);                 // 0x802f9f58
    bool IsJump(int);                   // 0x802f9fa0
    bool IsSit(int);                    // 0x802f9fe8
    bool IsBackAnime(int);              // 0x802fa030
    bool IsFloatAnime(int);             // 0x802fa078
    bool IsDangerAnime(int);            // 0x802fa0c0
    bool IsDangerLoopAnime(int);        // 0x802fa108
    bool IsDangerPlusAnime(int);        // 0x802fa17c
    bool IsGetItemAnime(int);           // 0x802fa1c4
    bool IsBurnAnime(int);              // 0x802fa208
    bool IsDrive(int);                  // 0x802fa250
    bool IsBack(int);                   // 0x802fa298
    bool IsGaol(int);                   // 0x802fa2fc
    bool IsAttack(int);                 // 0x802fa344
    void IsProhibition(int);            // 0x802fa38c
    void MakeThrowAnime(int, int, int); // 0x802fa408
    void MakeBackAnime(int);            // 0x802fa424
    void MakeFrontAnime(int);           // 0x802fa4b0
    void Init();                        // 0x802fa53c
    void DoGetAnime(int);               // 0x802fa598
    void DoBackAnime(int);              // 0x802fa7c4
    void DoFrontAnime(int);             // 0x802fa84c
    void DoChangeAnime(int);            // 0x802fa8b0
    void DoDriveAnime(int);             // 0x802fa98c
    void DoStartRunStartAnime(int);     // 0x802faa1c
    void DoStartRunEndAnime(int);       // 0x802faa58
    void DoDriverThrowAnime(int);       // 0x802faab8
    void DoDriverDamageAnime(int);      // 0x802fab20
    void DoDriverDriveAnime(int);       // 0x802fab84
    void DoThrowAnime(int);             // 0x802fabe8
    void DoDriftAnime(int);             // 0x802fac54
    void DoDriftEndAnime(int);          // 0x802fad78
    void DoSlideAnime(int);             // 0x802fae68
    void DoJumpAnime(int);              // 0x802faf60
    void DoCrouchAnime(int);            // 0x802fb014
    void DoStandAnime(int);             // 0x802fb09c
    void DoPushStartAnime(int);         // 0x802fb134
    void DoNormalStartAnime(int);       // 0x802fb194
    void DoRocketStartAnime(int);       // 0x802fb218
    void DoFalseStartAnime(int);        // 0x802fb2a0
    void DoDamageStartAnime(int);       // 0x802fb328
    void DoDamageEndAnime(int);         // 0x802fb424
    void DoBigDamageStartAnime(int);    // 0x802fb520
    void DoBigDamageEndAnime(int);      // 0x802fb61c
    void DoBurnStartAnime(int);         // 0x802fb718
    void DoBurnEndAnime(int);           // 0x802fb77c
    void DoFloatStartAnime(int);        // 0x802fb7e0
    void DoHangStartAnime(int);         // 0x802fb844
    void DoGoalStartAnime(int);         // 0x802fb8a4
    void DoStaffAnime(int);             // 0x802fb930
    void DoHappyAnime(int);             // 0x802fb9bc
    void DoWinAnime(int);               // 0x802fba28
    void DoDefeatAnime(int);            // 0x802fbaa0
    void DoFloatEndAnime(int);          // 0x802fbb00
    void DoSurpriseAnime(int);          // 0x802fbb64
    void DoSurpriseEndAnime(int);       // 0x802fbc34
    void DoHangJumpStartAnime(int);     // 0x802fbcc0
    void DoHangJumpEndAnime(int);       // 0x802fbd34
    void DoAppealAnime(int);            // 0x802fbdb0
    void DoStopAnime(int);              // 0x802fbe10
    void DoReStopAnime(int);            // 0x802fbe64
    void DoCheck(int);                  // 0x802fbeb8
    void DoAnime(int);                  // 0x802fc4cc
    // Inline/Unused
    // void IsDriverThrow(int);
    // void IsDamageS2(int);
    // void IsDriftEnd(int);
    // void IsTandemStartOK(int);
    // void IsTurn(int);
    // void IsDriftLimAnime(int);
    // void IsDangerEndAnime(int);
    // void MakeDriverThrowAnime(int, int, int);
    // void MakeGetAnime(ItemObj *, int);
    // Inline
    void IsChangeStart(); // 0x802f9bc4

    u8 _0[0x10];         //
    u64 mFlags;          // 0x10, 0x14
    u8 mType;            // 0x18
    u8 _19[0x30 - 0x19]; //
    u64 mDamageFlags;             // 30, 34
    u8 _38[0x48 - 0x38]; //

}; // Size: 0x48

// Outside class Inlines
// void DriverModel::TurnBack();
// void ItemObj::clrTransferPartner() // ItemObj.h; // 0x802fa7a8
// void ItemObj::tstTransferPartner() const // ItemObj.h; // 0x802fa7b8
// void DriverModel::BacktoDWait() // DriverModel.h; // 0x802faa94
// void DriverModel::StartNormalStart() // DriverModel.h; // 0x802fb1f4
// void DriverModel::StartRocketStart() // DriverModel.h; // 0x802fb27c
// void DriverModel::StartRocketStartFailure() // DriverModel.h; // 0x802fb304
// void DriverModel::SetFreeze() // DriverModel.h; // 0x802fbe58
// void DriverModel::ResetFreeze() // DriverModel.h; // 0x802fbeac

#endif // KARTANIME_H
