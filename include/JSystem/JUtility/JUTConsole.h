#ifndef _JUTCONSOLE_H
#define _JUTCONSOLE_H

#include <stdarg.h>

#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JGadget/linklist.h"
#include "types.h"

inline s32 colorCheck(s32 diff, s32 t)
{
    s32 ret = diff - t;
    return ret + 1;
}

class JUTConsole : public JKRDisposer
{
public:
    enum EConsoleType
    {
        UNK_TYPE2 = 2,
    };

    enum OutputFlag
    {
        /* 0x0 */ OUTPUT_NONE,
        /* 0x1 */ OUTPUT_OSREPORT,
        /* 0x2 */ OUTPUT_CONSOLE,
        /* 0x3 */ OUTPUT_OSR_AND_CONSOLE,
    };

    virtual ~JUTConsole(); // _08

    // _00 VTBL

    static JUTConsole *create(uint, uint, JKRHeap *);
    static JUTConsole *create(uint, void *, u32);
    static void destroy(JUTConsole *); // UNUSED
    JUTConsole(uint, uint, bool);
    static size_t getObjectSizeFromBufferSize(uint, uint);
    static size_t getLineFromObjectSize(u32, uint);
    void clear();
    void doDraw(JUTConsole::EConsoleType) const;
    void print_f(char const *, ...);
    void print(char const *);
    void dumpToTerminal(uint);
    void scroll(int);
    int getUsedLine() const;
    int getLineOffset() const;

    void setOutput(uint output) { mOutput = output; }
    void setPosition(int x, int y)
    {
        mPositionX = x;
        mPositionY = y;
    }
    void setFontSize(f32 x, f32 y)
    {
        mFontSizeX = x;
        mFontSizeY = y;
    }
    void setHeight(u32 height)
    {
        mHeight = height;
        if (mHeight > mMaxLines)
        {
            mHeight = mMaxLines;
        }
    }

    void setFont(JUTFont *p_font)
    {
        mFont = p_font;
        setFontSize(p_font->getWidth(), p_font->getHeight());
    }

    u32 getOutput() const { return mOutput; }
    int getPositionY() const { return mPositionY; }
    int getPositionX() const { return mPositionX; }
    u32 getHeight() const { return mHeight; }

    bool isVisible() const { return mIsVisible; }
    void setVisible(bool visible) { mIsVisible = visible; }

    void setLineAttr(int param_0, u8 param_1) { mBuf[(field_0x20 + 2) * param_0] = param_1; }
    u8 *getLinePtr(int param_0) const { return &mBuf[(field_0x20 + 2) * param_0] + 1; }
    int diffIndex(int param_0, int param_1) const
    {
        int diff = param_1 - param_0;
        if (diff >= 0)
        {
            return diff;
        }
        return diff += mMaxLines;
    }

    void scrollToLastLine() { scroll(mMaxLines); }
    void scrollToFirstLine() { scroll(-mMaxLines); }

private:
    JGadget::TLinkListNode mListNode; // _18

private:
    /* 0x20 */ u32 field_0x20;
    /* 0x24 */ u32 mMaxLines;
    /* 0x28 */ u8 *mBuf;
    /* 0x2C */ bool field_0x2c;
    /* 0x30 */ int field_0x30;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ int mPositionX;
    /* 0x44 */ int mPositionY;
    /* 0x48 */ u32 mHeight;
    /* 0x4C */ JUTFont *mFont;
    /* 0x50 */ f32 mFontSizeX;
    /* 0x54 */ f32 mFontSizeY;
    /* 0x58 */ uint mOutput;
    /* 0x5C */ JUtility::TColor field_0x5c;
    /* 0x60 */ JUtility::TColor field_0x60;
    /* 0x64 */ int field_0x64;
    /* 0x68 */ bool mIsVisible;
    /* 0x69 */ bool field_0x69;
    /* 0x6A */ bool field_0x6a;
    /* 0x6B */ bool field_0x6b;
}; // Size: 0x6C

class JUTConsoleManager
{
public:
    JUTConsoleManager();
    static JUTConsoleManager *createManager(JKRHeap *);
    void appendConsole(JUTConsole *console);
    void removeConsole(JUTConsole *console);
    void draw() const;
    void drawDirect(bool) const;
    void setDirectConsole(JUTConsole *);

    static JUTConsoleManager *getManager() { return sManager; }

    static JUTConsoleManager *sManager;

private:
    JGadget::TLinkList<JUTConsole, 4> soLink_;   // _00
    JUTConsole *mActiveConsole;                  // _0C
    JUTConsole *mDirectConsole;                  // _10
};                                               // Size: 0x14

#ifdef __cplusplus // not sure if this is needed, if it is, maybe recast JUTConsole to void * or forward declaration
extern "C" {
#endif
void JUTConsole_print_f_va_(JUTConsole *, const char *, va_list);

JUTConsole *JUTGetReportConsole();
void JUTSetReportConsole(JUTConsole *);
JUTConsole *JUTGetWarningConsole();
void JUTSetWarningConsole(JUTConsole *);
void JUTReportConsole(const char *);
void JUTReportConsole_f(const char *, ...);
void JUTReportConsole_f_va(const char *, va_list);
void JUTWarningConsole(const char*);
void JUTWarningConsole_f(const char *, ...);
#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif