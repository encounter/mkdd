#ifndef STMATH_H
#define STMATH_H

#include <types.h>

#include <JSystem/JMath/JMath.h>
#include <JSystem/JGeometry.h>

class stRandom : JMath::TRandom_fast_ {
public:
    static void createAllRandom();
    u32 getRandomMax(u32 max);
    f32 getArbitUnitVec(JGeometry::TVec3<f32>&, f32, f32);
    f32 getArbitUnitVecSimple(JGeometry::TVec3<f32>&, f32);
    f32 getArbitUnitVecXZ(JGeometry::TVec3<f32>&, f32);

    inline void setPermission(bool perm) {
        permission = perm;
    }

    static stRandom* sRndMgr[6];

private:
    /* ==== NOT MATCHING ==== */
    static stRandom* sMgr;
    stRandom() {
        permission = true;
        sMgr = this;
    }
    /* ===================== */
    u16 _0x4; // sin
    u16 _0x6; // cos
    f32 _0x8; // angle?
    u8 _0xC[4]; // unknown
    u32 randomSeed;
    bool permission;
    // padding bytes
};


stRandom * stGetRnd(u32 idx);
void stSetRndPermission(u32 idx, bool perm)

#endif // !STMATH_H
