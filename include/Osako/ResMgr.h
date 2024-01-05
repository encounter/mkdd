#ifndef RESMGR_H
#define RESMGR_H

#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "Kaneshige/RaceInfo.h"
#include "kartEnums.h"
#include "types.h"

namespace ResMgr
{ // Autogenerated
    // Global
    struct AramAsyncState
    {
        void *_0;
        u32 _4;
        char *folder;
        char *fileName; // 0xc
        int _10;
        AramAsyncState *parent; // 0x14

        // fabricated
        void setAll(void *p1, u32 p2, char *folder_, char *fileName_, int p5, AramAsyncState *p6)
        {
            _0 = p1;
            _4 = p2;
            folder = folder_;
            fileName = fileName_;
            _10 = p5;
            parent = p6;
        }
    }; // Size: 0x18

    enum ArchiveId
    {
        mcArcMRAM,
        mcArcMRAMLoc,
        mcArcARAM,
        mcArcCourse,
        mcArcSystem, // the Arc file hidden in the dol
        mcArcRace2D,
        mcArcAward,
        mcArcAward2D,
        mcArcOpening,
        mcArcMax
    };

    enum CourseDataId
    {
        mcCourseBmd,
        mcCourseBco,
        mcCourseBol,
        mcCourseBtk1,
        mcCourseBtk2,
        mcCourseBtk3,
        mcCourseBtp,
        mcCourseBrk,
        mcCourseSkyBmd,
        mcCourseSkyBtk,
        mcCourseSkyBrk,
        mcCourseMapBti,
        mcCourseNameBti,
        mcCourseDataGhost,
        mcCourseMax
    };

    enum CourseOrder
    {
        mcOrderMin,
        mcOrder_1,
        mcOrder_2,
        mcOrderMax
    };

    enum DriverDataId
    {
        mcDriverDataBmd,
        mcDriverData200Bmd,
        mcDriverDataBrk
    };

    enum DriverId
    {
        mcDriverBabyMario,
        mcDriverBabyLuigi,
        mcDriverParaTroopa,
        mcDriverKoopaTroopa,
        mcDriverPeach,
        mcDriverDaisy,
        mcDriverMario,
        mcDriverLuigi,
        mcDriverWario,
        mcDriverWaluigi,
        mcDriverYoshi,
        mcDriverBirdo,
        mcDriverDonkeyKong,
        mcDriverDiddyKong,
        mcDriverBowser,
        mcDriverBowserJr,
        mcDriverToad,
        mcDriverToadette,
        mcDriverKingBoo,
        mcDriverPetey
    };

    enum KartDataId
    {
        mcKartDataBody,
        mcKartDataArm,
        mcKartDataShock,
        mcKartTire,
        mcKartTireLeft,
        mcKartTireRight
    };

    enum MessageDataId
    {
        mcColor,
        mcProgressiveScan,
        mcDvd,
        mcCard,
        mcBattle,
        mcEuro60,
        mcLan,
        mcIpl,
        mcSecret,
        mcRace,
        mcYesNo,
        mcStaffRoll
    };

    enum ShadowDataId
    {
        mcShadowDataBmd,
        mcShadowDataBls,
        mcShadowDataBlk
    };

    // Inline/Unused
    char *getAwardArcName(ERaceGpCup);
    char *getCrsDataName(CourseDataId);
    char *getKartName(EKartID);
    char *getKartDataName(KartDataId);
    char *getDriverName(DriverId);
    char *getDriverDataName(DriverDataId);
    char *getShadowDataName(ShadowDataId);
    char *getMsgDataName(MessageDataId);

    char *getCrsArcName(ECourseID);                                        // 0x801fc5dc
    void create(JKRHeap *);                                                // 0x801fc860
    void loadKeepTask(void *);                                             // 0x801fc940
    void loadCourseTask(void *);                                           // 0x801fcbe8
    void loadAwardTask(void *);                                            // 0x801fcda4
    void loadOpeningTask(void *);                                          // 0x801fcf20
    void loadKeepData();                                                   // 0x801fcf84
    void loadCourseData(ECourseID, CourseOrder);                           // 0x801fcff4
    void loadAwardData(ERaceGpCup, JKRHeap *);                             // 0x801fd098
    void loadOpeningData(JKRHeap *);                                       // 0x801fd128
    bool isFinishLoadingArc(ArchiveId);                                    // 0x801fd1a4
    bool isLoadingArc(ArchiveId);                                          // 0x801fd1c0
    void *getPtr(KartDataId, EKartID);                                     // 0x801fd1dc
    void *getPtr(DriverDataId, DriverId);                                  // 0x801fd4dc
    void *getPtr(ShadowDataId, EKartID);                                   // 0x801fd6ac
    void *getPtr(CourseDataId);                                            // 0x801fd8e8
    void *getPtr(MessageDataId);                                           // 0x801fda40
    void *getPtr(ArchiveId, const char *);                                 // 0x801fdb70
    long getResSize(ArchiveId, const void *);                              // 0x801fdc20
    bool readResourceAsync(void *, u32, char *, char *, AramAsyncState *); // 0x801fdcd0
    void readAnmResTask(void *);                                           // 0x801fddb4
    bool findResource(ArchiveId, char *);                                  // 0x801fde70
    bool isFinishLoadingAram();                                            // 0x801fdf2c

    extern JKRArchive *mspaLoader[mcArcMax];   // 0x803fe2f8
    extern AramAsyncState msaAramResArg[0x40]; // 0x803fe95c, might be a different data type?
    extern ERaceGpCup msCupID;                 // 0x80414858
    extern u8 msUsedArgArray;                  // 0x8041485c
    extern u32 msLoadFlag;                     // 0x80416930
    extern u32 msLoadingFlag;                  // 0x80416934
    extern bool msRequestLoadingKeepData;      // 0x80416938
    extern ECourseID msCourseID;               // 0x8041693c
    extern CourseOrder msCourseOrder;          // 0x80416940
    extern ECourseID msMountCourseID;          // 0x80416944
    extern CourseOrder msMountCourseOrder;     // 0x80416948
    extern void *mspCourseName;                // 0x8041694c
    extern void *mspStaffGhost;                // 0x80416950
    extern u8 msFreeArgArray;                  // 0x80416954
    extern int msAramTaskNum;                  // 0x80416958

    extern const u32 mscKeepHeapSize;
    extern const u32 mscCourceHeapSize;

    inline void *getArchive(ArchiveId id) { return mspaLoader[(int)id]; };
    inline ECourseID getCourseID() { return msCourseID; }

}; // namespace ResMgr

extern u8 _pSystemArc[];

#endif // RESMGR_H
