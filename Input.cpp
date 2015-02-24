#include "Input.hpp"
namespace si
{

//Input::Input()
//{
//    Keys = new byte[256];
//    axs = new long[4];
//}

Input::Input(HWND& _hWnd)
{
    axX = 0;
    axY = 0;
    axZ = 0;
    nmX = 0.f;
    nmY = 0.f;
    Keys = new byte[256];
    axs = new float[4];
    for (bool& b : Buttons)
    {
        b = false;
    }
    hWnd = _hWnd;
//    std::cout << "Volam fci prepareInputDevices.\n";
    prepareInputDevices();
}

void Input::prepareInputDevices()
{
    HRESULT hr;
//    for (int i = 8; i < 8; i++)
//        Buttons[i] = false;
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
    for ( int i = 0; i < 256; ++i)
    {
        Keys[i] = 0;
    }
}

void Input::releaseDin()
{
    if(diKeybrd != NULL){
        diKeybrd->Release();
        diKeybrd = NULL;
    }
    if(diMouse != NULL){
        diMouse->Release();
        diMouse = NULL;
    }
    if(diiDI != NULL){
        diiDI->Release();
        diiDI = NULL;
    }
}

Input::~Input()
{
#ifdef DESTRUCTORVERBOSE
    std::cout << "Destructor Inputu." << std::endl;
#endif // DESTRUCTORVERBOSE
#ifdef DESTRUCTORVERBOSE
    std::cout << "delete[] keys." << std::endl;
#endif // DESTRUCTORVERBOSE
    delete[] Keys;
#ifdef DESTRUCTORVERBOSE
    std::cout << "delete[] axs." << std::endl;
#endif // DESTRUCTORVERBOSE
    delete[] axs;
#ifdef DESTRUCTORVERBOSE
    std::cout << "release dins." << std::endl;
#endif // DESTRUCTORVERBOSE
    releaseDin();
#ifdef DESTRUCTORVERBOSE
    std::cout << "ok." << std::endl;
#endif // DESTRUCTORVERBOSE
//    delete[] Buttons;
}

std::string& Input::prectiStavVstupu()
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
        vysledek = "nic";
        return vysledek;
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
    if(Buttons[1]) {    // odejit
        vysledek = "odejdi";
        return vysledek;
    }
    if(Buttons[0]){
        vysledek = "gener";
    }
    else
        vysledek = "nic";
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
        vysledek = "nic";
        return vysledek;
    }
    diKeybrd->GetDeviceState( 256, Keys );
//    vysledek = "nic";
    return vysledek;
}


}
