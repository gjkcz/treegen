#include "controler.h"
bool Buttons[8];
LPDIRECTINPUT8          diiDI = NULL; // DirectInput interface
LPDIRECTINPUTDEVICE8    diMouse = NULL; // Device interface
LPDIRECTINPUTDEVICE8    diKeybrd = NULL; // Device interface
byte Keys[256];
long axX, axY, axZ, nmX, nmY;
float PI = 3.14159265358979323846;


HRESULT InitInputDevice(HWND hInstance)
{
    HRESULT hr;
    for (int i = 8; i < 8; i++)
        Buttons[i] = false;
    if (FAILED(hr=DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, ( VOID** )&diiDI, NULL )))
        return hr;
    if (FAILED (hr=diiDI->CreateDevice(GUID_SysMouse,&diMouse, NULL)))
        return hr;
    if (FAILED (hr=diMouse->SetDataFormat(&c_dfDIMouse2)))
        return hr;
    if (FAILED (hr=diMouse->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        return hr;
    //mouse

    if (FAILED (hr=diiDI->CreateDevice(GUID_SysKeyboard,&diKeybrd, NULL)))
        return hr;
    if (FAILED (hr=diKeybrd->SetDataFormat(&c_dfDIKeyboard)))
        return hr;
    if (FAILED (hr=diKeybrd->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        return hr;


    return S_OK;
}


byte* ReadInputState(long* axs)
{
    HRESULT hr;
    DIMOUSESTATE2 ms;
    hr = diMouse->Poll();
    if (FAILED(hr))
    {
        hr = diMouse->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diMouse->Acquire();
        return S_OK;
    }
    diMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &ms);

    for (int i = 0; i < 8; i++)
    {
        if (ms.rgbButtons[i])
            Buttons[i] = true;
        else
            Buttons[i] = false;
    }
    if(Buttons[2])
    {
        axX += ms.lX;																	//Mouse
        axY += (ms.lY)*PI/180;
        axZ += ms.lZ;
    }
    if(Buttons[1])      //melo odejit
    {
        return Keys;
    }
    nmX+=ms.lX;
    nmY+=ms.lY;
    //axX += ms.lX;

    axs[0] = axX;
    axs[1] = axY;
    axs[2] = axZ;
    axs[3] = nmX;
    axs[4] = nmY;

    hr = diKeybrd->Poll();
    if (FAILED(hr))
    {
        hr = diKeybrd->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diKeybrd->Acquire();
        return S_OK;
    }
    diKeybrd->GetDeviceState(256, &Keys);
    return Keys;
}
