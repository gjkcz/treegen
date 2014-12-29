#include <windows.h>
#include "Engine.hpp"

//#include "inits.h"
#include "view.h"
//#include "controler.h"
#include "globals.h"

//byte* Keys = new byte[256];     // array holding status of each keyboard key
//long* axs = new long[4];        // aray to hold values of each mouse axis
//LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointer
//D3DXMATRIXA16* treeMatrix = new D3DXMATRIXA16[iObsah];   // array of matrices to hold the rotation and position of each tree
//LPDIRECT3DVERTEXBUFFER9* treeVertexBuffers = new LPDIRECT3DVERTEXBUFFER9[iObsah]; // array of Buffers to hold vertices

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
//    sw::Okno okno1 = sw::Okno(sw::Pozice(screenX, screenY), sw::Rozmery(width, height), "Tree");    //vytvor okno
    sw::Okno okno1 = sw::Okno(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer

    se::Engine iEngine = se::Engine(okno1);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice
//    se::Engine::prepareInputDevices();
    RedirectIOToConsole();  // Presmeruj IO do nasi nove konzole

// ve skutecnosti vubec Tmatxy nepotrebuje, jenom je alokovalo    if( SUCCEEDED( InitD3D( okno1.hWnd, g_pd3dDevice, TMatX ) ) ) {     // Initialize Direct3D, v souboru view
//        if( SUCCEEDED( InitInputDevice( okno1.hWnd ) ) ) {            // Inicializace mysi a klavesnice
//            int* Pocet = InitGeometry( g_pd3dDevice, TMatX, g_pVB );                // Create the scene geometry
//                iEngine.prectiVstup();
    okno1.ukaz();               // Show the window, az po inicializaci dx
    while ( okno1.jeOtevrene() ) {              // main loop
        //TODO:"kdyz klepnu na krizek, program prestal pracovat. Je to neco s konzoli?
        okno1.postarejSeOZpravy();
        iEngine.prectiVstup();

//                bQuit = ReadInputState( axs, Keys );
        if(iEngine.stav == WM_QUIT) {
            okno1.~Okno();
            break;
        }
        render( iEngine.vemG_pD3DDevice(), iEngine.vemPocetVrcholuStromu(),
                iEngine.vemKeys(), iEngine.vemAxs(), iEngine.vemTreeMatrixy(),
                iEngine.vemTreeVertexBuffers());
    }
//        }
//    }

    return 0;
}
