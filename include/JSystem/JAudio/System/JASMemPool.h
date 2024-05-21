#ifndef JAUDIO_JASMEMPOOL_H
#define JAUDIO_JASMEMPOOL_H


#include <dolphin/os.h>

#include "JSystem/JUtility/JUTAssert.h"

#include "JSystem/JAudio/System/JASHeap.h"

#include "types.h"

struct JASGenericMemPool
{
    JASGenericMemPool();
    ~JASGenericMemPool();
    void newMemPool(u32 n, int count);
    void free(void *p, u32 n);
    void *alloc(u32 n);

    void *mRunner;
    int mFreeMemCount;
    int mTotalMemCount;
    u32 _c;
};

template <typename T>
struct JASMemPool : public JASGenericMemPool
{
    JASMemPool<T>() : JASGenericMemPool() {}
    ~JASMemPool<T>() {}

    typedef JASMemPool<T> JASMemPoolT;

    void newMemPool(int count) {
        JASThreadingModel::SingleThreaded<JASMemPoolT>::Lock(*this);
        JASGenericMemPool::newMemPool(sizeof(T), count);
    }

    void free(void *p, u32 n) {
#line 187
        JUT_ASSERT(n == sizeof(T));
        JASThreadingModel::SingleThreaded<JASMemPoolT>::Lock(*this);
        JASGenericMemPool::free(p, n);
    }

    T *alloc(u32 n)
    {
        JUT_ASSERT(n == sizeof(T));
        JASThreadingModel::SingleThreaded<JASMemPoolT>::Lock(*this);
        return (T*)JASGenericMemPool::alloc(n); // evil cast fixes stuff
    }
};

template <u32 ChunkSize, typename T>
class JASMemChunkPool
{
    struct MemoryChunk
    {
        MemoryChunk(MemoryChunk *nextChunk)
        {
            mNextChunk = nextChunk;
            mUsedSize = 0;
            mChunks = 0;
        }

        bool checkArea(void *ptr)
        {
            return (u8 *)this + 0xc <= (u8 *)ptr && (u8 *)ptr < (u8 *)this + (ChunkSize + 0xc);
        }

        MemoryChunk *getNextChunk()
        {
            return mNextChunk;
        }

        void *alloc(u32 size)
        {
            u8 *rv = mBuffer + mUsedSize;
            mUsedSize += size;
            mChunks++;
            return rv;
        }

        void free()
        {
            mChunks--;
        }

        bool isEmpty()
        {
            return mChunks == 0;
        }

        void setNextChunk(MemoryChunk *chunk)
        {
            mNextChunk = chunk;
        }

        u32 getFreeSize()
        {
            return ChunkSize - mUsedSize;
        }

        void revive()
        {
            mUsedSize = 0;
        }

        MemoryChunk *mNextChunk; // 00
        u32 mUsedSize;           // 04
        u32 mChunks;             // 08
        u8 mBuffer[ChunkSize];   // 0c
    };

public:
    bool createNewChunk()
    {
        bool uVar2;
        if (_18 != NULL && _18->isEmpty())
        {
            _18->revive();
            uVar2 = 1;
        }
        else
        {
            MemoryChunk *pMVar4 = _18;
            _18 = new (JASKernel::getSystemHeap(), 0) MemoryChunk(pMVar4);
            if (_18 != NULL)
            {
                uVar2 = 1;
            }
            else
            {
                _18 = new (JKRHeap::getSystemHeap(), 0) MemoryChunk(pMVar4);
                if (_18 != NULL)
                {
                    uVar2 = 1;
                }
                else
                {
                    _18 = pMVar4;
                    uVar2 = 0;
                }
            }
        }
        return uVar2;
    }

    void *alloc(u32 size)
    {
        T::Lock lock(&mMutex);
        if (_18->getFreeSize() < size)
        {
            if (ChunkSize < size)
            {
                return NULL;
            }
            if (createNewChunk() == 0)
            {
                return NULL;
            }
        }
        return _18->alloc(size);
    }

    void free(void *ptr)
    {
        T::Lock lock(&((JASMemChunkPool<ChunkSize, T> *)ptr)->mMutex);
        MemoryChunk *chunk = ((JASMemChunkPool<ChunkSize, T> *)ptr)->_18;
        MemoryChunk *prevChunk = NULL;
        while (chunk != NULL)
        {
            if (chunk->checkArea(this))
            {
                chunk->free();
                if (chunk != ((JASMemChunkPool<ChunkSize, T> *)ptr)->_18 && chunk->isEmpty())
                {
                    MemoryChunk *nextChunk = chunk->getNextChunk();
                    delete chunk;
                    prevChunk->setNextChunk(nextChunk);
                }
                return;
            }
            prevChunk = chunk;
            chunk = chunk->getNextChunk();
        }
    }

    OSMutex mMutex;   // 00
    MemoryChunk *_18; //
};

template <typename T>
struct JASPoolAllocObject
{
    static void newMemPool(int count) 
    {
        memPool_.newMemPool(count);
    }

    static void operator delete(void *mem, u32 n)
    {
        memPool_.free(mem, n);
    }

    static void *operator new(u32 n) {
        return memPool_.alloc(n);
    }

    static JASMemPool<T> memPool_;
};

template <typename T>
struct JASMemPool_MultiThreaded : public JASGenericMemPool
{
    typedef JASMemPool_MultiThreaded<T> JASMemPool_MultiThreadedT;

    void newMemPool(int count)
    {
        JASThreadingModel::InterruptsDisable<JASMemPool_MultiThreadedT>::Lock lock(*this);
        JASGenericMemPool::newMemPool(sizeof(T), count);
    }

    void *alloc(u32 n)
    {
        JASThreadingModel::InterruptsDisable<JASMemPool_MultiThreadedT>::Lock lock(*this);
        return JASGenericMemPool::alloc(n);
    }

    JASMemPool_MultiThreaded<T>() : JASGenericMemPool() { }
    ~JASMemPool_MultiThreaded<T>() {}
};


template <typename T>
struct JASPoolAllocObject_MultiThreaded
{
    static void newMemPool(int count)
    {
        memPool_.newMemPool(count);
    }

    static void *operator new(u32 n)
    {
        return memPool_.alloc(n);
    }
    static void operator delete(void *mem, u32 n)
    {
        BOOL inter = OSDisableInterrupts();
        memPool_.free(mem, n);
        OSRestoreInterrupts(inter);
    }
    static JASMemPool_MultiThreaded<T> memPool_;
};

#endif