#ifndef JUGEMRODSIGNAL_H
#define JUGEMRODSIGNAL_H

#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JGeometry.h"

// probably inherited from TJugemMain

class TJugemRodSignal
{ // Autogenerated
public:
    // Global
    TJugemRodSignal();                     // 0x80293558
    ~TJugemRodSignal();                    // 0x80293630
    void reset();                          // 0x80293710
    void loadAnimation();                  // 0x802937e4
    void getShadowBmdFileName();           // 0x80293864
    void getBmdFileName();                 // 0x8029386c
    void createModel(JKRSolidHeap *, u32); // 0x80293894
    // void createColModel(J3DModelData *);                       // 0x802939ec
    void calc(); // 0x802939f0
    // void createEmitter(JPABaseEmitter **, long, const char *); // 0x80293bbc
    void startCountDown(); // 0x80293c60
    void show(u8);         // 0x80293c74
    void update();         // 0x80293cac
    void isAcceptEffect(); // 0x80293e74
    // void scRedParticleName;                                    // 0x80415160
    // void scGreenParticleName;                                  // 0x80415164
    static void *sJugemRodSignalBrkAnm; // 0x80416da8
    // void sRandomWait;                                          // 0x80416dac
    // void sLeftJointNo;                                         // 0x80416db0
    // void sMiddleJointNo;                                       // 0x80416db4
    // void sRightJointNo;                                        // 0x80416db8
    // void scSignalInterval;                                     // 0x8041c7d8
    //  Inline
    bool isCallThree();

    // Inline/Unused
    // void getJointPos(JGeometry::TVec3<float> *, long);
    // void updatePosition(JPABaseEmitter **, long);

    // void scRandomLength;

}; // class JugemRodSignal

class TJugemRodPukuPuku
{
public:
    TJugemRodPukuPuku();
    ~TJugemRodPukuPuku();
    void reset();
    void loadAnimation();
    void createModel(JKRSolidHeap *, u32);
    void show(u8);
    void update();
    void calc();
    void setPosition(const JGeometry::TVec3<float> &);
    // void setRMtx(const JGeometry::TPosition3<JGeometry::TMatrix34<JGeometry::SMatrix34C<float>>> &);
    void setCurrentViewNo(u32);
    // void nodeCallBack(J3DJoint *, int);
    // void sAnmInfos_Puku_Demo2;
    // void sAnmInfos_Puku_Demo3;
    // void sDemoAnmStateTable;

    // Inline/Unused
    // void JugemRodPukuPuku::getCurMatrix(Mtx *);
    // void JugemRodPukuPuku::scCutFrame;
};
#endif