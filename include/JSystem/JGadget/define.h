#ifndef DEFINE_H
#define DEFINE_H

#include "JSystem/JUtility/JUTAssert.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    class JGadget_outMessage
    {
    public:
        typedef void (*MessageFunc)(const char *, int, const char *);

        static void warning(const char *, int, const char *);

        JGadget_outMessage(MessageFunc fn, const char *file, int line);
        ~JGadget_outMessage();

        JGadget_outMessage &operator<<(const char *str);

    private:
        MessageFunc mMsgFunc;
        char mBuffer[256];
        char *mWrite_p;
        char *mFile;
        int mLine;
    };

#ifdef JGADGET_DEBUG

#define JGADGET_ASSERTWARN(cond) \
    ((cond) || ((JGadget_outMessage(JGadget_outMessage::warning, __FILE__, __LINE__) << (#cond)), false))

#define JGADGET_EXITWARN(cond)                                                                 \
    if (!(cond))                                                                               \
    {                                                                                          \
        JGadget_outMessage(JGadget_outMessage::warning, __FILE__, __LINE__) << (#cond), false; \
        return false;                                                                          \
    }

#define JGADGET_ASSERT(cond) \
    JUT_ASSERT(cond);

#else

#define JGADGET_ASSERTWARN(cond) \
    ((cond) || (false))

#define JGADGET_EXITWARN(cond) \
    if (!(cond))               \
    {                          \
        false;                 \
        return false;          \
    }

#define JGADGET_ASSERT(...)

#endif

#ifdef __cplusplus
}
#endif

#endif