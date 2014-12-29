#include "Input.hpp"
namespace si
{


Input::Input(HWND hWnd)
{
    prepareInputDevices(hWnd);
}

void Input::prepareInputDevices(HWND hWnd)
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

    std::cout << S_OK;
}

Input::~Input()
{
}


}
