#ifndef LIGHTMGR_H
#define LIGHTMGR_H

#include "JSystem/JGeometry.h"
#include "JSystem/JUtility/TColor.h"
#include "types.h"

// TODO: everything
class LightObj {
public:
    LightObj(const char *); // auto inlined it seems
    LightObj(const char *, u32);

    void init(const char *, u32);
    void setTagName(u32 tagName) { mTagName = tagName; };

    // 00 Vtable
    virtual ~LightObj();
    virtual Mtx *getEffectMtx();
    virtual void draw();
    virtual void getColor(JUtility::TColor *) const;
    virtual void calc();
    virtual void setGXObj();

private:
    u8 _04[0x20 - 0x4];
    u32 mTagName;            // 0x20
    JSULink<LightObj> mLink; // 0x24
    u32 _34; 
}; // Size 0x38

class LtObjAmbient : public LightObj {
public:
    LtObjAmbient(JUtility::TColor color) : LightObj("アンビエント", 0xffffffff)
    {
        GXColor gxColor = color;
        mColor.set(gxColor);
    }

    LtObjAmbient(const char * name, JUtility::TColor color) : LightObj(name, 0xffffffff)
    {
        GXColor gxColor = color;
        mColor.set(gxColor);
    }
    virtual ~LtObjAmbient();                         // overide
    virtual void getColor(JUtility::TColor *) const; // overide
    virtual void draw();                             // overide

private:
    JUtility::TColor mColor;
}; // Size: 0x3c

class LtObjDiffuse : public LightObj {
public:
    virtual ~LtObjDiffuse(); // overide
    virtual void setGXObj(); // overide
    virtual void draw();     // overide
    void load(GXLightID id);

private:
    JGeometry::TVec3f mPos;  // 0x38
    JUtility::TColor mColor; // 0x44
    Mtx *mViewMtx;           // 0x48
    u16 mLoadNo;             // 0x4c
    GXLightObj mLightObj;    // 0x50
};

class LightMgr
{ // Autogenerated
public:
    // Global
    LightMgr();                      // 0x801b3ec0
    void createCharColor();          // 0x801b3fb8
    static int createManager();      // 0x801b3fbc
    void appendLight(LightObj *);    // 0x801b400c
    void removeLight(LightObj *);    // 0x801b4054
    void draw();                     // 0x801b409c
    void calc();                     // 0x801b4278
    void searchLight(unsigned long); // 0x801b431c
    ~LightMgr();                     // 0x801b446c

    static LightMgr *getManager() {return sLightManager; };

private:
    static LightMgr * sLightManager;          // 0x804163b8
    // Inline/Unused
    // void reset();
    // void searchRaceSceneLight(unsigned long);
    // void searchRaceKartLight(unsigned long, int);
}; // class LightMgr

#endif