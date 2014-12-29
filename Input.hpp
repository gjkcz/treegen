#ifndef __INPUT_H_INCLUDED__
#define __INPUT_H_INCLUDED__


#include <windows.h>
#include <dinput.h>
#include "guicon.h"
namespace si
{


#define PI 3.14159265358979323846

class Input
{
public:
    byte* Keys;     // array holding status of each keyboard key
    long* axs;      // aray to hold values of each mouse axis
    Input();
    Input(HWND hWnd);
    ~Input();
    HRESULT prectiStavVstupu();
private:
    HWND hWnd;
    bool Buttons[8];
    LPDIRECTINPUT8 diiDI;            // DirectInput interface
    LPDIRECTINPUTDEVICE8 diMouse;    // mouse device interface
    LPDIRECTINPUTDEVICE8 diKeybrd;   // keyboard device interface
    long axX, axY, axZ, nmX, nmY;
    void prepareInputDevices();
};


}


#endif // __INPUT_H_INCLUDED__
