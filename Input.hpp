#ifndef __INPUT_H_INCLUDED__
#define __INPUT_H_INCLUDED__

#define DIRECTINPUT_VERSION 0x0800

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
#include <dinput.h>
#include <iostream>

namespace si
{




#define PI 3.14159265358979323846

class Input
{
public:
    byte* Keys;     // array holding status of each keyboard key
    float* axs;      // aray to hold values of each mouse axis
    Input(HWND hWnd);
    ~Input();
    HRESULT prectiStavVstupu();
    void reset();
private:
    HWND hWnd;
    bool Buttons[8];
    LPDIRECTINPUT8 diiDI;            // DirectInput interface
    LPDIRECTINPUTDEVICE8 diMouse;    // mouse device interface
    LPDIRECTINPUTDEVICE8 diKeybrd;   // keyboard device interface
    float axX, axY, axZ, nmX, nmY;
    void prepareInputDevices();
};


}


#endif // __INPUT_H_INCLUDED__
