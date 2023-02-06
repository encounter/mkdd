#ifndef ERRORVIEWAPP_H
#define ERRORVIEWAPP_H

#include "Osako/GameApp.h"

class ErrorViewApp : public GameApp
{ // Autogenerated
    // Global
public:
    enum ErrorId
    {
        ERROR1,
        ERROR2,
        ERROR3,
        ERROR4,
        ERROR5
    };

    static ErrorViewApp *create(); // 0x802011cc
    static void call(ErrorId);            // 0x8020121c
    ErrorViewApp();                // 0x80201310
    virtual ~ErrorViewApp();       // 0x80201384
    virtual void draw();           // 0x802013e4
    virtual void calc();           // 0x80201408
    virtual void reset();          // 0x802015a8

    static ErrorViewApp *mspErrorViewApp; // 0x804169c0
    static ErrorId msErrorId;             // 0x804169c4
}; // class ErrorViewApp
#endif                  // ERRORVIEWAPP_H