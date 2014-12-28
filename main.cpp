#include <windows.h>
#include "SWU/Okno.hpp"
#include "Engine.hpp"

#include "inits.h"
#include "view.h"
#include "controler.h"
#include "globals.h"

byte* Keys = new byte[256];     // array holding status of each keyboard key
long* axs = new long[4];        // aray to hold values of each mouse axis
LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointer
D3DXMATRIXA16* TMatX = new D3DXMATRIXA16[iObsah];   // array of matrices to hold the rotation and position of each tree
LPDIRECT3DVERTEXBUFFER9* g_pVB = new LPDIRECT3DVERTEXBUFFER9[iObsah]; // array of Buffers to hold vertices

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    HRESULT bQuit=NULL;
//    sw::Okno okno1 = sw::Okno(sw::Pozice(screenX, screenY), sw::Rozmery(width, height), "Tree");    //vytvor okno
    sw::Okno okno1 = sw::Okno(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer
    se::Engine::prepareD3D();
    se::Engine::prepareInputDevices();
    RedirectIOToConsole();  // Presmeruj IO do nasi nove konzole

    if( SUCCEEDED( InitD3D( okno1.hWnd, g_pd3dDevice, TMatX ) ) ) {     // Initialize Direct3D
        if( SUCCEEDED( InitInputDevice( okno1.hWnd ) ) ) {            // Inicializace mysi a klavesnice
            int* Pocet = InitGeometry( g_pd3dDevice, TMatX, g_pVB );                // Create the scene geometry
            okno1.ukaz();               // Show the window, az po inicializaci dx
            while ( okno1.jeOtevrene() ) {
                //TODO:"kdyz klepnu na krizek, program prestal pracovat. Je to neco s konzoli?
                okno1.postarejSeOZpravy();
                bQuit = ReadInputState( axs, Keys );
                if(bQuit == WM_QUIT) okno1.~Okno();
                render( g_pd3dDevice, Pocet, Keys, axs, TMatX, g_pVB );
            }
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    for(int i = 0; i < iObsah; i++) {
        if( g_pVB[i] != NULL )
            g_pVB[i]->Release();
    }
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();
}

float random()
{
    float _rndm=0.f;
    //_rndm = abs(sin((timeGetTime() % 360)*(rand()/32767.f)*D3DX_PI/180));
    /*while(_rndm<0.998f)
    {*/
    while(timeGetTime()%1000>=999) {
        srand(timeGetTime());
    }
    _rndm = rand()/32000.f;
    return _rndm;
}

int zaokrouhli(float _f)
{
    int _v=0;
    if((_f -(int)_f) < 0.5)
        _v = _f-(_f -(int)_f);
    else
        _v = _f-(_f -(int)_f)+1;
    return _v;
}
