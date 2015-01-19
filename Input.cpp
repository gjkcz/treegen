#include "Input.hpp"
namespace si
{

//Input::Input()
//{
//    Keys = new byte[256];
//    axs = new long[4];
//}

Input::Input(HWND _hWnd)
{
    axX = 0;
    axY = 0;
    axZ = 0;
    Keys = new byte[256];
    axs = new float[4];
    hWnd = _hWnd;
//    std::cout << "Volam fci prepareInputDevices.\n";
    prepareInputDevices();
}

void Input::prepareInputDevices()
{
    HRESULT hr;
    for (int i = 8; i < 8; i++)
        Buttons[i] = false;
    if (FAILED(hr=DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, ( VOID** )&diiDI, NULL )))
        std::cout << hr;
    if (FAILED (hr=diiDI->CreateDevice(GUID_SysMouse,&diMouse, NULL)))
        std::cout << hr;
    if (FAILED (hr=diMouse->SetDataFormat(&c_dfDIMouse2)))
        std::cout << hr;
    if (FAILED (hr=diMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        std::cout << hr;
    //mouse

    if (FAILED (hr=diiDI->CreateDevice(GUID_SysKeyboard,&diKeybrd, NULL)))
        std::cout << hr;
    if (FAILED (hr=diKeybrd->SetDataFormat(&c_dfDIKeyboard)))
        std::cout << hr;
    if (FAILED (hr=diKeybrd->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        std::cout << hr;

//        axs = new long[4];
//            Keys = new byte[256];

    std::cout << S_OK;
}

void Input::reset()
{
    axs[0] = 0.f;
    axs[1] = 0.f;
    axs[2] = 0.f;
    axs[3] = 0.f;
    axs[4] = 0.f;
}

Input::~Input()
{
    delete Keys;
    delete axs;
}

HRESULT Input::prectiStavVstupu()
{
//        axs = new long[4];
//            Keys = new byte[256];

    HRESULT hr;
    DIMOUSESTATE2 ms;
    hr = diMouse->Poll();
    if (FAILED(hr)) {
        hr = diMouse->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diMouse->Acquire();
        return S_OK;
    }
    diMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &ms);

    for (int i = 0; i < 8; i++) {
        if (ms.rgbButtons[i])
            Buttons[i] = true;
        else
            Buttons[i] = false;
    }
    if(true || Buttons[2]) {        //timto zpusobuji kontrolu pohybu mysi tlacitkem
        axX -= ms.lX;																	//Mouse
        axY -= (ms.lY);//*PI/180;
        axZ += ms.lZ;
    }
    if(Buttons[1]) {    //melo odejit
        return WM_QUIT;
    }
//    nmX+=ms.lX;
//    nmY+=ms.lY;
    //axX += ms.lX;

    axs[0] = axX;
    axs[1] = axY;
    axs[2] = axZ;
    axs[3] = nmX;
    axs[4] = nmY;

    hr = diKeybrd->Poll();																//Klavesnice
    if (FAILED(hr)) {
        hr = diKeybrd->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diKeybrd->Acquire();
        return S_OK;
    }
    diKeybrd->GetDeviceState( 256, Keys );
    return S_OK;
}

}
