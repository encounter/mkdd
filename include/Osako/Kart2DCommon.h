#ifndef KART2DCOMMON_H
#define KART2DCOMMON_H

#include <JSystem/J2D/J2DPane.h>
#include <JSystem/JKernel/JKRHeap.h>

class Kart2DCommon
{ // Autogenerated
public:
    void changeNumberTexture(int num, J2DPicture **paPicture, u8 places, bool, bool); // 0x8020edd0
    ResTIMG *getAsciiTexture(char);                                                   // 0x8020ef24
    void changeStringTexture(const char *aString, J2DPicture **paPicture, u8 places); // 0x8020effc
    Kart2DCommon();                                                                   // 0x8020f158
    virtual ~Kart2DCommon() { mspKart2DCommon = nullptr; }                            // 0x8020f48c

    static void create(JKRHeap *heap)
    {
        if (mspKart2DCommon == nullptr)
            mspKart2DCommon = new (heap, 0) Kart2DCommon();
    }

private:
    static Kart2DCommon *mspKart2DCommon; // 0x80416a70
    ResTIMG *mNumberFont[11];             // 0 to 9
    ResTIMG *mFontData[26];               // chars A to Z
    ResTIMG *mIndexCharImg[20];
    ResTIMG *mIndexKartImg[21];
    ResTIMG *mPartName[4];
    ResTIMG *mPartsLocName[1];
    ResTIMG *mPosImg[8];
    ResTIMG *mResCupImg[5];
    ResTIMG *mCupImg[5];
    ResTIMG *mBattleIconImg[3];
    ResTIMG *mMark[5];
    ResTIMG *mAlphaTex;
}; // Size:0x1bc

extern const char *cpaCharName[20];
extern const char *cpaKartName[21];
extern const char *cpaPartsName[4];
extern const char *cpaCupName[5];
extern const char *cpaCupIcon[5];
extern const char *cpaBattleIcon[3];
extern const char *cpaMarkName[5];
extern const char *cpaPartsLocName[1];

#endif // KART2DCOMMON_H